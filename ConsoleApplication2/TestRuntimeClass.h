#pragma once
#include "TestWinRT.TestRuntimeClass.g.h"

namespace winrt::TestWinRT::implementation
{
    struct TestRuntimeClass : TestRuntimeClassT<TestRuntimeClass>
    {
        TestRuntimeClass() = default;

        std::int32_t MethodA1(std::int32_t x);
        std::int32_t MethodA2(std::int32_t x);
        std::int32_t MethodA3(std::int32_t x, std::int32_t y);
        std::int32_t MethodA4(std::int32_t x, std::int32_t y, std::int32_t z);
        std::int32_t MethodB1(std::int32_t x);
        std::int32_t MethodB2(std::int32_t x);
        std::int32_t MethodB3();
        std::int32_t MethodB4(std::int32_t x, std::int32_t y, std::int32_t z, std::int32_t w);
        std::int32_t MethodC1(std::int32_t x);
        std::int32_t MethodC2(std::int32_t x, std::int32_t y);
        std::int32_t MethodD1(std::int32_t x);
        std::int32_t MethodD2(winrt::Windows::Foundation::IInspectable const& obj);
        std::int32_t MethodD3(std::int32_t x, winrt::Windows::Foundation::IInspectable const& obj);
        hstring MethodE1(hstring const& s);
        hstring MethodE2(hstring const& s);
    };
}
