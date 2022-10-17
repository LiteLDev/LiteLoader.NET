#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <llapi/utils/Hash.h>
#include <functional>
#include <variant>
#include "type_traits.hpp"

namespace llnet::callback {

	template<typename _Tx>
	struct _Get_func_impl {

	};

	template<typename _Ret, typename... _Types>
	struct _Get_func_impl<_Ret(_Types...)> {
		using result_type = _Ret;
		template<size_t _Index> struct arg {
			using type = std::tuple_element<_Index, std::tuple<_Types...>>::type;
		};
		template<size_t _Index>using arg_t = arg<_Index>::type;
	};

	template<typename _Fty1, typename _Fty2, typename _TDelegate>
	struct function_marshaler {

	};

	template<typename _Ret1, typename _Ret2, typename..._Types1, typename ..._Types2, typename _TDelegate>
	value struct function_marshaler<_Ret1(_Types1...), _Ret2(_Types2...), _TDelegate> {
		static_assert(is_delegate_v<_TDelegate>, "_TDelegate only accept delegate types.");

	protected:
		using _Func_impl_1 = _Get_func_impl<_Ret1(_Types1...)>;
		using _Func_impl_2 = _Get_func_impl<_Ret2(_Types2...)>;

	public:

		typedef _Ret1(*_Native_pfunc_type)(_Types1...);
		delegate _Ret1 _Native_delegate_type(_Types1...);

		typedef _Ret2(*_Managed_pfunc_type)(_Types2...);
		//delegate _Ret2 _Managed_delegate_type(_Types2...);    //equals to _TDelegate

		typedef _Ret1(*__Native_cast_args_pfunc_type)(Object^, _Types1...);
		typedef _Ret2(*__Managed_cast_args_pfunc_type)(void*, _Types2...);

	private:
		value struct _Managed_func_caller {
			_TDelegate^ func;
			property __Native_cast_args_pfunc_type _invoke_func;
			GCHandle gch;

			_Ret1 _invoke(_Types1&&... args) {
				_invoke_func(func, std::forward(args));
			}
		};

		value struct _Native_func_caller {
			_Native_pfunc_type func;
			property __Managed_cast_args_pfunc_type _invoke_func;
			/*GCHandle gch;*/    //no GCHandle

			_Ret2 _invoke(_Types2&&... args) {
				_invoke_func(func, std::forward(args));
			}
		};

	public:
		template<class _First, class _Second>
		value struct _MyPair {
			_First first;
			_Second second;
		};

	protected:
		template<bool _Is_managed>
		using _Select_func_type = std::conditional_t<_Is_managed, _Native_pfunc_type, _TDelegate^>;

		template<bool _Is_managed>
		using _Select_caller = std::conditional_t<_Is_managed, _Managed_func_caller, _Native_func_caller>;

		template<bool _Is_managed>
		using _Result_pair = _MyPair<_Select_func_type<_Is_managed>, _Select_caller<_Is_managed>>;

	public:

		template<typename _Cast_args_fptr, typename _Source, typename _Target>
		static _Target create(_Source) = delete;

		inline constexpr static bool _Managed = true;
		inline constexpr static bool _Native = false;

		template<__Native_cast_args_pfunc_type fptr>
		static _Result_pair<_Managed> create(_TDelegate^ func) {
			if constexpr (fptr == nullptr)
				throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

			_Managed_func_caller caller{};
			caller.func = func;
			caller._invoke_func = fptr;

			auto _native_invoke_delfunc = gcnew _Native_delegate_type(caller, &_Managed_func_caller::_invoke);
			caller.gch = GCHandle::Alloc(_native_invoke_delfunc);

			auto _native_invoke_pfunc = static_cast<_Native_pfunc_type>(
				(void*)Marshal::GetFunctionPointerForDelegate(_native_invoke_delfunc));

			return _Result_pair<_Managed>{_native_invoke_pfunc, caller};
		}

		template<__Managed_cast_args_pfunc_type fptr>
		static _Result_pair<_Native> create(_Native_pfunc_type func) {
			if constexpr (fptr == nullptr)
				throw gcnew System::NullReferenceException("Template arg <fptr> can not be null");

			_Native_func_caller caller{};
			caller.func = func;
			caller._invoke_func = fptr;

			auto _managed_invoke_delfunc = gcnew _TDelegate(caller, &_Native_func_caller::_invoke);

			return _Result_pair<_Native>{_managed_invoke_delfunc, caller};
		}
	};
}


delegate double _Delegate(String^);

double _source_func(String^ str) {
	//    source managed function
	Console::WriteLine(str);
}

double _cast_args(Object^ delfunc, std::string str) {
	//    cast args and call delegate
	return static_cast<_Delegate^>(delfunc)(marshalString(str));
}

void Test()
{
	auto delfunc = gcnew _Delegate(&_source_func);

	using function_marshaler = llnet::callback::function_marshaler<double(std::string), double(String^), _Delegate>;

	//    pair<native_fptr,internal_caller_instance>
	auto pair = function_marshaler::create<_cast_args>(delfunc);

	std::string str = "str";

	//    native call
	pair.first(str);
}