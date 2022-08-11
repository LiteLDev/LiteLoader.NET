#pragma unmanaged 

#include <Windows.h>

typedef DWORD EXCEPTION_CODE;

EXCEPTION_CODE _try_catch(void(*pfunc)())
{
	__try
	{
		pfunc();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return GetExceptionCode();
	}

	return 0;
}