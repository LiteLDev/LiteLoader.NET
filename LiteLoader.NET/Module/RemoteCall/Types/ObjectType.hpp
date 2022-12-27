#pragma once
#include <LiteLoader.NET/Main/DotNETGlobal.hpp>

#include <LiteLoader.NET/Module/RemoteCall/Interfaces/IValueType.hpp>

namespace LiteLoader::RemoteCall
{
	ref class Valuetype;
}

namespace LiteLoader::RemoteCall
{
	public ref class ObjectType: IValueType
	{
	public:
		ObjectType(Dictionary<String^, Valuetype^>^ v);
		Dictionary<String^, Valuetype^>^ value;
	public:
		virtual String^ ToString() override;
	};
}

