
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
// typedef void (*HookFunctionType)(void* a1, void* a2);
#pragma unmanaged
void HookFunctionInstance(UINT exitCode, LPCWSTR pszMessage, LPCWSTR errorSource, LPCWSTR argExceptionString)
{
	//unmanaged is necessary,otherwise it will cause stack overflow
	// do not use other functions outside of this function
	std::cout << "[fixClrFatalError] CLR Fatal Error." << std::endl;
	std::cout << "[fixClrFatalError] ExitCode : " << exitCode << std::endl;
	if (pszMessage != nullptr)
		std::cout << "[fixClrFatalError] pszMessage : " << *pszMessage << std::endl;
	if (errorSource != nullptr)
		std::cout << "[fixClrFatalError] errorSource : " << *errorSource << std::endl;
	if (argExceptionString != nullptr)
		std::cout << "[fixClrFatalError] argExceptionString : " << *argExceptionString << std::endl;
	throw new std::exception("CLR Fatal Error");
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
			uintptr_t result = FindSignature((uintptr_t)baseAddress, ((uintptr_t)(baseAddress)+size),
				"48 89 5C 24 08 48 89 74 24 10 48 89 7C 24 18 41 54 41 56 41 57 48 81 EC B0 00 00 00 4D 8B E1 4D 8B F0 48 8B DA 8B F9 44 8B 15 ? ? ? 00 65 48 8B 04 25 58 00 00 00 B9 30 01 00 00 4E 8B 3C D0 49 8B 34 0F 48 89 74 24 60 33 C0 F0 48 0F B1 35 ? ? ? 00 48 3B C6 75 11 48 8D 0D ? ? ? 00 E8 ? ? FE FF E9 85 01 00 00 48 85 C0 74 23 BB 01 00 00 00 EB 0B 33 D2 8D 4A 32 FF 15 ? ? ?");
				if (result != 0)
			{
				void* pold;
				HookFunction((void*)result, &pold, (void*)(HookFunctionInstance));
				logger.info("The fatal error of coreclr.dll has been redirected. {}", result);
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