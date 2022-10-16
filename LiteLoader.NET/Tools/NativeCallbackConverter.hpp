#include <LiteLoader.NET/Main/DotNETGlobal.hpp>
#include <llapi/utils/Hash.h>
#include <functional>
#include "type_traits.hpp"

namespace llnet::callback {
	namespace detail {
		template<typename _Td>
		struct _Delegate_class {

		};

		template<typename _Tx>
		struct _Get_delegate_impl {
			static_assert(std::_Always_false<_Tx>);
		};

		template<typename _Ret, typename... _Types>
		struct _Get_delegate_impl<_Ret(_Types...)> {
			using result_type = _Ret;

			template<size_t _Index> struct args {
				using type = std::tuple_element<_Index, std::tuple<_Types...>>::type;
			};

			template<size_t _Index>using args_t = args<_Index>::type;
		};
	}

	template<typename T1, typename T2>
	struct function_marshaler {

	};

	//void Test()
	//{
	//	detail::_Get_delegate_impl<void(int, bool)>::args_t<0> a;
	//}
}