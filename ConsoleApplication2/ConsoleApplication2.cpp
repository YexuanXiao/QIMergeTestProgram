#include <windows.h>
#define WINRT_ENABLE_QIOPT
#include "base_fixed.h"
#include "winrt/Windows.Foundation.h"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <chrono>

// Generated projection headers from TestInterfaces.idl
#include <winrt/TestWinRT.h>
#include "TestRuntimeClass.h"
#include "TestPerf.h"

using namespace winrt;
using namespace winrt::TestWinRT;

// =============================================================================
// Verification infrastructure
// =============================================================================

void verify(bool condition, const char* msg)
{
    if (condition)
    {
        std::printf("PASS: %s\n", msg);
    }
    else
    {
        std::printf("FAIL: %s\n", msg);
        exit(1);
    }
}

// =============================================================================
// Scope-isolation helpers — separate function boundaries for cross-scope tests
// =============================================================================

int32_t ScopeCall_B1(TestRuntimeClass const& obj)
{
    return obj.MethodB1(10);
}

int32_t ScopeCall_B2(TestRuntimeClass const& obj)
{
    return obj.MethodB2(20);
}

int32_t ScopeCall_C1(TestRuntimeClass const& obj)
{
    return obj.MethodC1(30);
}

int32_t ScopeCall_D1(TestRuntimeClass const& obj)
{
    return obj.MethodD1(40);
}

inline auto MakeTestObj() -> TestRuntimeClass
{
    return winrt::make<winrt::TestWinRT::implementation::TestRuntimeClass>();
}

// =============================================================================
// TEST GROUP 1 — Same non-default interface, value object
// =============================================================================

void Test_SameIface_Value_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodB2(20);
    verify(r1 == 1110, "SameIface_Value_B: MethodB1(10)");
    verify(r2 == 1220, "SameIface_Value_B: MethodB2(20)");
}

void Test_SameIface_Value_C()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodC1(10);
    int32_t r2 = obj.MethodC2(20, 30);
    verify(r1 == 2110, "SameIface_Value_C: MethodC1(10)");
    verify(r2 == 2250, "SameIface_Value_C: MethodC2(20,30)");
}

void Test_SameIface_Value_D()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodD1(10);
    int32_t r2 = obj.MethodD1(20);
    verify(r1 == 3110, "SameIface_Value_D: MethodD1(10)");
    verify(r2 == 3120, "SameIface_Value_D: MethodD1(20)");
}

void Test_SameIface_Value_E()
{
    auto obj = MakeTestObj();
    winrt::hstring r1 = obj.MethodE1(L"hello");
    winrt::hstring r2 = obj.MethodE2(L"world");
    verify(r1 == L"E1:hello", "SameIface_Value_E: MethodE1");
    verify(r2 == L"E2:world", "SameIface_Value_E: MethodE2");
}

// =============================================================================
// TEST GROUP 2 — Same non-default interface, reference
// =============================================================================

void Test_SameIface_Ref_B()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodB1(10);
    int32_t r2 = ref.MethodB2(20);
    verify(r1 == 1110, "SameIface_Ref_B: MethodB1(10)");
    verify(r2 == 1220, "SameIface_Ref_B: MethodB2(20)");
}

void Test_SameIface_Ref_C()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodC1(10);
    int32_t r2 = ref.MethodC2(20, 30);
    verify(r1 == 2110, "SameIface_Ref_C: MethodC1(10)");
    verify(r2 == 2250, "SameIface_Ref_C: MethodC2(20,30)");
}

void Test_SameIface_Ref_D()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodD1(10);
    int32_t r2 = ref.MethodD1(20);
    verify(r1 == 3110, "SameIface_Ref_D: MethodD1(10)");
    verify(r2 == 3120, "SameIface_Ref_D: MethodD1(20)");
}

// =============================================================================
// TEST GROUP 3 — Same non-default interface, pointer
// =============================================================================

void Test_SameIface_Ptr_B()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodB1(10);
    int32_t r2 = ptr->MethodB2(20);
    verify(r1 == 1110, "SameIface_Ptr_B: MethodB1(10)");
    verify(r2 == 1220, "SameIface_Ptr_B: MethodB2(20)");
}

void Test_SameIface_Ptr_C()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodC1(10);
    int32_t r2 = ptr->MethodC2(20, 30);
    verify(r1 == 2110, "SameIface_Ptr_C: MethodC1(10)");
    verify(r2 == 2250, "SameIface_Ptr_C: MethodC2(20,30)");
}

void Test_SameIface_Ptr_D()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodD1(10);
    int32_t r2 = ptr->MethodD1(20);
    verify(r1 == 3110, "SameIface_Ptr_D: MethodD1(10)");
    verify(r2 == 3120, "SameIface_Ptr_D: MethodD1(20)");
}

// =============================================================================
// TEST GROUP 4 — Different non-default interfaces, value object
// =============================================================================

