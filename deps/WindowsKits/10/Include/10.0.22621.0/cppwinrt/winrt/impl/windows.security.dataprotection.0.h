// C++/WinRT v2.0.220110.5

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#ifndef WINRT_Windows_Security_DataProtection_0_H
#define WINRT_Windows_Security_DataProtection_0_H
WINRT_EXPORT namespace winrt::Windows::Foundation
{
    struct Deferral;
    struct EventRegistrationToken;
    template <typename TResult> struct __declspec(empty_bases) IAsyncOperation;
    template <typename TSender, typename TResult> struct __declspec(empty_bases) TypedEventHandler;
}
WINRT_EXPORT namespace winrt::Windows::Storage
{
    struct IStorageItem;
}
WINRT_EXPORT namespace winrt::Windows::Storage::Streams
{
    struct IBuffer;
}
WINRT_EXPORT namespace winrt::Windows::System
{
    struct User;
}
WINRT_EXPORT namespace winrt::Windows::Security::DataProtection
{
    enum class UserDataAvailability : int32_t
    {
        Always = 0,
        AfterFirstUnlock = 1,
        WhileUnlocked = 2,
    };
    enum class UserDataBufferUnprotectStatus : int32_t
    {
        Succeeded = 0,
        Unavailable = 1,
    };
    enum class UserDataStorageItemProtectionStatus : int32_t
    {
        Succeeded = 0,
        NotProtectable = 1,
        DataUnavailable = 2,
    };
    struct IUserDataAvailabilityStateChangedEventArgs;
    struct IUserDataBufferUnprotectResult;
    struct IUserDataProtectionManager;
    struct IUserDataProtectionManagerStatics;
    struct IUserDataStorageItemProtectionInfo;
    struct UserDataAvailabilityStateChangedEventArgs;
    struct UserDataBufferUnprotectResult;
    struct UserDataProtectionManager;
    struct UserDataStorageItemProtectionInfo;
}
namespace winrt::impl
{
    template <> struct category<winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::IUserDataProtectionManager>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::IUserDataProtectionManagerStatics>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo>{ using type = interface_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataAvailabilityStateChangedEventArgs>{ using type = class_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectResult>{ using type = class_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataProtectionManager>{ using type = class_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionInfo>{ using type = class_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataAvailability>{ using type = enum_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectStatus>{ using type = enum_category; };
    template <> struct category<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionStatus>{ using type = enum_category; };
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataAvailabilityStateChangedEventArgs> = L"Windows.Security.DataProtection.UserDataAvailabilityStateChangedEventArgs";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectResult> = L"Windows.Security.DataProtection.UserDataBufferUnprotectResult";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataProtectionManager> = L"Windows.Security.DataProtection.UserDataProtectionManager";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionInfo> = L"Windows.Security.DataProtection.UserDataStorageItemProtectionInfo";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataAvailability> = L"Windows.Security.DataProtection.UserDataAvailability";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectStatus> = L"Windows.Security.DataProtection.UserDataBufferUnprotectStatus";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionStatus> = L"Windows.Security.DataProtection.UserDataStorageItemProtectionStatus";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs> = L"Windows.Security.DataProtection.IUserDataAvailabilityStateChangedEventArgs";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult> = L"Windows.Security.DataProtection.IUserDataBufferUnprotectResult";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::IUserDataProtectionManager> = L"Windows.Security.DataProtection.IUserDataProtectionManager";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::IUserDataProtectionManagerStatics> = L"Windows.Security.DataProtection.IUserDataProtectionManagerStatics";
    template <> inline constexpr auto& name_v<winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo> = L"Windows.Security.DataProtection.IUserDataStorageItemProtectionInfo";
    template <> inline constexpr guid guid_v<winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs>{ 0xA76582C9,0x06A2,0x4273,{ 0xA8,0x03,0x83,0x4C,0x9F,0x87,0xFB,0xEB } }; // A76582C9-06A2-4273-A803-834C9F87FBEB
    template <> inline constexpr guid guid_v<winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult>{ 0x8EFD0E90,0xFA9A,0x46A4,{ 0xA3,0x77,0x01,0xCE,0xBF,0x1E,0x74,0xD8 } }; // 8EFD0E90-FA9A-46A4-A377-01CEBF1E74D8
    template <> inline constexpr guid guid_v<winrt::Windows::Security::DataProtection::IUserDataProtectionManager>{ 0x1F13237D,0xB42E,0x4A88,{ 0x94,0x80,0x0F,0x24,0x09,0x24,0xC8,0x76 } }; // 1F13237D-B42E-4A88-9480-0F240924C876
    template <> inline constexpr guid guid_v<winrt::Windows::Security::DataProtection::IUserDataProtectionManagerStatics>{ 0x977780E8,0x6DCE,0x4FAE,{ 0xAF,0x85,0x78,0x2A,0xC2,0xCF,0x45,0x72 } }; // 977780E8-6DCE-4FAE-AF85-782AC2CF4572
    template <> inline constexpr guid guid_v<winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo>{ 0x5B6680F6,0xE87F,0x40A1,{ 0xB1,0x9D,0xA6,0x18,0x7A,0x0C,0x66,0x2F } }; // 5B6680F6-E87F-40A1-B19D-A6187A0C662F
    template <> struct default_interface<winrt::Windows::Security::DataProtection::UserDataAvailabilityStateChangedEventArgs>{ using type = winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs; };
    template <> struct default_interface<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectResult>{ using type = winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult; };
    template <> struct default_interface<winrt::Windows::Security::DataProtection::UserDataProtectionManager>{ using type = winrt::Windows::Security::DataProtection::IUserDataProtectionManager; };
    template <> struct default_interface<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionInfo>{ using type = winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo; };
    template <> struct abi<winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall GetDeferral(void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall get_Status(int32_t*) noexcept = 0;
            virtual int32_t __stdcall get_UnprotectedBuffer(void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Security::DataProtection::IUserDataProtectionManager>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall ProtectStorageItemAsync(void*, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall GetStorageItemProtectionInfoAsync(void*, void**) noexcept = 0;
            virtual int32_t __stdcall ProtectBufferAsync(void*, int32_t, void**) noexcept = 0;
            virtual int32_t __stdcall UnprotectBufferAsync(void*, void**) noexcept = 0;
            virtual int32_t __stdcall IsContinuedDataAvailabilityExpected(int32_t, bool*) noexcept = 0;
            virtual int32_t __stdcall add_DataAvailabilityStateChanged(void*, winrt::event_token*) noexcept = 0;
            virtual int32_t __stdcall remove_DataAvailabilityStateChanged(winrt::event_token) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Security::DataProtection::IUserDataProtectionManagerStatics>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall TryGetDefault(void**) noexcept = 0;
            virtual int32_t __stdcall TryGetForUser(void*, void**) noexcept = 0;
        };
    };
    template <> struct abi<winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo>
    {
        struct __declspec(novtable) type : inspectable_abi
        {
            virtual int32_t __stdcall get_Availability(int32_t*) noexcept = 0;
        };
    };
    template <typename D>
    struct consume_Windows_Security_DataProtection_IUserDataAvailabilityStateChangedEventArgs
    {
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::Deferral) GetDeferral() const;
    };
    template <> struct consume<winrt::Windows::Security::DataProtection::IUserDataAvailabilityStateChangedEventArgs>
    {
        template <typename D> using type = consume_Windows_Security_DataProtection_IUserDataAvailabilityStateChangedEventArgs<D>;
    };
    template <typename D>
    struct consume_Windows_Security_DataProtection_IUserDataBufferUnprotectResult
    {
        [[nodiscard]] WINRT_IMPL_AUTO(winrt::Windows::Security::DataProtection::UserDataBufferUnprotectStatus) Status() const;
        [[nodiscard]] WINRT_IMPL_AUTO(winrt::Windows::Storage::Streams::IBuffer) UnprotectedBuffer() const;
    };
    template <> struct consume<winrt::Windows::Security::DataProtection::IUserDataBufferUnprotectResult>
    {
        template <typename D> using type = consume_Windows_Security_DataProtection_IUserDataBufferUnprotectResult<D>;
    };
    template <typename D>
    struct consume_Windows_Security_DataProtection_IUserDataProtectionManager
    {
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionStatus>) ProtectStorageItemAsync(winrt::Windows::Storage::IStorageItem const& storageItem, winrt::Windows::Security::DataProtection::UserDataAvailability const& availability) const;
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Security::DataProtection::UserDataStorageItemProtectionInfo>) GetStorageItemProtectionInfoAsync(winrt::Windows::Storage::IStorageItem const& storageItem) const;
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::Streams::IBuffer>) ProtectBufferAsync(winrt::Windows::Storage::Streams::IBuffer const& unprotectedBuffer, winrt::Windows::Security::DataProtection::UserDataAvailability const& availability) const;
        WINRT_IMPL_AUTO(winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Security::DataProtection::UserDataBufferUnprotectResult>) UnprotectBufferAsync(winrt::Windows::Storage::Streams::IBuffer const& protectedBuffer) const;
        WINRT_IMPL_AUTO(bool) IsContinuedDataAvailabilityExpected(winrt::Windows::Security::DataProtection::UserDataAvailability const& availability) const;
        WINRT_IMPL_AUTO(winrt::event_token) DataAvailabilityStateChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Security::DataProtection::UserDataProtectionManager, winrt::Windows::Security::DataProtection::UserDataAvailabilityStateChangedEventArgs> const& handler) const;
        using DataAvailabilityStateChanged_revoker = impl::event_revoker<winrt::Windows::Security::DataProtection::IUserDataProtectionManager, &impl::abi_t<winrt::Windows::Security::DataProtection::IUserDataProtectionManager>::remove_DataAvailabilityStateChanged>;
        [[nodiscard]] DataAvailabilityStateChanged_revoker DataAvailabilityStateChanged(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Security::DataProtection::UserDataProtectionManager, winrt::Windows::Security::DataProtection::UserDataAvailabilityStateChangedEventArgs> const& handler) const;
        WINRT_IMPL_AUTO(void) DataAvailabilityStateChanged(winrt::event_token const& token) const noexcept;
    };
    template <> struct consume<winrt::Windows::Security::DataProtection::IUserDataProtectionManager>
    {
        template <typename D> using type = consume_Windows_Security_DataProtection_IUserDataProtectionManager<D>;
    };
    template <typename D>
    struct consume_Windows_Security_DataProtection_IUserDataProtectionManagerStatics
    {
        WINRT_IMPL_AUTO(winrt::Windows::Security::DataProtection::UserDataProtectionManager) TryGetDefault() const;
        WINRT_IMPL_AUTO(winrt::Windows::Security::DataProtection::UserDataProtectionManager) TryGetForUser(winrt::Windows::System::User const& user) const;
    };
    template <> struct consume<winrt::Windows::Security::DataProtection::IUserDataProtectionManagerStatics>
    {
        template <typename D> using type = consume_Windows_Security_DataProtection_IUserDataProtectionManagerStatics<D>;
    };
    template <typename D>
    struct consume_Windows_Security_DataProtection_IUserDataStorageItemProtectionInfo
    {
        [[nodiscard]] WINRT_IMPL_AUTO(winrt::Windows::Security::DataProtection::UserDataAvailability) Availability() const;
    };
    template <> struct consume<winrt::Windows::Security::DataProtection::IUserDataStorageItemProtectionInfo>
    {
        template <typename D> using type = consume_Windows_Security_DataProtection_IUserDataStorageItemProtectionInfo<D>;
    };
}
#endif
