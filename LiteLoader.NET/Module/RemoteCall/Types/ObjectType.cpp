#include "ObjectType.hpp"

#include "ValueType.hpp"

namespace LiteLoader::RemoteCall
{

	inline ObjectType::ObjectType(Dictionary<String^, Valuetype^>^ v)
		: value(v)
	{
	}

	inline String^ ObjectType::ToString() {
		return value->Count.ToString();
	}
}