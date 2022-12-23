#pragma once
#include <type_traits>

namespace LiteLoader::NET
{
    template<class _Ty> struct remove_handle {
        using type = _Ty;
    };

    template<class _Ty> struct remove_handle<_Ty^> {
        using type = _Ty;
    };

    template<class _Ty> struct remove_handle<_Ty^ const> {
        using type = _Ty;
    };

    template<class _Ty>
    using remove_handle_t = typename remove_handle<_Ty>::type;

    template<class _Ty> struct is_delegate : std::bool_constant<__is_delegate(_Ty)> {
    };

    template <class _Ty>
    inline constexpr bool is_delegate_v = is_delegate<_Ty>::value;

    template<class _Ty> struct is_ref_class : std::bool_constant<__is_ref_class(_Ty)> {
    };

    template <class _Ty>
    inline constexpr bool is_ref_class_v = is_ref_class<_Ty>::value;

    template<class _Ty> struct is_value_class : std::bool_constant<__is_value_class(_Ty)> {
    };

    template <class _Ty>
    inline constexpr bool is_value_class_v = is_value_class<_Ty>::value;
}