void Test_DiffIface_Value_BC()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodC1(30);
    verify(r1 == 1110, "DiffIface_Value_BC: MethodB1(10)");
    verify(r2 == 2130, "DiffIface_Value_BC: MethodC1(30)");
}

void Test_DiffIface_Value_BD()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodD1(40);
    verify(r1 == 1110, "DiffIface_Value_BD: MethodB1(10)");
    verify(r2 == 3140, "DiffIface_Value_BD: MethodD1(40)");
}

void Test_DiffIface_Value_CD()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodC1(10);
    int32_t r2 = obj.MethodD1(40);
    verify(r1 == 2110, "DiffIface_Value_CD: MethodC1(10)");
    verify(r2 == 3140, "DiffIface_Value_CD: MethodD1(40)");
}

void Test_DiffIface_Value_BE()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    winrt::hstring r2 = obj.MethodE1(L"x");
    verify(r1 == 1110, "DiffIface_Value_BE: MethodB1(10)");
    verify(r2 == L"E1:x", "DiffIface_Value_BE: MethodE1");
}

// =============================================================================
// TEST GROUP 5 — Different non-default interfaces, reference
// =============================================================================

void Test_DiffIface_Ref_BC()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodB1(10);
    int32_t r2 = ref.MethodC1(30);
    verify(r1 == 1110, "DiffIface_Ref_BC: MethodB1(10)");
    verify(r2 == 2130, "DiffIface_Ref_BC: MethodC1(30)");
}

void Test_DiffIface_Ref_BD()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodB1(10);
    int32_t r2 = ref.MethodD1(40);
    verify(r1 == 1110, "DiffIface_Ref_BD: MethodB1(10)");
    verify(r2 == 3140, "DiffIface_Ref_BD: MethodD1(40)");
}

// =============================================================================
// TEST GROUP 6 — Different non-default interfaces, pointer
// =============================================================================

void Test_DiffIface_Ptr_BC()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodB1(10);
    int32_t r2 = ptr->MethodC1(30);
    verify(r1 == 1110, "DiffIface_Ptr_BC: MethodB1(10)");
    verify(r2 == 2130, "DiffIface_Ptr_BC: MethodC1(30)");
}

void Test_DiffIface_Ptr_BD()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodB1(10);
    int32_t r2 = ptr->MethodD1(40);
    verify(r1 == 1110, "DiffIface_Ptr_BD: MethodB1(10)");
    verify(r2 == 3140, "DiffIface_Ptr_BD: MethodD1(40)");
}

// =============================================================================
// TEST GROUP 7 — Different scopes (function-call boundaries)
// =============================================================================

void Test_DiffScope_SameIface_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = ScopeCall_B1(obj);
    int32_t r2 = ScopeCall_B2(obj);
    verify(r1 == 1110, "DiffScope_SameIface_B: ScopeCall_B1");
    verify(r2 == 1220, "DiffScope_SameIface_B: ScopeCall_B2");
}

void Test_DiffScope_DiffIface_BC()
{
    auto obj = MakeTestObj();
    int32_t r1 = ScopeCall_B1(obj);
    int32_t r2 = ScopeCall_C1(obj);
    verify(r1 == 1110, "DiffScope_DiffIface_BC: ScopeCall_B1");
    verify(r2 == 2130, "DiffScope_DiffIface_BC: ScopeCall_C1");
}

void Test_DiffScope_DiffIface_BD()
{
    auto obj = MakeTestObj();
    int32_t r1 = ScopeCall_B1(obj);
    int32_t r2 = ScopeCall_D1(obj);
    verify(r1 == 1110, "DiffScope_DiffIface_BD: ScopeCall_B1");
    verify(r2 == 3140, "DiffScope_DiffIface_BD: ScopeCall_D1");
}

void Test_DiffScope_Mixed_LocalRemote_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = ScopeCall_B2(obj);
    verify(r1 == 1110, "DiffScope_Mixed_LocalRemote_B: MethodB1");
    verify(r2 == 1220, "DiffScope_Mixed_LocalRemote_B: ScopeCall_B2");
}

// =============================================================================
// TEST GROUP 8 — Default interface (ITestInterfaceA)
// =============================================================================

void Test_DefaultIface_Value_TwoMethods()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(10);
    int32_t r2 = obj.MethodA2(20);
    verify(r1 == 110, "DefaultIface_Value: MethodA1(10)");
    verify(r2 == 220, "DefaultIface_Value: MethodA2(20)");
}

void Test_DefaultIface_Value_ThreeMethods()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(1);
    int32_t r2 = obj.MethodA2(2);
    int32_t r3 = obj.MethodA3(3, 4);
    verify(r1 == 101, "DefaultIface_Three: A1");
    verify(r2 == 202, "DefaultIface_Three: A2");
    verify(r3 == 307, "DefaultIface_Three: A3");
}

