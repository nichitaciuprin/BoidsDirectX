// C++/WinRT v2.0.220110.5

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#ifndef WINRT_Windows_Devices_Pwm_0_H
#define WINRT_Windows_Devices_Pwm_0_H
WINRT_EXPORT namespace winrt::Windows::Devices::Pwm::Provider
{
    struct IPwmProvider;
}
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    template <typename TResult> struct __declspec(empty_bases) IAsyncOperation;
}
WINRT_EXPORT namespace winrt::Windows::Foundation::Collections
{
    template <typename T> struct __declspec(empty_bases) IVectorView;
}
WINRT_EXPORT namespace winrt::Windows::Devices::Pwm
{
    enum class PwmPulsePolarity : int32_t
    {
        ActiveHigh = 0,
        ActiveLow = 1,
    };
    struct IPwmController;
    struct IPwmControllerStatics;
    struct IPwmControllerStatics2;
    struct IPwmControllerStatics3;
    struct IPwmPin;
    struct PwmController;
    struct PwmPin;
}
namespace winrt::impl
{
    template <> struct category<winrt::Windows::Devices::Pwm::IPwmController>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::IPwmControllerStatics>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::IPwmControllerStatics2>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::IPwmControllerStatics3>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::IPwmPin>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::PwmController>{ using type = class_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::PwmPin>{ using type = class_category; };
    template <> struct category<winrt::Windows::Devices::Pwm::PwmPulsePolarity>{ using type = enum_category; };
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::PwmController> = L"Windows.Devices.Pwm.PwmController";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::PwmPin> = L"Windows.Devices.Pwm.PwmPin";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::PwmPulsePolarity> = L"Windows.Devices.Pwm.PwmPulsePolarity";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::IPwmController> = L"Windows.Devices.Pwm.IPwmController";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics> = L"Windows.Devices.Pwm.IPwmControllerStatics";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics2> = L"Windows.Devices.Pwm.IPwmControllerStatics2";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics3> = L"Windows.Devices.Pwm.IPwmControllerStatics3";
    template <> inline constexpr auto& name_v<winrt::Windows::Devices::Pwm::IPwmPin> = L"Windows.Devices.Pwm.IPwmPin";
    template <> inline constexpr guid guid_v<winrt::Windows::Devices::Pwm::IPwmController>{ 0xC45F5C85,0xD2E8,0x42CF,{ 0x9B,0xD6,0xCF,0x5E,0xD0,0x29,0xE6,0xA7 } }; // C45F5C85-D2E8-42CF-9BD6-CF5ED029E6A7
    template <> inline constexpr guid guid_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics>{ 0x4263BDA1,0x8946,0x4404,{ 0xBD,0x48,0x81,0xDD,0x12,0x4A,0xF4,0xD9 } }; // 4263BDA1-8946-4404-BD48-81DD124AF4D9
    template <> inline constexpr guid guid_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics2>{ 0x44FC5B1F,0xF119,0x4BDD,{ 0x97,0xAD,0xF7,0x6E,0xF9,0x86,0x73,0x6D } }; // 44FC5B1F-F119-4BDD-97AD-F76EF986736D
    template <> inline constexpr guid guid_v<winrt::Windows::Devices::Pwm::IPwmControllerStatics3>{ 0xB2581871,0x0229,0x4344,{ 0xAE,0x3F,0x9B,0x7C,0xD0,0xE6,0x6B,0x94 } }; // B2581871-0229-4344-AE3F-9B7CD0E66B94
    template <> inline constexpr guid guid_v<winrt::Windows::Devices::Pwm::IPwmPin>{ 0x22972DC8,0xC6CF,0x4821,{ 0xB7,0xF9,0xC6,0x45,0x4F,0xB6,0xAF,0x79 } }; // 22972DC8-C6CF-4821-B7F9-C6454FB6AF79
    template <> struct default_interface<winrt::Windows::Devices::Pwm::PwmController>{ using type = winrt::Windows::Devices::Pwm::IPwmController; };
    template <> struct default_interface<winrt::Windows::Devices::Pwm::PwmPin>{ using type = winrt::Windows::Devices::Pwm::IPwmPin; };
    template <> struct abi<winrt::Windows::Devices::Pwm::IPwmController>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall get_PinCount(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_ActualFrequency(double*) noexcept = 0;
            virtual int32_t __stdcall SetDesiredFrequency(double, double*) noexcept = 0;
            virtual int32_t __stdcall get_MinFrequency(double*) noexcept = 0;
            virtual int32_t __stdcall get_MaxFrequency(double*) noexcept = 0;
            virtual int32_t __stdcall OpenPin(int32_t, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Devices::Pwm::IPwmControllerStatics>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall GetControllersAsync(void*, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Devices::Pwm::IPwmControllerStatics2>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall GetDefaultAsync(void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Devices::Pwm::IPwmControllerStatics3>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall GetDeviceSelector(void**) noexcept = 0;
            virtual int32_t __stdcall GetDeviceSelectorFromFriendlyName(void*, void**) noexcept = 0;
            virtual int32_t __stdcall FromIdAsync(void*, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Devices::Pwm::IPwmPin>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall get_Controller(void**) noexcept = 0;
            virtual int32_t __stdcall GetActiveDutyCyclePercentage(double*) noexcept = 0;
            virtual int32_t __stdcall SetActiveDutyCyclePercentage(double) noexcept = 0;
            virtual int32_t __stdcall get_Polarity(int32_t*) noexcept = 0;
            virtual int32_t __stdcall put_Polarity(int32_t) noexcept = 0;
            virtual int32_t __stdcall Start() noexcept = 0;
            virtual int32_t __stdcall Stop() noexcept = 0;
            virtual int32_t __stdcall get_IsStarted(bool*) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Windows_Devices_Pwm_IPwmController
    {
        [[nodiscard]] WINRT_IMPL_AUTO(int32_t) PinCount() const;
        [[nodiscard]] WINRT_IMPL_AUTO(double) ActualFrequency() const;
        WINRT_IMPL_AUTO(double) SetDesiredFrequency(double desiredFrequency) const;
        [[nodiscard]] WINRT_IMPL_AUTO(double) MinFrequency() const;
        [[nodiscard]] WINRT_IMPL_AUTO(double) MaxFrequency() const;
        WINRT_IMPL_AUTO(winrt::Windows::Devices::Pwm::PwmPin) OpenPin(int32_t pinNumber) const;
    };
    template <> struct consume<winrt::Windows::Devices::Pwm::IPwmController>
    {
        template <typename D> using type = consume_Windows_Devices_Pwm_IPwmController<D>;
    };
    template <typename D>
    struct consume_Windows_Devices_Pwm_IPwmControllerStatics
    {
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Devices::Pwm::PwmController>>) GetControllersAsync(winrt::Windows::Devices::Pwm::Provider::IPwmProvider const& provider) const;
    };
    template <> struct consume<winrt::Windows::Devices::Pwm::IPwmControllerStatics>
    {
        template <typename D> using type = consume_Windows_Devices_Pwm_IPwmControllerStatics<D>;
    };
    template <typename D>
    struct consume_Windows_Devices_Pwm_IPwmControllerStatics2
    {
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Devices::Pwm::PwmController>) GetDefaultAsync() const;
    };
    template <> struct consume<winrt::Windows::Devices::Pwm::IPwmControllerStatics2>
    {
        template <typename D> using type = consume_Windows_Devices_Pwm_IPwmControllerStatics2<D>;
    };
    template <typename D>
    struct consume_Windows_Devices_Pwm_IPwmControllerStatics3
    {
        WINRT_IMPL_AUTO(hstring) GetDeviceSelector() const;
        WINRT_IMPL_AUTO(hstring) GetDeviceSelector(param::hstring const& friendlyName) const;
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Devices::Pwm::PwmController>) FromIdAsync(param::hstring const& deviceId) const;
    };
    template <> struct consume<winrt::Windows::Devices::Pwm::IPwmControllerStatics3>
    {
        template <typename D> using type = consume_Windows_Devices_Pwm_IPwmControllerStatics3<D>;
    };
    template <typename D>
    struct consume_Windows_Devices_Pwm_IPwmPin
    {
        [[nodiscard]] WINRT_IMPL_AUTO(winrt::Windows::Devices::Pwm::PwmController) Controller() const;
        WINRT_IMPL_AUTO(double) GetActiveDutyCyclePercentage() const;
        WINRT_IMPL_AUTO(void) SetActiveDutyCyclePercentage(double dutyCyclePercentage) const;
        [[nodiscard]] WINRT_IMPL_AUTO(winrt::Windows::Devices::Pwm::PwmPulsePolarity) Polarity() const;
        WINRT_IMPL_AUTO(void) Polarity(winrt::Windows::Devices::Pwm::PwmPulsePolarity const& value) const;
        WINRT_IMPL_AUTO(void) Start() const;
        WINRT_IMPL_AUTO(void) Stop() const;
        [[nodiscard]] WINRT_IMPL_AUTO(bool) IsStarted() const;
    };
    template <> struct consume<winrt::Windows::Devices::Pwm::IPwmPin>
    {
        template <typename D> using type = consume_Windows_Devices_Pwm_IPwmPin<D>;
    };
}
#endif
