This is a test program intended to validate an optimization I implemented in clang‑llvm for duplicate `QueryInterface` calls on the same object and interface in COM programming. According to the COM protocol, if the first `QueryInterface` call for a given object and IID succeeds, subsequent calls are guaranteed to succeed as well, though they are not required to return the same pointer value. However, even if different values are returned, the originally returned pointer remains valid, so it is generally safe to merge duplicate `QueryInterface` calls. In fact, Windows team have already considered doing this (see this PR: https://github.com/microsoft/cppwinrt/pull/1579).

I implemented this optimization in my branch: https://github.com/YexuanXiao/llvm-project/tree/com-qi. The approach first introduces a C++ attribute, `[[clang::com_iunknown]]`, to mark a type as an IUnknown ABI type. This prevents the optimizer from incorrectly applying the optimization to unrelated types, so it must be proactively added by the user. After that, it runs two passes in sequence: `COMQIMergePass` and `COMAddRefReleaseElimPass`. The former replaces duplicate `QueryInterface` calls with the appropriate existing pointer, rewrites the return value to `S_OK`, and injects a corresponding `AddRef`. The latter finds and eliminates matching `AddRef`/`Release` pairs.

The repository includes a modified version of C++/WinRT 3.0.260520.1's `base.h`, named `base_fix.h`. Compared with the original, it makes only two changes: it applies the `[[clang::com_iunknown]]` attribute to the IUnknown ABI type only when `WINRT_WINRT_ENABLE_QIOPT` is defined, and it removes the `noinline` attribute from `unconditional_release_ref()`. You can enable or disable the optimization simply by defining or not defining `WINRT_ENABLE_QIOPT`, without having to rebuild LLVM.

Finally, the project includes extensive test cases to verify correctness, along with a simple performance test to confirm that the optimization is actually effective.

To build LLVM, you should install Visual Studio 2026, Ninja (in PATH), CMake (available via Visual Studio Installer), and Clang (available via Visual Studio Installer). Then, open the Visual Studio Command Prompt in your preferred way, clone the com-qi branch, cd llvm-project, and run:

```powershell
cmake -G Ninja -B build ./llvm -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS="clang;lld" -DCMAKE_INSTALL_PREFIX="C:\clang" -DLLVM_PARALLEL_LINK_JOBS=1 -DLLVM_USE_LINKER=lld && ninja install
```

Be sure to change the `CMAKE_INSTALL_PREFIX` path to a local location on your local drive.

To use the custom LLVM build, you should edit `Directory.build.props` and change the path to the one used by `CMAKE_INSTALL_PREFIX`.
