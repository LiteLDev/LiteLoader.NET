#include "../Header/LLAPI.h"

using System::Attribute;
using System::AttributeUsageAttribute;
using System::AttributeTargets;

namespace LLNET::Core
{
	[AttributeUsage(AttributeTargets::Assembly)]
	public ref class LLNETLibraryAttribute sealed
		:public Attribute
	{
	public:
		property int Major;
		property int Minor;
		property int Revision;
		property LLNET::LL::Version::StatusEnum Status;
		property String^ Desc;
		LLNETLibraryAttribute()
		{
			Major = 0;
			Minor = 0;
			Revision = 0;
			Status = LLNET::LL::Version::StatusEnum::Dev;
			Desc = "";
		}
	};

	[AttributeUsage(AttributeTargets::Class)]
	public ref class PluginMainAttribute sealed
		:public Attribute
	{
	public:
		property System::String^ Name;
		PluginMainAttribute(String^ name) 
		{
			Name = name;
		}
	};

	[AttributeUsage(AttributeTargets::Assembly, AllowMultiple = true)]
	public ref class LibPathAttribute sealed
		:public Attribute
	{
	public:
		property System::String^ Path;
		LibPathAttribute(String^ path)
		{
			Path = path; 
		}
	};
} // namespace LLNET