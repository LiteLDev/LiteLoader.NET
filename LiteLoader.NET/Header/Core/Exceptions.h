#pragma once
namespace LLNET::Core
{
	public
	ref class LiteLoaderDotNETException
		: public System::ApplicationException
	{
	public:
		LiteLoaderDotNETException()
			: ApplicationException()
		{
		}
		LiteLoaderDotNETException(System::String^ message)
			: ApplicationException(message)
		{
		}
	};
	public
	ref class HookFailedException
		: public LiteLoaderDotNETException
	{
	public:
		HookFailedException()
			: LiteLoaderDotNETException()
		{
		}
	};
	public
	ref class NativePluginException
		: public LiteLoaderDotNETException
	{
	public:
		NativePluginException()
			: LiteLoaderDotNETException()
		{
		}
	};
	public
	ref class InvalidRemoteCallTypeException
		:public LiteLoaderDotNETException
	{
	public:
		InvalidRemoteCallTypeException()
			:LiteLoaderDotNETException()
		{
		}
	};
	public
	ref class DynamicCommandInvalidCastException
		:public LiteLoaderDotNETException
	{
	public:
		DynamicCommandInvalidCastException()
			:LiteLoaderDotNETException()
		{
		}
	};
	public
	ref class RegisterCommandException
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
}