void Test_DefaultIface_Value_FourMethods()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(1);
    int32_t r2 = obj.MethodA2(2);
    int32_t r3 = obj.MethodA3(3, 4);
    int32_t r4 = obj.MethodA4(5, 6, 7);
    verify(r1 == 101, "DefaultIface_Four: A1");
    verify(r2 == 202, "DefaultIface_Four: A2");
    verify(r3 == 307, "DefaultIface_Four: A3");
    verify(r4 == 418, "DefaultIface_Four: A4");
}

void Test_DefaultIface_Ref()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodA1(10);
    int32_t r2 = ref.MethodA2(20);
    verify(r1 == 110, "DefaultIface_Ref: MethodA1");
    verify(r2 == 220, "DefaultIface_Ref: MethodA2");
}

void Test_DefaultIface_Ptr()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodA1(10);
    int32_t r2 = ptr->MethodA2(20);
    verify(r1 == 110, "DefaultIface_Ptr: MethodA1");
    verify(r2 == 220, "DefaultIface_Ptr: MethodA2");
}

// =============================================================================
// TEST GROUP 9 — Mixed default + non-default interfaces
// =============================================================================

void Test_MixedDefaultNonDefault_AB()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(10);
    int32_t r2 = obj.MethodB1(20);
    int32_t r3 = obj.MethodA2(30);
    verify(r1 == 110,  "Mixed_AB: MethodA1");
    verify(r2 == 1120, "Mixed_AB: MethodB1");
    verify(r3 == 230,  "Mixed_AB: MethodA2");
}

void Test_MixedDefaultNonDefault_AC()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(10);
    int32_t r2 = obj.MethodC1(20);
    int32_t r3 = obj.MethodA3(30, 40);
    verify(r1 == 110,  "Mixed_AC: MethodA1");
    verify(r2 == 2120, "Mixed_AC: MethodC1");
    verify(r3 == 370,  "Mixed_AC: MethodA3");
}

void Test_MixedDefaultNonDefault_ABC()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(1);
    int32_t r2 = obj.MethodB1(2);
    int32_t r3 = obj.MethodC1(3);
    verify(r1 == 101,  "Mixed_ABC: MethodA1");
    verify(r2 == 1102, "Mixed_ABC: MethodB1");
    verify(r3 == 2103, "Mixed_ABC: MethodC1");
}

// =============================================================================
// TEST GROUP 10 — Zero-parameter and multi-parameter methods
// =============================================================================

void Test_ZeroParam_Value_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB3();
    int32_t r2 = obj.MethodB3();
    int32_t r3 = obj.MethodB3();
    verify(r1 == 1300, "ZeroParam_B: call 1");
    verify(r2 == 1300, "ZeroParam_B: call 2");
    verify(r3 == 1300, "ZeroParam_B: call 3");
}

void Test_MultiParam_Value_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB4(1, 2, 3, 4);
    int32_t r2 = obj.MethodB4(5, 6, 7, 8);
    verify(r1 == 1410, "MultiParam_B: (1,2,3,4)");
    verify(r2 == 1426, "MultiParam_B: (5,6,7,8)");
}

void Test_MixedParamCounts_Value_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB3();
    int32_t r2 = obj.MethodB1(1);
    int32_t r3 = obj.MethodB2(2);
    int32_t r4 = obj.MethodB4(3, 4, 5, 6);
    verify(r1 == 1300, "MixedParamCounts_B: B3()");
    verify(r2 == 1101, "MixedParamCounts_B: B1(1)");
    verify(r3 == 1202, "MixedParamCounts_B: B2(2)");
    verify(r4 == 1418, "MixedParamCounts_B: B4(3,4,5,6)");
}

// =============================================================================
// TEST GROUP 11 — Three/ four methods on same non-default interface
// =============================================================================

void Test_ThreeMethods_SameIface_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(1);
    int32_t r2 = obj.MethodB2(2);
    int32_t r3 = obj.MethodB3();
    verify(r1 == 1101, "ThreeMethods_B: B1");
    verify(r2 == 1202, "ThreeMethods_B: B2");
    verify(r3 == 1300, "ThreeMethods_B: B3");
}

void Test_FourMethods_SameIface_B()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(1);
    int32_t r2 = obj.MethodB2(2);
    int32_t r3 = obj.MethodB3();
    int32_t r4 = obj.MethodB4(3, 4, 5, 6);
    verify(r1 == 1101, "FourMethods_B: B1");
    verify(r2 == 1202, "FourMethods_B: B2");
    verify(r3 == 1300, "FourMethods_B: B3");
    verify(r4 == 1418, "FourMethods_B: B4");
}

// =============================================================================
// TEST GROUP 12 — Three/ four methods on different non-default interfaces
// =============================================================================

void Test_ThreeMethods_DiffIface_BCD()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(1);
    int32_t r2 = obj.MethodC1(2);
    int32_t r3 = obj.MethodD1(3);
    verify(r1 == 1101, "ThreeDiff_BCD: B1");
    verify(r2 == 2102, "ThreeDiff_BCD: C1");
    verify(r3 == 3103, "ThreeDiff_BCD: D1");
}

