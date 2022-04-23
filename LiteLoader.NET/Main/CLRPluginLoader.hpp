#pragma once
#pragma unmanaged
#include <Windows.h>
#include <metahost.h>
#include <mscoree.h>
#pragma comment(lib, "mscoree.lib")

#pragma unmanaged
namespace ManageCodeInvoker
{
#pragma unmanaged
	class ClrHost
	{
		bool Initialized = false;
		HRESULT hr = NULL;
		ICLRMetaHost* pMetaHost = nullptr;
		ICLRRuntimeInfo* pRuntimeInfo = nullptr;
		ICLRRuntimeHost* pClrRuntimeHost = nullptr;
		DWORD dwLengthRet = NULL;
		std::wstring Version;
	public:
		const HRESULT HR() const { return hr; }
		const int ReturnValue() const { return (int)dwLengthRet; }
		const std::wstring& GetVersion() const { return Version; }


		void Init(std::wstring pszVersion) {

			if (Initialized)
				return;

			Version = pszVersion;

			hr = CLRCreateInstance(CLSID_CLRMetaHost, IID_PPV_ARGS(&pMetaHost));//创建实例
			if (FAILED(hr))
			{
				Release();
				throw(std::runtime_error("Failed to Create CLR Instance"));
			}

			hr = pMetaHost->GetRuntime(Version.c_str(), IID_PPV_ARGS(&pRuntimeInfo));//获取CLR信息
			if (FAILED(hr))
			{
				Release();
				throw(std::runtime_error("Failed to Get Runtime"));
			}

			BOOL fLoadable;
			hr = pRuntimeInfo->IsLoadable(&fLoadable);
			if (FAILED(hr) || !fLoadable)
			{
				Release();
				throw(std::runtime_error("Failed to Load Runtime"));
			}

			hr = pRuntimeInfo->GetInterface(CLSID_CLRRuntimeHost, //初始化ClrRuntimeHost
				IID_PPV_ARGS(&pClrRuntimeHost));
			if (FAILED(hr))
			{
				Release();
				throw(std::runtime_error("Failed to Get Runtime Interface"));
			}

			hr = pClrRuntimeHost->Start();//启动CLR
			if (FAILED(hr))
			{
				Release();
				throw(std::runtime_error("Failed to Start CLR"));
			}
			Initialized = true;
		}
		void Release() {
			if (!Initialized)
				return;
			if (pClrRuntimeHost != nullptr) {
				pClrRuntimeHost->Stop();
				pClrRuntimeHost->Release();
				pClrRuntimeHost = nullptr;
			}
			if (pMetaHost != nullptr) {
				pMetaHost->Release();
				pMetaHost = nullptr;
			}
			if (pRuntimeInfo != nullptr) {
				pRuntimeInfo->Release();
				pRuntimeInfo = nullptr;
			}
			hr = NULL;
			dwLengthRet = NULL;
			Initialized = false;
		}

		void ExcuteManageCode(
			PCWSTR pszAssemblyName,
			PCWSTR pszClassName,
			PCWSTR pszMethodName,
			PCWSTR argument
		) {
			if (!Initialized)
			{
				return;
				throw(std::runtime_error("Clr not Initialized."));
			}
			try
			{
				hr = pClrRuntimeHost->ExecuteInDefaultAppDomain(
					pszAssemblyName,
					pszClassName,
					pszMethodName,
					argument,
					&dwLengthRet
				);
			}
			catch (const std::exception& exc)
			{
				std::cout << exc.what() << std::endl;
			}
			if (FAILED(hr))
			{
				Release();
				throw(std::runtime_error("Failed to Run Managed Code"));
			}

		}
	};
}

