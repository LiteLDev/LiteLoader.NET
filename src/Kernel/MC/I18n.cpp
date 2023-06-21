#include <mutex>
#include <src/Header/MC/I18n.hpp>

namespace MC {
	String^ I18n::Get(String^ str)
	{
		return marshalString(::I18n::get(marshalString(str)));
	}
	String^ I18n::Get(String^ str, System::Collections::Generic::IList<String^>^ args)
	{
		auto len = args->Count;
		std::vector<std::string> stdvector(len);
		for (int i = 0; i < len; ++i)
			stdvector.emplace_back(marshalString(args[i]));
		return marshalString(::I18n::get(marshalString(str), stdvector));
	}
}