#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <llapi/utils/Hash.h>
#include <functional>
#include "type_traits.hpp"

namespace llnet::callback {
	namespace detail {

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

	}

	template<typename _Fty1, typename _Fty2, typename _TDelegate>
	struct function_marshaler {

	};

	template<typename _Ret1, typename _Ret2, typename..._Types1, typename ..._Types2, typename _TDelegate>
	value struct function_marshaler<_Ret1(_Types1...), _Ret2(_Types2...), _TDelegate> {
		static_assert(is_delegate_v<_TDelegate>, "_TDelegate only accept delegate types.");
	protected:
		using _Func_impl_1 = detail::_Get_func_impl<_Ret1(_Types1...)>;
		using _Func_impl_2 = detail::_Get_func_impl<_Ret2(_Types2...)>;

		typedef _Ret1(*_Native_func_type)(_Types1...);
		delegate _Ret1 _Native_delegate_type(_Types1...);

		typedef _Ret2(*_Managed_func_type)(_Types2...);
		//delegate _Ret2 _Managed_delegate_type(_Types2...);    //equals to _TDelegate

	private:
		value struct _Managed_func_caller {
			_TDelegate^ func;
			property _Native_func_type _invoke_func;
		};

		value struct _Native_func_caller {
			_Native_func_type func;
			property _TDelegate^ _invoke_func;
		};

	protected:
		template<bool _Is_managed>
		using _Select_func_type = std::conditional_t<_Is_managed, _TDelegate^, _Native_func_type>;

		template<bool _Is_managed>
		using _Select_caller = std::conditional_t<_Is_managed, _Managed_func_caller, _Native_func_caller>;

		template<bool _Is_managed>
		using _Result_pair = std::pair<_Select_func_type<_Is_managed>, _Select_caller<_Is_managed>>;

		template<typename _Source, typename _Target>
		static _Target _create(_Source) = delete;

		template<>
		static _Result_pair<false> _create(_TDelegate^ del) {
			auto caller = gcnew _Managed_func_caller;
			caller->delfunc = del;
		}

	};
}