void Test_FourMethods_DiffIface_BCDE()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(1);
    int32_t r2 = obj.MethodC1(2);
    int32_t r3 = obj.MethodD1(3);
    winrt::hstring r4 = obj.MethodE1(L"test");
    verify(r1 == 1101, "FourDiff_BCDE: B1");
    verify(r2 == 2102, "FourDiff_BCDE: C1");
    verify(r3 == 3103, "FourDiff_BCDE: D1");
    verify(r4 == L"E1:test", "FourDiff_BCDE: E1");
}

// =============================================================================
// TEST GROUP 13 — Object (IInspectable) parameters
// =============================================================================

void Test_ObjParam_Value_D()
{
    auto obj = MakeTestObj();
    auto param = winrt::box_value(42);
    int32_t r1 = obj.MethodD2(param);
    int32_t r2 = obj.MethodD3(10, param);
    verify(r1 == 3242, "ObjParam_D: MethodD2(42)");
    verify(r2 == 3352, "ObjParam_D: MethodD3(10,42)");
}

void Test_ObjParam_Ref_D()
{
    auto obj = MakeTestObj();
    auto param = winrt::box_value(42);
    auto& ref = obj;
    int32_t r1 = ref.MethodD2(param);
    int32_t r2 = ref.MethodD3(10, param);
    verify(r1 == 3242, "ObjParam_Ref_D: MethodD2(42)");
    verify(r2 == 3352, "ObjParam_Ref_D: MethodD3(10,42)");
}

void Test_ObjParam_Ptr_D()
{
    auto obj = MakeTestObj();
    auto param = winrt::box_value(42);
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodD2(param);
    int32_t r2 = ptr->MethodD3(10, param);
    verify(r1 == 3242, "ObjParam_Ptr_D: MethodD2(42)");
    verify(r2 == 3352, "ObjParam_Ptr_D: MethodD3(10,42)");
}

void Test_ObjParam_Mixed_D1_D2()
{
    auto obj = MakeTestObj();
    auto param = winrt::box_value(42);
    int32_t r1 = obj.MethodD1(10);
    int32_t r2 = obj.MethodD2(param);
    verify(r1 == 3110, "ObjParam_Mixed: D1");
    verify(r2 == 3242, "ObjParam_Mixed: D2(42)");
}

// =============================================================================
// TEST GROUP 14 — Same method called repeatedly
// =============================================================================

void Test_SameMethodTwice_Value_B1()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodB1(10);
    int32_t r3 = obj.MethodB1(10);
    verify(r1 == 1110, "SameMethodTwice_B1: call 1");
    verify(r2 == 1110, "SameMethodTwice_B1: call 2");
    verify(r3 == 1110, "SameMethodTwice_B1: call 3");
}

void Test_SameMethodTwice_Value_C1()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodC1(10);
    int32_t r2 = obj.MethodC1(10);
    verify(r1 == 2110, "SameMethodTwice_C1: call 1");
    verify(r2 == 2110, "SameMethodTwice_C1: call 2");
}

void Test_SameMethodTwice_Value_D1()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodD1(10);
    int32_t r2 = obj.MethodD1(10);
    verify(r1 == 3110, "SameMethodTwice_D1: call 1");
    verify(r2 == 3110, "SameMethodTwice_D1: call 2");
}

// =============================================================================
// TEST GROUP 15 — String parameter/return type methods
// =============================================================================

void Test_StringParam_Value_E()
{
    auto obj = MakeTestObj();
    winrt::hstring r1 = obj.MethodE1(L"hello");
    winrt::hstring r2 = obj.MethodE2(L"world");
    winrt::hstring r3 = obj.MethodE1(L"foo");
    verify(r1 == L"E1:hello", "StringParam_E: E1(hello)");
    verify(r2 == L"E2:world", "StringParam_E: E2(world)");
    verify(r3 == L"E1:foo",   "StringParam_E: E1(foo)");
}

void Test_StringParam_Ref_E()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    winrt::hstring r1 = ref.MethodE1(L"a");
    winrt::hstring r2 = ref.MethodE2(L"b");
    verify(r1 == L"E1:a", "StringParam_Ref_E: E1");
    verify(r2 == L"E2:b", "StringParam_Ref_E: E2");
}

void Test_StringParam_Ptr_E()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    winrt::hstring r1 = ptr->MethodE1(L"a");
    winrt::hstring r2 = ptr->MethodE2(L"b");
    verify(r1 == L"E1:a", "StringParam_Ptr_E: E1");
    verify(r2 == L"E2:b", "StringParam_Ptr_E: E2");
}

// =============================================================================
// TEST GROUP 16 — All non-default interfaces interleaved
// =============================================================================

