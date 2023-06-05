#pragma once
#include <mc/I18n.hpp>

#include <src/Main/ClassTemplate.hpp>

namespace MC
{
	public
	ref class I18n : ClassTemplate<I18n, ::I18n>
	{
	public:
		static String^ Get(String^);
		static String^ Get(String^, System::Collections::Generic::IList<String^>^);
	};
}