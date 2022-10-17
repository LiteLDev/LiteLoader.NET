#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <llapi/utils/Hash.h>
#include <functional>
#include <variant>
#include "type_traits.hpp"

namespace llnet::callback {

	//template<typename _Tx>
	//struct _Get_func_impl {

	//};

	//template<typename _Ret, typename... _Types>
	//struct _Get_func_impl<_Ret(_Types...)> {
	//	using result_type = _Ret;
	//	template<size_t _Index> struct arg {
	//		using type = std::tuple_element<_Index, std::tuple<_Types...>>::type;
	//	};
	//	template<size_t _Index>using arg_t = arg<_Index>::type;
	//};

	namespace detail {

		public interface class IFunctionCaller {
			void Release();
		};

		template<class _First, class _Second>
		value struct _MyPair {
			_First first;
			_Second second;
		};

		template<typename _Dty, typename _Ret, typename... _Types>
		value struct _Managed2native_func_marshaler {
			static_assert(is_delegate_v<_Dty>, "_TDelegate only accept delegate types.");
		public:
			typedef _Ret(*_Native_pfunc_type)(_Types...);
			delegate _Ret _Native_delegate_type(_Types...);

			typedef _Ret(__clrcall* _Native_cast_args_pfunc_type)(Object^, _Types...);

			value struct _Managed_func_caller
				:IFunctionCaller {
				_Dty^ func;
				property _Native_cast_args_pfunc_type _invoke_func;
				GCHandle gch;

				_Ret _invoke(_Types... args) {
					return _invoke_func(func, args...);
				}

				void Release() override {
					if (gch.IsAllocated)
						gch.Free();
				}
			};

			template<_Native_cast_args_pfunc_type fptr>
			inline static _MyPair<_Native_pfunc_type, _Managed_func_caller> _create(_Dty^ func) {
				if constexpr (fptr == nullptr)
					throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

				_Managed_func_caller caller{};
				caller.func = func;
				caller._invoke_func = fptr;

				auto _native_invoke_delfunc = gcnew _Native_delegate_type(caller, &_Managed_func_caller::_invoke);
				caller.gch = GCHandle::Alloc(_native_invoke_delfunc);

				auto _native_invoke_pfunc = static_cast<_Native_pfunc_type>(
					(void*)Marshal::GetFunctionPointerForDelegate(_native_invoke_delfunc));

				return _MyPair<_Native_pfunc_type, _Managed_func_caller>{_native_invoke_pfunc, caller};
			}

		};

		template<typename _Dty, typename _Fty>
		struct _Get_func_impl_m2n {
			static_assert(std::_Always_false<_Fty>);
		};

		template<typename _Dty, typename _Ret, typename... _Types>
		struct _Get_func_impl_m2n<_Dty, _Ret(_Types...)> {
			using type = _Managed2native_func_marshaler<_Dty, _Ret, _Types...>;
		};

		template<typename _Dty, typename _Ret, typename... _Types>
		value struct _Native2managed_func_marshaler {
			static_assert(is_delegate_v<_Dty>, "_TDelegate only accept delegate types.");
		public:
			typedef _Ret(*_Native_pfunc_type)(_Types...);
			delegate _Ret _Native_delegate_type(_Types...);

			typedef _Ret(__clrcall* _Managed_cast_args_pfunc_type)(void*, _Types...);

			value struct _Native_func_caller
				:IFunctionCaller {
				_Native_pfunc_type func;
				property _Managed_cast_args_pfunc_type _invoke_func;
				/*GCHandle gch;*/    //no GCHandle

				_Ret _invoke(_Types... args) {
					return _invoke_func(func, args...);
				}

				void Release() {
					//nothing...
				}
			};

			template<_Managed_cast_args_pfunc_type fptr>
			static _MyPair<_Dty^, _Native_func_caller> create(_Native_pfunc_type func) {
				if constexpr (fptr == nullptr)
					throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

				_Native_func_caller caller{};
				caller.func = func;
				caller._invoke_func = fptr;

				auto _managed_invoke_delfunc = gcnew _TDelegate(caller, &_Native_func_caller::_invoke);

				return _MyPair<_Dty^, _Native_func_caller>{_managed_invoke_delfunc, caller};
			}
		};

		//template<typename _Dty, typename _Fty>
		//struct _Get_func_impl_n2m {
		//	static_assert(std::_Always_false<_Fty>);
		//};

		//template<typename _Dty, typename _Ret, typename... _Types>
		//struct _Get_func_impl_n2m<_Dty, _Ret(_Types...)> {
		//	using type = _Native2managed_func_marshaler<_Dty, _Ret, _Types...>;
		//};

	}

	template<typename _Fty1, typename _TDelegate, typename _Ret, typename... _Types>
	value struct converter {
	private:
		using _Managed_to_native = typename detail::_Get_func_impl_m2n<_TDelegate, _Fty1>::type;
		using _Native_to_managed = typename detail::_Native2managed_func_marshaler<_TDelegate, _Ret, _Types...>;

		using _Native_pfunc_type = typename _Managed_to_native::_Native_pfunc_type;

		using _Managed_func_caller = typename _Managed_to_native::_Managed_func_caller;
		using _Native_func_caller = typename _Native_to_managed::_Native_func_caller;

		using _Native_cast_args_pfunc_type = typename _Managed_to_native::_Native_cast_args_pfunc_type;
		using _Managed_cast_args_pfunc_type = typename _Native_to_managed::_Managed_cast_args_pfunc_type;

	public:

		template<_Native_cast_args_pfunc_type fptr>
		static detail::_MyPair<_Native_pfunc_type, _Managed_func_caller> create(_TDelegate^ func) {
			return _Managed_to_native::_create<fptr>(func);
		}

		template<_Managed_cast_args_pfunc_type fptr>
		static detail::_MyPair<_TDelegate^, _Native_func_caller> create(_Native_pfunc_type func) {
			return _Native_to_managed::_create<fptr>(func);
		}
	};
}