void Test_AllNonDefault_Interleaved()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(1);
    int32_t r2 = obj.MethodC1(2);
    int32_t r3 = obj.MethodD1(3);
    int32_t r4 = obj.MethodB2(4);
    int32_t r5 = obj.MethodC2(5, 6);
    winrt::hstring r6 = obj.MethodE1(L"x");
    verify(r1 == 1101, "AllNonDefault: B1");
    verify(r2 == 2102, "AllNonDefault: C1");
    verify(r3 == 3103, "AllNonDefault: D1");
    verify(r4 == 1204, "AllNonDefault: B2");
    verify(r5 == 2211, "AllNonDefault: C2");
    verify(r6 == L"E1:x", "AllNonDefault: E1");
}

void Test_AllNonDefault_Interleaved_Ref()
{
    auto obj = MakeTestObj();
    auto& ref = obj;
    int32_t r1 = ref.MethodB1(1);
    int32_t r2 = ref.MethodC1(2);
    int32_t r3 = ref.MethodD1(3);
    int32_t r4 = ref.MethodB2(4);
    verify(r1 == 1101, "AllNonDefault_Ref: B1");
    verify(r2 == 2102, "AllNonDefault_Ref: C1");
    verify(r3 == 3103, "AllNonDefault_Ref: D1");
    verify(r4 == 1204, "AllNonDefault_Ref: B2");
}

void Test_AllNonDefault_Interleaved_Ptr()
{
    auto obj = MakeTestObj();
    auto* ptr = &obj;
    int32_t r1 = ptr->MethodB1(1);
    int32_t r2 = ptr->MethodC1(2);
    int32_t r3 = ptr->MethodD1(3);
    int32_t r4 = ptr->MethodB2(4);
    verify(r1 == 1101, "AllNonDefault_Ptr: B1");
    verify(r2 == 2102, "AllNonDefault_Ptr: C1");
    verify(r3 == 3103, "AllNonDefault_Ptr: D1");
    verify(r4 == 1204, "AllNonDefault_Ptr: B2");
}

// =============================================================================
// TEST GROUP 17 — Nested basic-block scopes
// =============================================================================

void Test_NestedScope_B()
{
    auto obj = MakeTestObj();
    int32_t r1;
    int32_t r2;
    {
        r1 = obj.MethodB1(10);
    }
    {
        r2 = obj.MethodB2(20);
    }
    verify(r1 == 1110, "NestedScope_B: MethodB1");
    verify(r2 == 1220, "NestedScope_B: MethodB2");
}

void Test_NestedScope_DiffIface_BC()
{
    auto obj = MakeTestObj();
    int32_t r1;
    int32_t r2;
    {
        r1 = obj.MethodB1(10);
    }
    {
        r2 = obj.MethodC1(30);
    }
    verify(r1 == 1110, "NestedScope_BC: MethodB1");
    verify(r2 == 2130, "NestedScope_BC: MethodC1");
}

// =============================================================================
// TEST GROUP 18 — Sequential calls: default iface ↔ non-default ↔ default
// =============================================================================

void Test_Interleaved_DefaultNonDefault_ABA()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodA1(1);
    int32_t r2 = obj.MethodB1(2);
    int32_t r3 = obj.MethodA2(3);
    int32_t r4 = obj.MethodB2(4);
    int32_t r5 = obj.MethodA3(5, 6);
    verify(r1 == 101,  "ABA: A1");
    verify(r2 == 1102, "ABA: B1");
    verify(r3 == 203,  "ABA: A2");
    verify(r4 == 1204, "ABA: B2");
    verify(r5 == 311,  "ABA: A3");
}

// =============================================================================
// TEST GROUP 19 — Edge case: different non-default ifaces with same-typed return
// =============================================================================

void Test_SameReturn_DifferentNonDefault()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB3();
    int32_t r2 = obj.MethodB1(0);
    int32_t r3 = obj.MethodC1(0);
    int32_t r4 = obj.MethodD1(0);
    verify(r1 == 1300, "SameReturn: B3");
    verify(r2 == 1100, "SameReturn: B1(0)");
    verify(r3 == 2100, "SameReturn: C1(0)");
    verify(r4 == 3100, "SameReturn: D1(0)");
}

// =============================================================================
// TEST GROUP 20 — Multiple objects in the same scope
// =============================================================================

void Test_MultipleObjects_SameScope()
{
    auto obj1 = MakeTestObj();
    auto obj2 = MakeTestObj();
    int32_t r1 = obj1.MethodB1(10);
    int32_t r2 = obj2.MethodB1(20);
    int32_t r3 = obj1.MethodB2(30);
    int32_t r4 = obj2.MethodB2(40);
    verify(r1 == 1110, "MultiObj: obj1.B1(10)");
    verify(r2 == 1120, "MultiObj: obj2.B1(20)");
    verify(r3 == 1230, "MultiObj: obj1.B2(30)");
    verify(r4 == 1240, "MultiObj: obj2.B2(40)");
}

