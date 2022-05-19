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
}
