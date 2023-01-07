#include <src/Main/DotNETGlobal.hpp>
#include <llapi/utils/Hash.h>
#include <functional>
#include <variant>
#include "type_traits.hpp"

namespace LiteLoader::NET
{
    public interface class IFunctionCaller
    {
        void Release();
    };
}

namespace LiteLoader::NET::callback {

    namespace detail {

        constexpr bool _Managed = true;
        constexpr bool _Native = true;



        using IFunctionCaller = LiteLoader::NET::IFunctionCaller;



        template<class _First, class _Second>
        value struct _MyPair {
            _First first;
            _Second second;
        };



        template<bool _Allow_delegate, typename _Ret, typename... _Types>
        value struct _Func_def;

        template<typename _Ret, typename... _Types>
        value struct _Func_def <false, _Ret, _Types...> {
            typedef _Ret(*_Func_ptr)(_Types...);
        };

        template<typename _Ret, typename... _Types>
        value struct _Func_def<true, _Ret, _Types...> {
            typedef _Ret(*_Func_ptr)(_Types...);
            delegate _Ret _Func_del(_Types...);
        };



        template<bool _Allow_delegate, typename _Field_func>
        struct _Get_func_def {
            static_assert(std::_Always_false<_Field_func>, "only accept function types.");
        };

        template<bool _Allow_delegate, typename _Ret, typename... _Types>
        struct _Get_func_def<_Allow_delegate, _Ret __cdecl(_Types...)> {
            using type = _Func_def<_Allow_delegate, _Ret, _Types...>;
        };

        template<bool _Allow_delegate, typename _Ret, typename... _Types>
        struct _Get_func_def<_Allow_delegate, _Ret __clrcall(_Types...)> {
            using type = _Func_def<_Allow_delegate, _Ret, _Types...>;
        };



        template<bool _Allow_delegate, typename _Add, typename _Ret, typename... _Types>
        value struct _Add_param_func_def;

        template<typename _Add, typename _Ret, typename... _Types>
        value struct _Add_param_func_def <false, _Add, _Ret, _Types...> {
            typedef _Ret(*_Func_ptr)(_Add, _Types...);
        };

        template<typename _Add, typename _Ret, typename... _Types>
        value struct _Add_param_func_def<true, _Add, _Ret, _Types...> {
            typedef _Ret(*_Func_ptr)(_Add, _Types...);
            delegate _Ret _Func_del(_Add, _Types...);
        };



        template<bool _Allow_delegate, typename _Field_func, typename _Add>
        struct _Get_param_added_func_def {
            static_assert(std::_Always_false<_Field_func>, "only accept function types.");
        };

        template<bool _Allow_delegate, typename _Ret, typename... _Types, typename _Add>
        struct _Get_param_added_func_def<_Allow_delegate, _Ret __cdecl(_Types...), _Add> {
            using type = _Add_param_func_def<_Allow_delegate, _Add, _Ret, _Types...>;
        };

        template<bool _Allow_delegate, typename _Ret, typename... _Types, typename _Add>
        struct _Get_param_added_func_def<_Allow_delegate, _Ret __clrcall(_Types...), _Add> {
            using type = _Add_param_func_def<_Allow_delegate, _Add, _Ret, _Types...>;
        };



        template<bool _Is_managed, bool _Use_std_function, typename _Field_func, typename _Ret, typename... _Types>
        value struct _Func_caller;

        template<typename _Field_func, typename _Ret, typename... _Types>
        value struct _Func_caller<true, false, _Field_func, _Ret, _Types...>
            :IFunctionCaller {

            _Field_func^ func;
            _Ret(*_invoke_func)(_Field_func^, _Types...);
            GCHandle gch;

            _Ret _invoke(_Types... args) {
                return _invoke_func(func, args...);
            }

            virtual void Release() {
                if (gch.IsAllocated) {
                    gch.Free();
                }
                func = nullptr;
                _invoke_func = nullptr;
            }
        };

        template<typename _Field_func, typename _Ret, typename... _Types>
        value struct _Func_caller<false, false, _Field_func, _Ret, _Types...>
            :IFunctionCaller {

            _Field_func func;
            _Ret(*_invoke_func)(_Field_func, _Types...);

            _Ret _invoke(_Types... args) {
                return _invoke_func(func, args...);
            }

            virtual void Release() {
                func = nullptr;
                _invoke_func = nullptr;
            }
        };

        template<typename _Field_func, typename _Ret, typename... _Types>
        value struct _Func_caller<false, true, _Field_func, _Ret, _Types...>
            :IFunctionCaller {

            using _Std_func_type = std::function<typename std::remove_pointer_t<_Field_func>>;

            _Std_func_type* func;
            _Ret(*_invoke_func)(_Std_func_type*, _Types...);
            bool ownsInstance;

            _Ret _invoke(_Types... args) {
                return _invoke_func(func, args...);
            }

            virtual void Release() {
                if (ownsInstance)
                    delete func;

                func = nullptr;
                _invoke_func = nullptr;
            }
        };