void Test_MultipleObjects_DiffIface()
{
    auto obj1 = MakeTestObj();
    auto obj2 = MakeTestObj();
    int32_t r1 = obj1.MethodB1(10);
    int32_t r2 = obj2.MethodC1(20);
    int32_t r3 = obj1.MethodC1(30);
    int32_t r4 = obj2.MethodB1(40);
    verify(r1 == 1110, "MultiObjDiff: obj1.B1(10)");
    verify(r2 == 2120, "MultiObjDiff: obj2.C1(20)");
    verify(r3 == 2130, "MultiObjDiff: obj1.C1(30)");
    verify(r4 == 1140, "MultiObjDiff: obj2.B1(40)");
}

// =============================================================================
// TEST GROUP 21 — Interleaved two objects, same non-default interface
// If optimizer caches QI per UUID globally (not per object), obj1's cached
// interface pointer could be used for obj2 or vice versa → wrong results.
// =============================================================================

void Test_TwoObjs_Interleaved_SameIface()
{
    auto obj1 = MakeTestObj();
    auto obj2 = MakeTestObj();
    int32_t r1 = obj1.MethodB1(10);
    int32_t r2 = obj2.MethodB1(99);
    int32_t r3 = obj1.MethodB2(30);
    int32_t r4 = obj2.MethodB2(77);
    verify(r1 == 1110, "TwoObjs_Interleaved: obj1.B1(10)");
    verify(r2 == 1199, "TwoObjs_Interleaved: obj2.B1(99)");
    verify(r3 == 1230, "TwoObjs_Interleaved: obj1.B2(30)");
    verify(r4 == 1277, "TwoObjs_Interleaved: obj2.B2(77)");
}

// =============================================================================
// TEST GROUP 22 — Copied projection object
// A copy of the projection should independently QI (or at least work correctly).
// If the optimizer reuses QI across the original and copy, it could go wrong.
// =============================================================================

void Test_CopiedObject_SameIface()
{
    auto obj1 = MakeTestObj();
    auto obj2 = obj1;  // copy projection
    int32_t r1 = obj1.MethodB1(10);
    int32_t r2 = obj2.MethodB2(20);
    verify(r1 == 1110, "CopiedObj: original.B1(10)");
    verify(r2 == 1220, "CopiedObj: copy.B2(20)");
}

void Test_CopiedObject_DiffIface()
{
    auto obj1 = MakeTestObj();
    auto obj2 = obj1;
    int32_t r1 = obj1.MethodB1(10);
    int32_t r2 = obj2.MethodC1(30);
    verify(r1 == 1110, "CopiedObjDiff: original.B1(10)");
    verify(r2 == 2130, "CopiedObjDiff: copy.C1(30)");
}

// =============================================================================
// TEST GROUP 23 — Same object accessed via mixed value / ref / ptr
// The optimizer must correctly identify the same underlying object through
// different access patterns.
// =============================================================================

void Test_MixedAccessPatterns_SameIface()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    auto& ref = obj;
    int32_t r2 = ref.MethodB2(20);
    auto* ptr = &obj;
    int32_t r3 = ptr->MethodB3();
    verify(r1 == 1110, "MixedAccess: value.B1(10)");
    verify(r2 == 1220, "MixedAccess: ref.B2(20)");
    verify(r3 == 1300, "MixedAccess: ptr->B3()");
}

void Test_MixedAccessPatterns_DiffIface()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    auto& ref = obj;
    int32_t r2 = ref.MethodC1(20);
    auto* ptr = &obj;
    int32_t r3 = ptr->MethodD1(30);
    verify(r1 == 1110, "MixedAccessDiff: value.B1");
    verify(r2 == 2120, "MixedAccessDiff: ref.C1");
    verify(r3 == 3130, "MixedAccessDiff: ptr->D1");
}

// =============================================================================
// TEST GROUP 24 — Sequential branches (if/else)
// Calls in separate branches may or may not be merged; correctness must hold.
// =============================================================================

__declspec(noinline) bool always_true() { return true; }

void Test_Branches_SameIface()
{
    auto obj = MakeTestObj();
    int32_t r1;
    int32_t r2;
    if (always_true())
    {
        r1 = obj.MethodB1(10);
    }
    else
    {
        r1 = obj.MethodB1(0);
    }
    if (always_true())
    {
        r2 = obj.MethodB2(20);
    }
    else
    {
        r2 = obj.MethodB2(0);
    }
    verify(r1 == 1110, "Branches: B1(10)");
    verify(r2 == 1220, "Branches: B2(20)");
}

void Test_Branches_DiffIface()
{
    auto obj = MakeTestObj();
    int32_t r1;
    int32_t r2;
    if (always_true())
    {
        r1 = obj.MethodB1(10);
    }
    else
    {
        r1 = obj.MethodC1(0);
    }
    if (always_true())
    {
        r2 = obj.MethodC1(20);
    }
    else
    {
        r2 = obj.MethodB1(0);
    }
    verify(r1 == 1110, "BranchesDiff: B1(10)");
    verify(r2 == 2120, "BranchesDiff: C1(20)");
}

