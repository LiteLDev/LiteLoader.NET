#include "ArrayType.hpp"

#include "ValueType.hpp"

namespace LiteLoader::RemoteCall
{
	inline ArrayType::ArrayType(List<Valuetype^>^ v)
		:value(v)
	{
	}

	inline String^ ArrayType::ToString() {
		return value->Count.ToString();
	}
}