        template<bool _Is_managed, bool _Use_std_function, typename _Field_func, typename _Fty1>
        struct _Get_func_caller {
            static_assert(std::_Always_false<_Field_func>, "only accept function types.");
        };

        template<bool _Is_managed, bool _Use_std_function, typename _Field_func, typename _Ret, typename... _Types>
        struct _Get_func_caller<_Is_managed, _Use_std_function, _Field_func, _Ret __cdecl(_Types...)> {
            using type = _Func_caller<_Is_managed, _Use_std_function, _Field_func, _Ret, _Types...>;
        };

        template<bool _Is_managed, bool _Use_std_function, typename _Field_func, typename _Ret, typename... _Types>
        struct _Get_func_caller<_Is_managed, _Use_std_function, _Field_func, _Ret __clrcall(_Types...)> {
            using type = _Func_caller<_Is_managed, _Use_std_function, _Field_func, _Ret, _Types...>;
        };


        template<typename _Fty1, typename _Fty2, typename _Dty>
        struct _Managed_to_native_func_marshaler {
            static_assert(is_delegate_v<_Dty>, "_TDelegate only accept delegate types.");
        public:
            using func_def = typename _Get_func_def<true, _Fty1>::type;
            using invoke_func_def = typename _Get_param_added_func_def<false, _Fty1, _Dty^>::type;

            using _Native_pfunc_type = typename func_def::_Func_ptr;
            using _Native_delegate_type = typename func_def::_Func_del;
            using _Native_invoke_pfunc_type = typename invoke_func_def::_Func_ptr;

            using _Managed_func_caller = typename _Get_func_caller<true, false, _Dty, _Fty1>::type;

            inline static _MyPair<_Native_pfunc_type, _Managed_func_caller> _create(_Dty^ func, _Native_invoke_pfunc_type fptr) {
                if (fptr == nullptr)
                    throw gcnew System::NullReferenceException("Template arg <fptr> can not be null.");

                _Managed_func_caller caller{};
                caller.func = func;
                caller._invoke_func = fptr;

                auto _native_invoke_delfunc = gcnew _Native_delegate_type(caller, &_Managed_func_caller::_invoke);
                caller.gch = GCHandle::Alloc(_native_invoke_delfunc);

                auto _native_invoke_pfunc = static_cast<_Native_pfunc_type>(
                    Marshal::GetFunctionPointerForDelegate(_native_invoke_delfunc).ToPointer());

                _MyPair<_Native_pfunc_type, _Managed_func_caller> ret;

                ret.first = _native_invoke_pfunc;
                ret.second = caller;

                return ret;
            }
            template<_Native_invoke_pfunc_type fptr>
            inline static _MyPair<_Native_pfunc_type, _Managed_func_caller> _create(_Dty^ func) {
                return _create(func, fptr);
            }
        };

        template<typename _Fty1, typename _Fty2, typename _Dty>
        struct _Native_to_managed_func_marshaler {
            static_assert(is_delegate_v<_Dty>, "_TDelegate only accept delegate types.");
        public:
            using func_def = typename _Get_func_def<true, _Fty1>::type;

            using _Native_pfunc_type = typename func_def::_Func_ptr;

            using invoke_func_def = typename _Get_param_added_func_def<false, _Fty2, _Native_pfunc_type>::type;

            using _Native_delegate_type = typename func_def::_Func_del;
            using _Managed_invoke_pfunc_type = typename invoke_func_def::_Func_ptr;

            using _Native_func_caller = typename _Get_func_caller<false, false, _Native_pfunc_type, _Fty2> ::type;

            static _MyPair<_Dty^, _Native_func_caller> _create(_Native_pfunc_type func, _Managed_invoke_pfunc_type fptr) {
                if (fptr == nullptr)
                    throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

                _Native_func_caller caller{};
                caller.func = func;
                caller._invoke_func = fptr;

                auto _managed_invoke_delfunc = gcnew _Dty(caller, &_Native_func_caller::_invoke);

                _MyPair<_Dty^, _Native_func_caller> ret;

                ret.first = _managed_invoke_delfunc;
                ret.second = caller;

                return ret;
            }
            template<_Managed_invoke_pfunc_type fptr>
            static _MyPair<_Dty^, _Native_func_caller> _create(_Native_pfunc_type func) {
                return _create(func, fptr);
            }
        };

        template<typename _Fty1, typename _Fty2, typename _Dty>
        struct _Native_to_managed_func_marshaler_std_function {
            static_assert(is_delegate_v<_Dty>, "_TDelegate only accept delegate types.");
        public:
            using func_def = typename _Get_func_def<true, _Fty1>::type;
            using _Native_pfunc_type = typename func_def::_Func_ptr;
            using _Std_function_type = typename std::function<typename std::remove_pointer_t<_Native_pfunc_type>>;
            using invoke_func_def = typename _Get_param_added_func_def<false, _Fty2, _Std_function_type*>::type;

            using _Native_delegate_type = typename func_def::_Func_del;
            using _Managed_invoke_pfunc_type = typename invoke_func_def::_Func_ptr;

