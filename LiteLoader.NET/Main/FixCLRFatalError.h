
// 8/15/2022 - LazuliKao 
//it might not be the best solution but currently, I only have done this.
//
//without this fix, as long as any function called in managed code will lose
//  native "try catch", and all fatal exceptions will be handled by "coreclr"
//  instead of already written C++ "try catch", which causes a fatal error
//  and terminate the program.
//the solution is to hook "coreclr.dll" and redirect the `LogInfoForFatalError` function
//```
//PublicSymbol    ?LogInfoForFatalError@@YAXIPEB_W00@Z
//RelativeVirtualAddress  2480668
//```
//(This method will be called by "coreclr" during a fatal error, after 
// which the program will be terminated)
//By throwing a C++ exception directly in this method, you can catch
//the exception outside, instead of terminating the program.


inline uintptr_t FindSignature(uintptr_t rangeStart, uintptr_t rangeEnd, const char* szSignature)
{
	const char* pattern = szSignature;
	uintptr_t firstMatch = 0;
#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))

	BYTE patByte = GET_BYTE(pattern);
	const char* oldPat = pattern;

	for (uintptr_t pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pattern)
			return firstMatch;

		while (*(PBYTE)pattern == ' ')
			pattern++;

		if (!*pattern)
			return firstMatch;

		if (oldPat != pattern)
		{
			oldPat = pattern;
			if (*(PBYTE)pattern != '\?')
				patByte = GET_BYTE(pattern);
		}

		if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte)
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pattern[2] || !pattern[1])
				return firstMatch;

			// if (*(PWORD)pattern == '\?\?' || *(PBYTE)pattern != '\?')
			// pattern += 3;

			// else
			pattern += 2;
		}
		else
		{
			pattern = szSignature;
			firstMatch = 0;
		}
	}
	return 0u;
}
#pragma unmanaged
typedef void (*LogInfoForFatalErrorType)(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString);
#pragma unmanaged
static void* oldLogInfoForFatalError;
#pragma unmanaged
typedef void (*EEPolicy_LogFatalErrorType)(UINT exitCode, UINT_PTR address, LPCWSTR pszMessage, PEXCEPTION_POINTERS pExceptionInfo, LPCWSTR errorSource, LPCWSTR argExceptionString);
#pragma unmanaged
static void* oldEEPolicy_LogFatalError = nullptr;
#pragma unmanaged
void LogInfoForFatalError(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
	//call old function to print info
	((LogInfoForFatalErrorType)oldLogInfoForFatalError)(exitCode, pszMessage, errorSource, argExceptionString);
	//unmanaged is necessary,otherwise it will cause stack overflow
	// do not use other functions outside of this function
	if (oldEEPolicy_LogFatalError == nullptr)
	{
		std::cout << "[fixClrFatalError] CLR Fatal Error." << std::endl;
		std::cout << "[fixClrFatalError] ExitCode : " << exitCode << std::endl;
		if (pszMessage != nullptr) {
			std::cout << "[fixClrFatalError] pszMessage : ";
			wprintf_s(pszMessage);
			std::cout << std::endl;
		}
		if (errorSource != nullptr)
		{
			std::cout << "[fixClrFatalError] errorSource : ";
			wprintf_s(errorSource);
			std::cout << std::endl;
		}
		if (argExceptionString != nullptr) {
			std::cout << "[fixClrFatalError] argExceptionString : ";
			wprintf_s(argExceptionString);
			std::cout << std::endl;
		}
	}
	//throw an exception which could be caught outside ,otherwise the program will be terminated by clr
	throw;
}
#pragma unmanaged
void EEPolicy_LogFatalError(UINT exitCode, UINT_PTR address, LPCWSTR pszMessage, PEXCEPTION_POINTERS pExceptionInfo, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
	//unmanaged is necessary,otherwise it will cause stack overflow
	// do not use other functions outside of this function
	//call original
	std::cout << "[fixClrFatalError] CLR Fatal Error." << std::endl;
	std::cout << "[fixClrFatalError] Address : " << address << std::endl;
	std::cout << "[fixClrFatalError] ExitCode : " << exitCode << std::endl;
	if (pszMessage != nullptr) {
		std::cout << "[fixClrFatalError] pszMessage : ";
		wprintf_s(pszMessage);
		std::cout << std::endl;
	}
	if (errorSource != nullptr)
	{
		std::cout << "[fixClrFatalError] errorSource : ";
		wprintf_s(errorSource);
		std::cout << std::endl;
	}
	if (argExceptionString != nullptr) {
		std::cout << "[fixClrFatalError] argExceptionString : ";
		wprintf_s(argExceptionString);
		std::cout << std::endl;
	}
	if (pExceptionInfo != nullptr) {
		std::cout << "[fixClrFatalError] ExceptionAddress : " << pExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
		//https://github.com/dotnet/runtime/blob/9d6396deb02161f5ee47af72ccac52c2e1bae458/src/coreclr/vm/eepolicy.cpp#L426
		std::cout << "[fixClrFatalError] ExceptionCode : " << ((pExceptionInfo && pExceptionInfo->ExceptionRecord) ? pExceptionInfo->ExceptionRecord->ExceptionCode : 0) << std::endl;
		std::cout << "[fixClrFatalError] ExceptionFlags : " << pExceptionInfo->ExceptionRecord->ExceptionFlags << std::endl;
		if (pExceptionInfo->ExceptionRecord->ExceptionInformation != nullptr)
		{
			std::cout << "[fixClrFatalError] ExceptionInformation : " << *(pExceptionInfo->ExceptionRecord->ExceptionInformation) << std::endl;
		}
	}
	((EEPolicy_LogFatalErrorType)oldEEPolicy_LogFatalError)(exitCode, address, pszMessage, pExceptionInfo, errorSource, argExceptionString);
}
#pragma managed
inline void FixCLRFatalError(Logger& logger)
{
	auto cp = System::Diagnostics::Process::GetCurrentProcess();
	for each (System::Diagnostics::ProcessModule ^ mod in cp->Modules)
	{
		if (mod->ModuleName->ToLower() == "coreclr.dll")
		{
			void* baseAddress = mod->BaseAddress.ToPointer();
			int size = mod->ModuleMemorySize;
			//To update signature please use this : https://github.com/LazuliKao/CoreClrPatch/blob/main/build.fsx
			
			//?LogInfoForFatalError@@YAXIPEB_W00@Z
			//https://github.com/dotnet/runtime/blob/9d6396deb02161f5ee47af72ccac52c2e1bae458/src/coreclr/vm/eepolicy.cpp#L324
			uintptr_t result = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress)+size),
				"48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 54 41 56 41 57 48 81 EC B0 00 00 00 4D 8B E1 4D 8B F0 48 8B DA 8B F9 44 8B 15 ? ? ? 00 65 48 8B 04 25 58 00 00 00 B9 30 01 00 00 4E 8B 3C D0 49 8B 34 0F 48 89 74 24 60 33 C0 F0 48 0F B1 35 ? ? ? 00 48 3B C6 75 11 48 8D 0D ? ? ? 00 E8 ? ? FE FF E9 85 01 00 00 48 85 C0 74 23 BB 01 00 00 00 EB 0B 33 D2 8D 4A 32 FF 15 ? ? ?");
			if (result != 0)
			{
				HookFunction((void*)result, &oldLogInfoForFatalError, (void*)(LogInfoForFatalError));
				logger.info("The fatal error of coreclr.dll has been redirected. {}", result);
				//?LogFatalError@EEPolicy@@CAXI_KPEB_WPEAU_EXCEPTION_POINTERS@@11@Z
				//https://github.com/dotnet/runtime/blob/9d6396deb02161f5ee47af72ccac52c2e1bae458/src/coreclr/vm/eepolicy.cpp#L410
				uintptr_t eepolicylog = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress)+size),
					"40 53 56 57 41 ? 41 ? 41 57 48 81 EC D8 0C 00 00 48 8B 05 ? ? ? 00 48 33 C4 48 89 84 24 C8 0C 00 00 49 8B D9 48 89 9C 24 80 00 00 00 49 8B F0 4C 8B ? 44 8B E9 89 8C 24 90 00 00 00 48 89 9C 24 C0 00 00 00 4C 8B 84 24 30 0D 00 00 4C 8B ? 24 38 0D 00 00 4D 8B ? 48 8B D6 E8 ? 0A 00 00 33 FF 48 8B 05 ? ? ? 00 39 78 24 75 17 48 8B 0D ? ? ? 00 48 8B C1 48 C1 E8 08 84 C0 74");
				if (eepolicylog != 0)
				{
					HookFunction((void*)eepolicylog, &oldEEPolicy_LogFatalError, (void*)(EEPolicy_LogFatalError));
				}
			}
			else
			{
				logger.info("Unable to find signature.");
				logger.info("Please open an issue on LLNet Repo and upload your coreclr.dll.");
				logger.info("{}", marshalString(mod->FileVersionInfo->FileName));
			}
		}
	}
}