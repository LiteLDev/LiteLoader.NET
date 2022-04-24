using System::Attribute;
using System::AttributeUsageAttribute;
using System::AttributeTargets;

namespace LLNET::Core
{
	public ref class LLNETLibraryAttribute sealed
		:public Attribute
	{
	public:
		property int Major;
		property int Minor;
		property int Revision;
		LLNETLibraryAttribute(int major, int minor, int revision)
		{
			Major = major;
			Minor = minor;
			Revision = revision;
		}
	};
} // namespace LLNET