            using _Native_func_caller = typename _Get_func_caller<false, true, _Native_pfunc_type, _Fty2> ::type;

            static _MyPair<_Dty^, _Native_func_caller> _create(_Std_function_type&& func, _Managed_invoke_pfunc_type fptr) {
                if (fptr == nullptr)
                    throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

                _Native_func_caller caller{};
                caller.ownsInstance = true;
                caller.func = new _Std_function_type(func);
                caller._invoke_func = fptr;

                auto _managed_invoke_delfunc = gcnew _Dty(caller, &_Native_func_caller::_invoke);

                _MyPair<_Dty^, _Native_func_caller> ret;

                ret.first = _managed_invoke_delfunc;
                ret.second = caller;

                return ret;
            }
            template<_Managed_invoke_pfunc_type fptr>
            static _MyPair<_Dty^, _Native_func_caller> _create(_Std_function_type&& func) {
                return _create(std::forward(func), fptr);
            }

            static _MyPair<_Dty^, _Native_func_caller> _create(_Std_function_type const& func, _Managed_invoke_pfunc_type fptr) {
                if (fptr == nullptr)
                    throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

                _Native_func_caller caller{};
                caller.ownsInstance = false;
                caller.func = &const_cast<_Std_function_type&>(func);
                caller._invoke_func = fptr;

                auto _managed_invoke_delfunc = gcnew _Dty(caller, &_Native_func_caller::_invoke);

                _MyPair<_Dty^, _Native_func_caller> ret;

                ret.first = _managed_invoke_delfunc;
                ret.second = caller;

                return ret;
            }
            template<_Managed_invoke_pfunc_type fptr>
            static _MyPair<_Dty^, _Native_func_caller> _create(_Std_function_type const& func) {
                return _create(func, fptr);
            }
        };
    }

    template<typename _Fty1, typename _Fty2, typename _TDelegate>
    value struct converter {
    public:
        using _Managed_to_native = typename detail::_Managed_to_native_func_marshaler<_Fty1, _Fty2, _TDelegate>;
        using _Native_to_managed = typename detail::_Native_to_managed_func_marshaler<_Fty1, _Fty2, _TDelegate>;
        using _Native_to_managed_std_function = typename detail::_Native_to_managed_func_marshaler_std_function<_Fty1, _Fty2, _TDelegate>;

        using _Native_pfunc_type = typename _Managed_to_native::_Native_pfunc_type;
        using _Std_func_type = typename _Native_to_managed_std_function::_Std_function_type;

        using _Managed_func_caller = typename _Managed_to_native::_Managed_func_caller;
        using _Native_func_caller = typename _Native_to_managed::_Native_func_caller;
        using _Std_func_caller = typename _Native_to_managed_std_function::_Native_func_caller;

        using _Native_invoke_pfunc_type = typename _Managed_to_native::_Native_invoke_pfunc_type;
        using _Managed_invoke_pfunc_type = typename _Native_to_managed::_Managed_invoke_pfunc_type;
        using _Managed_invoke_pfunc_type_std_function = typename _Native_to_managed_std_function::_Managed_invoke_pfunc_type;

        template<_Native_invoke_pfunc_type fptr>
        static detail::_MyPair<_Native_pfunc_type, _Managed_func_caller> create(_TDelegate^ func) {
            return _Managed_to_native::_create<fptr>(func);
        }

        template<_Managed_invoke_pfunc_type fptr>
        static detail::_MyPair<_TDelegate^, _Native_func_caller> create(_Native_pfunc_type func) {
            return _Native_to_managed::_create<fptr>(func);
        }

        static detail::_MyPair<_Native_pfunc_type, _Managed_func_caller> create(_TDelegate^ func, _Native_invoke_pfunc_type fptr) {
            return _Managed_to_native::_create(func, fptr);
        }

        static detail::_MyPair<_TDelegate^, _Native_func_caller> create(_Native_pfunc_type func, _Managed_invoke_pfunc_type fptr) {
            return _Native_to_managed::_create(func, fptr);
        }

        template<_Managed_invoke_pfunc_type_std_function fptr>
        static detail::_MyPair<_TDelegate^, _Std_func_caller> create(_Std_func_type&& func) {
            return _Native_to_managed_std_function::_create<fptr>(std::forward(func));
        }

        static detail::_MyPair<_TDelegate^, _Std_func_caller> create(_Std_func_type&& func, _Managed_invoke_pfunc_type_std_function fptr) {
            return _Native_to_managed_std_function::_create(std::forward(func), fptr);
        }

        template<_Managed_invoke_pfunc_type_std_function fptr>
        static detail::_MyPair<_TDelegate^, _Std_func_caller> create(_Std_func_type const& func) {
            return _Native_to_managed_std_function::_create<fptr>(func);
        }

        static detail::_MyPair<_TDelegate^, _Std_func_caller> create(_Std_func_type const& func, _Managed_invoke_pfunc_type_std_function fptr) {
            return _Native_to_managed_std_function::_create(func, fptr);
        }

    };


}
