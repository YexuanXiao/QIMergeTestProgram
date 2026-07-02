#include "TestRuntimeClass.h"
#include <winrt/Windows.Foundation.h>

namespace winrt::TestWinRT::implementation
{
    // -- ITestInterfaceA (default) --
    std::int32_t TestRuntimeClass::MethodA1(std::int32_t x) { return 100 + x; }
    std::int32_t TestRuntimeClass::MethodA2(std::int32_t x) { return 200 + x; }
    std::int32_t TestRuntimeClass::MethodA3(std::int32_t x, std::int32_t y) { return 300 + x + y; }
    std::int32_t TestRuntimeClass::MethodA4(std::int32_t x, std::int32_t y, std::int32_t z) { return 400 + x + y + z; }

    // -- ITestInterfaceB --
    std::int32_t TestRuntimeClass::MethodB1(std::int32_t x) { return 1100 + x; }
    std::int32_t TestRuntimeClass::MethodB2(std::int32_t x) { return 1200 + x; }
    std::int32_t TestRuntimeClass::MethodB3() { return 1300; }
    std::int32_t TestRuntimeClass::MethodB4(std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w) { return 1400 + x + y + z + w; }

    // -- ITestInterfaceC --
    std::int32_t TestRuntimeClass::MethodC1(std::int32_t x) { return 2100 + x; }
    std::int32_t TestRuntimeClass::MethodC2(std::int32_t x, std::int32_t y) { return 2200 + x + y; }

    // -- ITestInterfaceD --
    std::int32_t TestRuntimeClass::MethodD1(std::int32_t x) { return 3100 + x; }
    std::int32_t TestRuntimeClass::MethodD2(winrt::Windows::Foundation::IInspectable const& obj) { return 3200 + winrt::unbox_value<int32_t>(obj); }
    std::int32_t TestRuntimeClass::MethodD3(std::int32_t x, winrt::Windows::Foundation::IInspectable const& obj) { return 3300 + x + winrt::unbox_value<int32_t>(obj); }

    // -- ITestInterfaceE --
    hstring TestRuntimeClass::MethodE1(hstring const& s) { return hstring{L"E1:"} + s; }
    hstring TestRuntimeClass::MethodE2(hstring const& s) { return hstring{L"E2:"} + s; }
}