// =============================================================================
// TEST GROUP 25 — Method result used as argument to another call on same object
// The optimizer must evaluate the first call fully before passing result to
// the second call's QI-requiring path.
// =============================================================================

void Test_ResultAsArg_SameIface()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodB1(r1);        // use result of B1 as arg to B1
    int32_t r3 = obj.MethodB2(r2);        // use result of B1 as arg to B2
    verify(r1 == 1110, "ResultAsArg: B1(10)");
    verify(r2 == 2210, "ResultAsArg: B1(B1(10))");
    verify(r3 == 3410, "ResultAsArg: B2(B1(B1(10)))");
}

void Test_ResultAsArg_DiffIface()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodC1(r1);
    verify(r1 == 1110, "ResultAsArgDiff: B1(10)");
    verify(r2 == 3210, "ResultAsArgDiff: C1(B1(10))");
}

// =============================================================================
// TEST GROUP 26 — Object passed through helper by value then used
// =============================================================================

TestRuntimeClass passThrough(TestRuntimeClass x) { return x; }

void Test_PassThroughValue_ThenCall()
{
    auto obj = MakeTestObj();
    auto obj2 = passThrough(obj);
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj2.MethodB2(20);
    verify(r1 == 1110, "PassThrough: original.B1(10)");
    verify(r2 == 1220, "PassThrough: returned.B2(20)");
}

// =============================================================================
// TEST GROUP 27 — Three objects, each calling same interface
// Worst-case scenario: cache confusion across 3 objects
// =============================================================================

void Test_ThreeObjs_Interleaved()
{
    auto obj1 = MakeTestObj();
    auto obj2 = MakeTestObj();
    auto obj3 = MakeTestObj();
    int32_t r1 = obj1.MethodB1(1);
    int32_t r2 = obj2.MethodB1(2);
    int32_t r3 = obj3.MethodB1(3);
    int32_t r4 = obj1.MethodB2(4);
    int32_t r5 = obj2.MethodB2(5);
    int32_t r6 = obj3.MethodB2(6);
    verify(r1 == 1101, "ThreeObjs: obj1.B1(1)");
    verify(r2 == 1102, "ThreeObjs: obj2.B1(2)");
    verify(r3 == 1103, "ThreeObjs: obj3.B1(3)");
    verify(r4 == 1204, "ThreeObjs: obj1.B2(4)");
    verify(r5 == 1205, "ThreeObjs: obj2.B2(5)");
    verify(r6 == 1206, "ThreeObjs: obj3.B2(6)");
}

// =============================================================================
// TEST GROUP 28 — Check that default-interface calls are not polluted by QI
// If optimizer incorrectly applies non-default QI thinking to default calls.
// =============================================================================

void Test_DefaultNotPolluted_By_NonDefault()
{
    auto obj = MakeTestObj();
    int32_t r1 = obj.MethodB1(10);
    int32_t r2 = obj.MethodA1(20);
    int32_t r3 = obj.MethodB2(30);
    int32_t r4 = obj.MethodA2(40);
    verify(r1 == 1110, "DefaultNotPolluted: B1(10)");
    verify(r2 == 120,  "DefaultNotPolluted: A1(20)");
    verify(r3 == 1230, "DefaultNotPolluted: B2(30)");
    verify(r4 == 240,  "DefaultNotPolluted: A2(40)");
}

