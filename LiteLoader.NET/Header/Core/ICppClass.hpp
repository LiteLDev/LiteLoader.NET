#pragma once
namespace LLNET::Core
{
	public interface class ICppClass
	{
		property System::IntPtr Intptr
		{
		public:
			virtual System::IntPtr get();
		};

		virtual void _dtor(void* ptr);
	};
}