using namespace System::Collections::Generic;

namespace LiteLoader::NET
{
	public interface class IPluginInitializer
	{
	public:
		property System::Version^ Version
		{
			System::Version^ get();
		}
		property System::String^ Introduction
		{
			System::String^ get();
		}
		property Dictionary<System::String^, System::String^>^ MetaData
		{
			Dictionary<System::String^, System::String^>^ get();
		}
		void OnInitialize();
	};
}