void test_correctness()
{
    std::printf("=== Running C++/WinRT QI merge optimization correctness tests ===\n");

    std::printf("[Group  1] Same non-default iface, value...\n");
    Test_SameIface_Value_B();
    Test_SameIface_Value_C();
    Test_SameIface_Value_D();
    Test_SameIface_Value_E();

    std::printf("[Group  2] Same non-default iface, ref...\n");
    Test_SameIface_Ref_B();
    Test_SameIface_Ref_C();
    Test_SameIface_Ref_D();

    std::printf("[Group  3] Same non-default iface, ptr...\n");
    Test_SameIface_Ptr_B();
    Test_SameIface_Ptr_C();
    Test_SameIface_Ptr_D();

    std::printf("[Group  4] Different non-default ifaces, value...\n");
    Test_DiffIface_Value_BC();
    Test_DiffIface_Value_BD();
    Test_DiffIface_Value_CD();
    Test_DiffIface_Value_BE();

    std::printf("[Group  5] Different non-default ifaces, ref...\n");
    Test_DiffIface_Ref_BC();
    Test_DiffIface_Ref_BD();

    std::printf("[Group  6] Different non-default ifaces, ptr...\n");
    Test_DiffIface_Ptr_BC();
    Test_DiffIface_Ptr_BD();

    std::printf("[Group  7] Different scopes...\n");
    Test_DiffScope_SameIface_B();
    Test_DiffScope_DiffIface_BC();
    Test_DiffScope_DiffIface_BD();
    Test_DiffScope_Mixed_LocalRemote_B();

    std::printf("[Group  8] Default interface...\n");
    Test_DefaultIface_Value_TwoMethods();
    Test_DefaultIface_Value_ThreeMethods();
    Test_DefaultIface_Value_FourMethods();
    Test_DefaultIface_Ref();
    Test_DefaultIface_Ptr();

    std::printf("[Group  9] Mixed default + non-default...\n");
    Test_MixedDefaultNonDefault_AB();
    Test_MixedDefaultNonDefault_AC();
    Test_MixedDefaultNonDefault_ABC();

    std::printf("[Group 10] Zero-param and multi-param...\n");
    Test_ZeroParam_Value_B();
    Test_MultiParam_Value_B();
    Test_MixedParamCounts_Value_B();

    std::printf("[Group 11] Three+ methods same iface...\n");
    Test_ThreeMethods_SameIface_B();
    Test_FourMethods_SameIface_B();

    std::printf("[Group 12] Three+ methods different ifaces...\n");
    Test_ThreeMethods_DiffIface_BCD();
    Test_FourMethods_DiffIface_BCDE();

    std::printf("[Group 13] Object parameters...\n");
    Test_ObjParam_Value_D();
    Test_ObjParam_Ref_D();
    Test_ObjParam_Ptr_D();
    Test_ObjParam_Mixed_D1_D2();

    std::printf("[Group 14] Same method called repeatedly...\n");
    Test_SameMethodTwice_Value_B1();
    Test_SameMethodTwice_Value_C1();
    Test_SameMethodTwice_Value_D1();

    std::printf("[Group 15] String param/return...\n");
    Test_StringParam_Value_E();
    Test_StringParam_Ref_E();
    Test_StringParam_Ptr_E();

    std::printf("[Group 16] All non-default interleaved...\n");
    Test_AllNonDefault_Interleaved();
    Test_AllNonDefault_Interleaved_Ref();
    Test_AllNonDefault_Interleaved_Ptr();

    std::printf("[Group 17] Nested scopes...\n");
    Test_NestedScope_B();
    Test_NestedScope_DiffIface_BC();

    std::printf("[Group 18] Interleaved default/non-default...\n");
    Test_Interleaved_DefaultNonDefault_ABA();

    std::printf("[Group 19] Same return, different non-default...\n");
    Test_SameReturn_DifferentNonDefault();

    std::printf("[Group 20] Multiple objects same scope...\n");
    Test_MultipleObjects_SameScope();
    Test_MultipleObjects_DiffIface();

    std::printf("[Group 21] Two objects interleaved same iface...\n");
    Test_TwoObjs_Interleaved_SameIface();

    std::printf("[Group 22] Copied projection object...\n");
    Test_CopiedObject_SameIface();
    Test_CopiedObject_DiffIface();

    std::printf("[Group 23] Mixed access patterns (value/ref/ptr)...\n");
    Test_MixedAccessPatterns_SameIface();
    Test_MixedAccessPatterns_DiffIface();

    std::printf("[Group 24] Branches (if/else)...\n");
    Test_Branches_SameIface();
    Test_Branches_DiffIface();

    std::printf("[Group 25] Result-as-argument...\n");
    Test_ResultAsArg_SameIface();
    Test_ResultAsArg_DiffIface();

    std::printf("[Group 26] Pass-through value...\n");
    Test_PassThroughValue_ThenCall();

    std::printf("[Group 27] Three objects interleaved...\n");
    Test_ThreeObjs_Interleaved();

    std::printf("[Group 28] Default not polluted by non-default...\n");
    Test_DefaultNotPolluted_By_NonDefault();

    std::printf("=== CORRECTNESS TESTS PASSED ===\n");
}

void test_perf_internal()
{
    const int loops = 10000;

    auto worker = winrt::make<winrt::TestWinRT::implementation::TestPerf>();

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i != loops; ++i) {
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
        worker.DoQI();
    }
    auto end = std::chrono::steady_clock::now();
    auto extra_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::printf("DoQI    : %lld ns\n", extra_ns);

    start = std::chrono::steady_clock::now();
    for (int i = 0; i != loops; ++i) {

        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
        worker.DoDirect();
    }
    end = std::chrono::steady_clock::now();
    auto default_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::printf("DoDirect: %lld ns\n", default_ns);
}

void test_perf()
{
	std::printf("=== Running C++/WinRT QI merge optimization performance tests ===\n");
	std::printf("Running round 1.\n");
	test_perf_internal();
	std::printf("Running round 2.\n");
    test_perf_internal();
	std::printf("Running round 3.\n");
    test_perf_internal();
	std::printf("=== PERFORMANCE TESTS DONE ===\n");
}

int main()
{
	test_correctness();
	test_perf();
}