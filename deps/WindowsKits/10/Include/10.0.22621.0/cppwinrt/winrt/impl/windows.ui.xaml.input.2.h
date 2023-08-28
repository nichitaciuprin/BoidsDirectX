// C++/WinRT v2.0.220110.5

// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once
#ifndef WINRT_Windows_UI_Xaml_Input_2_H
#define WINRT_Windows_UI_Xaml_Input_2_H
#include "winrt/impl/Windows.Foundation.1.h"
#include "winrt/impl/Windows.UI.Xaml.1.h"
#include "winrt/impl/Windows.UI.Xaml.Input.1.h"
WINRT_EXPORT namespace winrt::Windows::UI::Xaml::Input
{
    struct DoubleTappedEventHandler : winrt::Windows::Foundation::IUnknown
    {
        DoubleTappedEventHandler(std::nullptr_t = nullptr) noexcept {}
        DoubleTappedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> DoubleTappedEventHandler(L lambda);
        template <typename F> DoubleTappedEventHandler(F* function);
        template <typename O, typename M> DoubleTappedEventHandler(O* object, M method);
        template <typename O, typename M> DoubleTappedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> DoubleTappedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::DoubleTappedRoutedEventArgs const& e) const;
    };
    struct HoldingEventHandler : winrt::Windows::Foundation::IUnknown
    {
        HoldingEventHandler(std::nullptr_t = nullptr) noexcept {}
        HoldingEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> HoldingEventHandler(L lambda);
        template <typename F> HoldingEventHandler(F* function);
        template <typename O, typename M> HoldingEventHandler(O* object, M method);
        template <typename O, typename M> HoldingEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> HoldingEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::HoldingRoutedEventArgs const& e) const;
    };
    struct KeyEventHandler : winrt::Windows::Foundation::IUnknown
    {
        KeyEventHandler(std::nullptr_t = nullptr) noexcept {}
        KeyEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> KeyEventHandler(L lambda);
        template <typename F> KeyEventHandler(F* function);
        template <typename O, typename M> KeyEventHandler(O* object, M method);
        template <typename O, typename M> KeyEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> KeyEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::KeyRoutedEventArgs const& e) const;
    };
    struct ManipulationCompletedEventHandler : winrt::Windows::Foundation::IUnknown
    {
        ManipulationCompletedEventHandler(std::nullptr_t = nullptr) noexcept {}
        ManipulationCompletedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> ManipulationCompletedEventHandler(L lambda);
        template <typename F> ManipulationCompletedEventHandler(F* function);
        template <typename O, typename M> ManipulationCompletedEventHandler(O* object, M method);
        template <typename O, typename M> ManipulationCompletedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> ManipulationCompletedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::ManipulationCompletedRoutedEventArgs const& e) const;
    };
    struct ManipulationDeltaEventHandler : winrt::Windows::Foundation::IUnknown
    {
        ManipulationDeltaEventHandler(std::nullptr_t = nullptr) noexcept {}
        ManipulationDeltaEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> ManipulationDeltaEventHandler(L lambda);
        template <typename F> ManipulationDeltaEventHandler(F* function);
        template <typename O, typename M> ManipulationDeltaEventHandler(O* object, M method);
        template <typename O, typename M> ManipulationDeltaEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> ManipulationDeltaEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs const& e) const;
    };
    struct ManipulationInertiaStartingEventHandler : winrt::Windows::Foundation::IUnknown
    {
        ManipulationInertiaStartingEventHandler(std::nullptr_t = nullptr) noexcept {}
        ManipulationInertiaStartingEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> ManipulationInertiaStartingEventHandler(L lambda);
        template <typename F> ManipulationInertiaStartingEventHandler(F* function);
        template <typename O, typename M> ManipulationInertiaStartingEventHandler(O* object, M method);
        template <typename O, typename M> ManipulationInertiaStartingEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> ManipulationInertiaStartingEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs const& e) const;
    };
    struct ManipulationStartedEventHandler : winrt::Windows::Foundation::IUnknown
    {
        ManipulationStartedEventHandler(std::nullptr_t = nullptr) noexcept {}
        ManipulationStartedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> ManipulationStartedEventHandler(L lambda);
        template <typename F> ManipulationStartedEventHandler(F* function);
        template <typename O, typename M> ManipulationStartedEventHandler(O* object, M method);
        template <typename O, typename M> ManipulationStartedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> ManipulationStartedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs const& e) const;
    };
    struct ManipulationStartingEventHandler : winrt::Windows::Foundation::IUnknown
    {
        ManipulationStartingEventHandler(std::nullptr_t = nullptr) noexcept {}
        ManipulationStartingEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> ManipulationStartingEventHandler(L lambda);
        template <typename F> ManipulationStartingEventHandler(F* function);
        template <typename O, typename M> ManipulationStartingEventHandler(O* object, M method);
        template <typename O, typename M> ManipulationStartingEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> ManipulationStartingEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::ManipulationStartingRoutedEventArgs const& e) const;
    };
    struct PointerEventHandler : winrt::Windows::Foundation::IUnknown
    {
        PointerEventHandler(std::nullptr_t = nullptr) noexcept {}
        PointerEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> PointerEventHandler(L lambda);
        template <typename F> PointerEventHandler(F* function);
        template <typename O, typename M> PointerEventHandler(O* object, M method);
        template <typename O, typename M> PointerEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> PointerEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e) const;
    };
    struct RightTappedEventHandler : winrt::Windows::Foundation::IUnknown
    {
        RightTappedEventHandler(std::nullptr_t = nullptr) noexcept {}
        RightTappedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> RightTappedEventHandler(L lambda);
        template <typename F> RightTappedEventHandler(F* function);
        template <typename O, typename M> RightTappedEventHandler(O* object, M method);
        template <typename O, typename M> RightTappedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> RightTappedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::RightTappedRoutedEventArgs const& e) const;
    };
    struct TappedEventHandler : winrt::Windows::Foundation::IUnknown
    {
        TappedEventHandler(std::nullptr_t = nullptr) noexcept {}
        TappedEventHandler(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::Foundation::IUnknown(ptr, take_ownership_from_abi) {}
        template <typename L> TappedEventHandler(L lambda);
        template <typename F> TappedEventHandler(F* function);
        template <typename O, typename M> TappedEventHandler(O* object, M method);
        template <typename O, typename M> TappedEventHandler(com_ptr<O>&& object, M method);
        template <typename O, typename M> TappedEventHandler(weak_ref<O>&& object, M method);
        auto operator()(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const& e) const;
    };
    struct __declspec(empty_bases) AccessKeyDisplayDismissedEventArgs : winrt::Windows::UI::Xaml::Input::IAccessKeyDisplayDismissedEventArgs
    {
        AccessKeyDisplayDismissedEventArgs(std::nullptr_t) noexcept {}
        AccessKeyDisplayDismissedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IAccessKeyDisplayDismissedEventArgs(ptr, take_ownership_from_abi) {}
        AccessKeyDisplayDismissedEventArgs();
    };
    struct __declspec(empty_bases) AccessKeyDisplayRequestedEventArgs : winrt::Windows::UI::Xaml::Input::IAccessKeyDisplayRequestedEventArgs
    {
        AccessKeyDisplayRequestedEventArgs(std::nullptr_t) noexcept {}
        AccessKeyDisplayRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IAccessKeyDisplayRequestedEventArgs(ptr, take_ownership_from_abi) {}
        AccessKeyDisplayRequestedEventArgs();
    };
    struct __declspec(empty_bases) AccessKeyInvokedEventArgs : winrt::Windows::UI::Xaml::Input::IAccessKeyInvokedEventArgs
    {
        AccessKeyInvokedEventArgs(std::nullptr_t) noexcept {}
        AccessKeyInvokedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IAccessKeyInvokedEventArgs(ptr, take_ownership_from_abi) {}
        AccessKeyInvokedEventArgs();
    };
    struct __declspec(empty_bases) AccessKeyManager : winrt::Windows::UI::Xaml::Input::IAccessKeyManager
    {
        AccessKeyManager(std::nullptr_t) noexcept {}
        AccessKeyManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IAccessKeyManager(ptr, take_ownership_from_abi) {}
        [[nodiscard]] static auto IsDisplayModeEnabled();
        static auto IsDisplayModeEnabledChanged(winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& handler);
        using IsDisplayModeEnabledChanged_revoker = impl::factory_event_revoker<winrt::Windows::UI::Xaml::Input::IAccessKeyManagerStatics, &impl::abi_t<winrt::Windows::UI::Xaml::Input::IAccessKeyManagerStatics>::remove_IsDisplayModeEnabledChanged>;
        [[nodiscard]] static IsDisplayModeEnabledChanged_revoker IsDisplayModeEnabledChanged(auto_revoke_t, winrt::Windows::Foundation::TypedEventHandler<winrt::Windows::Foundation::IInspectable, winrt::Windows::Foundation::IInspectable> const& handler);
        static auto IsDisplayModeEnabledChanged(winrt::event_token const& token);
        static auto ExitDisplayMode();
        [[nodiscard]] static auto AreKeyTipsEnabled();
        static auto AreKeyTipsEnabled(bool value);
    };
    struct __declspec(empty_bases) CanExecuteRequestedEventArgs : winrt::Windows::UI::Xaml::Input::ICanExecuteRequestedEventArgs
    {
        CanExecuteRequestedEventArgs(std::nullptr_t) noexcept {}
        CanExecuteRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::ICanExecuteRequestedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) CharacterReceivedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::ICharacterReceivedRoutedEventArgs,
        impl::base<CharacterReceivedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<CharacterReceivedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        CharacterReceivedRoutedEventArgs(std::nullptr_t) noexcept {}
        CharacterReceivedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::ICharacterReceivedRoutedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) ContextRequestedEventArgs : winrt::Windows::UI::Xaml::Input::IContextRequestedEventArgs,
        impl::base<ContextRequestedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ContextRequestedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ContextRequestedEventArgs(std::nullptr_t) noexcept {}
        ContextRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IContextRequestedEventArgs(ptr, take_ownership_from_abi) {}
        ContextRequestedEventArgs();
    };
    struct __declspec(empty_bases) DoubleTappedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IDoubleTappedRoutedEventArgs,
        impl::base<DoubleTappedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<DoubleTappedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        DoubleTappedRoutedEventArgs(std::nullptr_t) noexcept {}
        DoubleTappedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IDoubleTappedRoutedEventArgs(ptr, take_ownership_from_abi) {}
        DoubleTappedRoutedEventArgs();
    };
    struct __declspec(empty_bases) ExecuteRequestedEventArgs : winrt::Windows::UI::Xaml::Input::IExecuteRequestedEventArgs
    {
        ExecuteRequestedEventArgs(std::nullptr_t) noexcept {}
        ExecuteRequestedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IExecuteRequestedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) FindNextElementOptions : winrt::Windows::UI::Xaml::Input::IFindNextElementOptions
    {
        FindNextElementOptions(std::nullptr_t) noexcept {}
        FindNextElementOptions(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IFindNextElementOptions(ptr, take_ownership_from_abi) {}
        FindNextElementOptions();
    };
    struct __declspec(empty_bases) FocusManager : winrt::Windows::UI::Xaml::Input::IFocusManager
    {
        FocusManager(std::nullptr_t) noexcept {}
        FocusManager(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IFocusManager(ptr, take_ownership_from_abi) {}
        static auto GetFocusedElement();
        static auto TryMoveFocus(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection);
        static auto FindNextFocusableElement(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection);
        static auto FindNextFocusableElement(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection, winrt::Windows::Foundation::Rect const& hintRect);
        static auto TryMoveFocus(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection, winrt::Windows::UI::Xaml::Input::FindNextElementOptions const& focusNavigationOptions);
        static auto FindNextElement(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection);
        static auto FindFirstFocusableElement(winrt::Windows::UI::Xaml::DependencyObject const& searchScope);
        static auto FindLastFocusableElement(winrt::Windows::UI::Xaml::DependencyObject const& searchScope);
        static auto FindNextElement(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection, winrt::Windows::UI::Xaml::Input::FindNextElementOptions const& focusNavigationOptions);
        static auto TryFocusAsync(winrt::Windows::UI::Xaml::DependencyObject const& element, winrt::Windows::UI::Xaml::FocusState const& value);
        static auto TryMoveFocusAsync(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection);
        static auto TryMoveFocusAsync(winrt::Windows::UI::Xaml::Input::FocusNavigationDirection const& focusNavigationDirection, winrt::Windows::UI::Xaml::Input::FindNextElementOptions const& focusNavigationOptions);
        static auto GotFocus(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::FocusManagerGotFocusEventArgs> const& handler);
        using GotFocus_revoker = impl::factory_event_revoker<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6, &impl::abi_t<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6>::remove_GotFocus>;
        [[nodiscard]] static GotFocus_revoker GotFocus(auto_revoke_t, winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::FocusManagerGotFocusEventArgs> const& handler);
        static auto GotFocus(winrt::event_token const& token);
        static auto LostFocus(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::FocusManagerLostFocusEventArgs> const& handler);
        using LostFocus_revoker = impl::factory_event_revoker<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6, &impl::abi_t<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6>::remove_LostFocus>;
        [[nodiscard]] static LostFocus_revoker LostFocus(auto_revoke_t, winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::FocusManagerLostFocusEventArgs> const& handler);
        static auto LostFocus(winrt::event_token const& token);
        static auto GettingFocus(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::GettingFocusEventArgs> const& handler);
        using GettingFocus_revoker = impl::factory_event_revoker<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6, &impl::abi_t<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6>::remove_GettingFocus>;
        [[nodiscard]] static GettingFocus_revoker GettingFocus(auto_revoke_t, winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::GettingFocusEventArgs> const& handler);
        static auto GettingFocus(winrt::event_token const& token);
        static auto LosingFocus(winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::LosingFocusEventArgs> const& handler);
        using LosingFocus_revoker = impl::factory_event_revoker<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6, &impl::abi_t<winrt::Windows::UI::Xaml::Input::IFocusManagerStatics6>::remove_LosingFocus>;
        [[nodiscard]] static LosingFocus_revoker LosingFocus(auto_revoke_t, winrt::Windows::Foundation::EventHandler<winrt::Windows::UI::Xaml::Input::LosingFocusEventArgs> const& handler);
        static auto LosingFocus(winrt::event_token const& token);
        static auto GetFocusedElement(winrt::Windows::UI::Xaml::XamlRoot const& xamlRoot);
    };
    struct __declspec(empty_bases) FocusManagerGotFocusEventArgs : winrt::Windows::UI::Xaml::Input::IFocusManagerGotFocusEventArgs
    {
        FocusManagerGotFocusEventArgs(std::nullptr_t) noexcept {}
        FocusManagerGotFocusEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IFocusManagerGotFocusEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) FocusManagerLostFocusEventArgs : winrt::Windows::UI::Xaml::Input::IFocusManagerLostFocusEventArgs
    {
        FocusManagerLostFocusEventArgs(std::nullptr_t) noexcept {}
        FocusManagerLostFocusEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IFocusManagerLostFocusEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) FocusMovementResult : winrt::Windows::UI::Xaml::Input::IFocusMovementResult
    {
        FocusMovementResult(std::nullptr_t) noexcept {}
        FocusMovementResult(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IFocusMovementResult(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) GettingFocusEventArgs : winrt::Windows::UI::Xaml::Input::IGettingFocusEventArgs,
        impl::base<GettingFocusEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<GettingFocusEventArgs, winrt::Windows::UI::Xaml::Input::IGettingFocusEventArgs2, winrt::Windows::UI::Xaml::Input::IGettingFocusEventArgs3, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        GettingFocusEventArgs(std::nullptr_t) noexcept {}
        GettingFocusEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IGettingFocusEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) HoldingRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IHoldingRoutedEventArgs,
        impl::base<HoldingRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<HoldingRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        HoldingRoutedEventArgs(std::nullptr_t) noexcept {}
        HoldingRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IHoldingRoutedEventArgs(ptr, take_ownership_from_abi) {}
        HoldingRoutedEventArgs();
    };
    struct __declspec(empty_bases) InertiaExpansionBehavior : winrt::Windows::UI::Xaml::Input::IInertiaExpansionBehavior
    {
        InertiaExpansionBehavior(std::nullptr_t) noexcept {}
        InertiaExpansionBehavior(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IInertiaExpansionBehavior(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) InertiaRotationBehavior : winrt::Windows::UI::Xaml::Input::IInertiaRotationBehavior
    {
        InertiaRotationBehavior(std::nullptr_t) noexcept {}
        InertiaRotationBehavior(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IInertiaRotationBehavior(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) InertiaTranslationBehavior : winrt::Windows::UI::Xaml::Input::IInertiaTranslationBehavior
    {
        InertiaTranslationBehavior(std::nullptr_t) noexcept {}
        InertiaTranslationBehavior(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IInertiaTranslationBehavior(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) InputScope : winrt::Windows::UI::Xaml::Input::IInputScope,
        impl::base<InputScope, winrt::Windows::UI::Xaml::DependencyObject>,
        impl::require<InputScope, winrt::Windows::UI::Xaml::IDependencyObject, winrt::Windows::UI::Xaml::IDependencyObject2>
    {
        InputScope(std::nullptr_t) noexcept {}
        InputScope(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IInputScope(ptr, take_ownership_from_abi) {}
        InputScope();
    };
    struct __declspec(empty_bases) InputScopeName : winrt::Windows::UI::Xaml::Input::IInputScopeName,
        impl::base<InputScopeName, winrt::Windows::UI::Xaml::DependencyObject>,
        impl::require<InputScopeName, winrt::Windows::UI::Xaml::IDependencyObject, winrt::Windows::UI::Xaml::IDependencyObject2>
    {
        InputScopeName(std::nullptr_t) noexcept {}
        InputScopeName(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IInputScopeName(ptr, take_ownership_from_abi) {}
        InputScopeName();
        explicit InputScopeName(winrt::Windows::UI::Xaml::Input::InputScopeNameValue const& nameValue);
    };
    struct __declspec(empty_bases) KeyRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IKeyRoutedEventArgs,
        impl::base<KeyRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<KeyRoutedEventArgs, winrt::Windows::UI::Xaml::Input::IKeyRoutedEventArgs2, winrt::Windows::UI::Xaml::Input::IKeyRoutedEventArgs3, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        KeyRoutedEventArgs(std::nullptr_t) noexcept {}
        KeyRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IKeyRoutedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) KeyboardAccelerator : winrt::Windows::UI::Xaml::Input::IKeyboardAccelerator,
        impl::base<KeyboardAccelerator, winrt::Windows::UI::Xaml::DependencyObject>,
        impl::require<KeyboardAccelerator, winrt::Windows::UI::Xaml::IDependencyObject, winrt::Windows::UI::Xaml::IDependencyObject2>
    {
        KeyboardAccelerator(std::nullptr_t) noexcept {}
        KeyboardAccelerator(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IKeyboardAccelerator(ptr, take_ownership_from_abi) {}
        KeyboardAccelerator();
        [[nodiscard]] static auto KeyProperty();
        [[nodiscard]] static auto ModifiersProperty();
        [[nodiscard]] static auto IsEnabledProperty();
        [[nodiscard]] static auto ScopeOwnerProperty();
    };
    struct __declspec(empty_bases) KeyboardAcceleratorInvokedEventArgs : winrt::Windows::UI::Xaml::Input::IKeyboardAcceleratorInvokedEventArgs,
        impl::require<KeyboardAcceleratorInvokedEventArgs, winrt::Windows::UI::Xaml::Input::IKeyboardAcceleratorInvokedEventArgs2>
    {
        KeyboardAcceleratorInvokedEventArgs(std::nullptr_t) noexcept {}
        KeyboardAcceleratorInvokedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IKeyboardAcceleratorInvokedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) LosingFocusEventArgs : winrt::Windows::UI::Xaml::Input::ILosingFocusEventArgs,
        impl::base<LosingFocusEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<LosingFocusEventArgs, winrt::Windows::UI::Xaml::Input::ILosingFocusEventArgs2, winrt::Windows::UI::Xaml::Input::ILosingFocusEventArgs3, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        LosingFocusEventArgs(std::nullptr_t) noexcept {}
        LosingFocusEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::ILosingFocusEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) ManipulationCompletedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IManipulationCompletedRoutedEventArgs,
        impl::base<ManipulationCompletedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ManipulationCompletedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ManipulationCompletedRoutedEventArgs(std::nullptr_t) noexcept {}
        ManipulationCompletedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationCompletedRoutedEventArgs(ptr, take_ownership_from_abi) {}
        ManipulationCompletedRoutedEventArgs();
    };
    struct __declspec(empty_bases) ManipulationDeltaRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IManipulationDeltaRoutedEventArgs,
        impl::base<ManipulationDeltaRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ManipulationDeltaRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ManipulationDeltaRoutedEventArgs(std::nullptr_t) noexcept {}
        ManipulationDeltaRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationDeltaRoutedEventArgs(ptr, take_ownership_from_abi) {}
        ManipulationDeltaRoutedEventArgs();
    };
    struct __declspec(empty_bases) ManipulationInertiaStartingRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IManipulationInertiaStartingRoutedEventArgs,
        impl::base<ManipulationInertiaStartingRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ManipulationInertiaStartingRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ManipulationInertiaStartingRoutedEventArgs(std::nullptr_t) noexcept {}
        ManipulationInertiaStartingRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationInertiaStartingRoutedEventArgs(ptr, take_ownership_from_abi) {}
        ManipulationInertiaStartingRoutedEventArgs();
    };
    struct __declspec(empty_bases) ManipulationPivot : winrt::Windows::UI::Xaml::Input::IManipulationPivot
    {
        ManipulationPivot(std::nullptr_t) noexcept {}
        ManipulationPivot(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationPivot(ptr, take_ownership_from_abi) {}
        ManipulationPivot();
        ManipulationPivot(winrt::Windows::Foundation::Point const& center, double radius);
    };
    struct __declspec(empty_bases) ManipulationStartedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IManipulationStartedRoutedEventArgs,
        impl::base<ManipulationStartedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ManipulationStartedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ManipulationStartedRoutedEventArgs(std::nullptr_t) noexcept {}
        ManipulationStartedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationStartedRoutedEventArgs(ptr, take_ownership_from_abi) {}
        ManipulationStartedRoutedEventArgs();
    };
    struct __declspec(empty_bases) ManipulationStartingRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IManipulationStartingRoutedEventArgs,
        impl::base<ManipulationStartingRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<ManipulationStartingRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        ManipulationStartingRoutedEventArgs(std::nullptr_t) noexcept {}
        ManipulationStartingRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IManipulationStartingRoutedEventArgs(ptr, take_ownership_from_abi) {}
        ManipulationStartingRoutedEventArgs();
    };
    struct __declspec(empty_bases) NoFocusCandidateFoundEventArgs : winrt::Windows::UI::Xaml::Input::INoFocusCandidateFoundEventArgs,
        impl::base<NoFocusCandidateFoundEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<NoFocusCandidateFoundEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        NoFocusCandidateFoundEventArgs(std::nullptr_t) noexcept {}
        NoFocusCandidateFoundEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::INoFocusCandidateFoundEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) Pointer : winrt::Windows::UI::Xaml::Input::IPointer
    {
        Pointer(std::nullptr_t) noexcept {}
        Pointer(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IPointer(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) PointerRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IPointerRoutedEventArgs,
        impl::base<PointerRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<PointerRoutedEventArgs, winrt::Windows::UI::Xaml::Input::IPointerRoutedEventArgs2, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        PointerRoutedEventArgs(std::nullptr_t) noexcept {}
        PointerRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IPointerRoutedEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) ProcessKeyboardAcceleratorEventArgs : winrt::Windows::UI::Xaml::Input::IProcessKeyboardAcceleratorEventArgs
    {
        ProcessKeyboardAcceleratorEventArgs(std::nullptr_t) noexcept {}
        ProcessKeyboardAcceleratorEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IProcessKeyboardAcceleratorEventArgs(ptr, take_ownership_from_abi) {}
    };
    struct __declspec(empty_bases) RightTappedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::IRightTappedRoutedEventArgs,
        impl::base<RightTappedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<RightTappedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        RightTappedRoutedEventArgs(std::nullptr_t) noexcept {}
        RightTappedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IRightTappedRoutedEventArgs(ptr, take_ownership_from_abi) {}
        RightTappedRoutedEventArgs();
    };
    struct __declspec(empty_bases) StandardUICommand : winrt::Windows::UI::Xaml::Input::IStandardUICommand,
        impl::base<StandardUICommand, winrt::Windows::UI::Xaml::Input::XamlUICommand, winrt::Windows::UI::Xaml::DependencyObject>,
        impl::require<StandardUICommand, winrt::Windows::UI::Xaml::Input::IStandardUICommand2, winrt::Windows::UI::Xaml::Input::IXamlUICommand, winrt::Windows::UI::Xaml::Input::ICommand, winrt::Windows::UI::Xaml::IDependencyObject, winrt::Windows::UI::Xaml::IDependencyObject2>
    {
        StandardUICommand(std::nullptr_t) noexcept {}
        StandardUICommand(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IStandardUICommand(ptr, take_ownership_from_abi) {}
        StandardUICommand();
        explicit StandardUICommand(winrt::Windows::UI::Xaml::Input::StandardUICommandKind const& kind);
        using winrt::Windows::UI::Xaml::Input::IStandardUICommand::Kind;
        using impl::consume_t<StandardUICommand, winrt::Windows::UI::Xaml::Input::IStandardUICommand2>::Kind;
        [[nodiscard]] static auto KindProperty();
    };
    struct __declspec(empty_bases) TappedRoutedEventArgs : winrt::Windows::UI::Xaml::Input::ITappedRoutedEventArgs,
        impl::base<TappedRoutedEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>,
        impl::require<TappedRoutedEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>
    {
        TappedRoutedEventArgs(std::nullptr_t) noexcept {}
        TappedRoutedEventArgs(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::ITappedRoutedEventArgs(ptr, take_ownership_from_abi) {}
        TappedRoutedEventArgs();
    };
    struct __declspec(empty_bases) XamlUICommand : winrt::Windows::UI::Xaml::Input::IXamlUICommand,
        impl::base<XamlUICommand, winrt::Windows::UI::Xaml::DependencyObject>,
        impl::require<XamlUICommand, winrt::Windows::UI::Xaml::Input::ICommand, winrt::Windows::UI::Xaml::IDependencyObject, winrt::Windows::UI::Xaml::IDependencyObject2>
    {
        XamlUICommand(std::nullptr_t) noexcept {}
        XamlUICommand(void* ptr, take_ownership_from_abi_t) noexcept : winrt::Windows::UI::Xaml::Input::IXamlUICommand(ptr, take_ownership_from_abi) {}
        XamlUICommand();
        [[nodiscard]] static auto LabelProperty();
        [[nodiscard]] static auto IconSourceProperty();
        [[nodiscard]] static auto KeyboardAcceleratorsProperty();
        [[nodiscard]] static auto AccessKeyProperty();
        [[nodiscard]] static auto DescriptionProperty();
        [[nodiscard]] static auto CommandProperty();
    };
}
#endif
