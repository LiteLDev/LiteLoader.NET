#pragma once
namespace LLNET::Core
{
	public ref class LiteLoaderDotNETException
		: public System::Exception
	{
	public:
		LiteLoaderDotNETException()
			: Exception()
		{
		}
		LiteLoaderDotNETException(System::String^ message)
			: Exception(message)
		{
		}
	};

	public ref class HookFailedException
		: public LiteLoaderDotNETException
	{
	public:
		HookFailedException()
			: LiteLoaderDotNETException()
		{
		}
	};

	public ref class NativePluginException
		: public LiteLoaderDotNETException
	{
	public:
		NativePluginException()
			: LiteLoaderDotNETException()
		{
		}
	};

	public ref class InvalidRemoteCallTypeException
		:public LiteLoaderDotNETException
	{
	public:
		InvalidRemoteCallTypeException()
			:LiteLoaderDotNETException()
		{
		}
	};

	public ref class RemoteCallImportFunctionException
		:public LiteLoaderDotNETException
	{
	public:
		RemoteCallImportFunctionException()
			:LiteLoaderDotNETException()
		{
		}
		RemoteCallImportFunctionException(System::String^ message)
			:LiteLoaderDotNETException(message)
		{
		}
	};

	public ref class RemoteCallExportFunctionException
		:public LiteLoaderDotNETException
	{
	public:
		RemoteCallExportFunctionException()
			:LiteLoaderDotNETException()
		{
		}
		RemoteCallExportFunctionException(System::String^ message)
			:LiteLoaderDotNETException(message)
		{
		}
	};

	public ref class DynamicCommandInvalidCastException
		:public LiteLoaderDotNETException
	{
	public:
		DynamicCommandInvalidCastException()
			:LiteLoaderDotNETException()
		{
		}
	};

	public ref class RegisterCommandException
		:public LiteLoaderDotNETException
	{
	public:
		RegisterCommandException()
			:LiteLoaderDotNETException()
		{
		}
		RegisterCommandException(System::String^ message)
			:LiteLoaderDotNETException(message)
		{
		}
	};

	public ref class MCException
		:LiteLoaderDotNETException
	{
	public:
		MCException(System::String^ message)
			:LiteLoaderDotNETException(message)
		{
		}

		MCException()
			:LiteLoaderDotNETException()
		{
		}
	};

	public ref class EventException
		:LiteLoaderDotNETException
	{
	public:
		EventException(System::String^ message)
			:LiteLoaderDotNETException(message)
		{
		}
		EventException()
			:LiteLoaderDotNETException()
		{
		}
	};

	public ref class RegisterEventException
		:EventException
	{
	public:
		RegisterEventException(System::String^ message)
			:EventException(message)
		{
		}
	};

	public ref class RegisterEventListenerException
		:EventException
	{
	public:
		RegisterEventListenerException(System::String^ message)
			:EventException(message)
		{
		}
	};

	public ref class CancelEventException
		:EventException
	{
	public:
		CancelEventException()
			:EventException()
		{
		}
	};
}
