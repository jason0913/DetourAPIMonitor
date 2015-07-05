
/*	VOID WINAPI ExitProcess(
	_In_ UINT uExitCode
	);*/
static VOID(WINAPI* origExitProcess)(UINT uExitCode) = ExitProcess;
VOID WINAPI fakeExitProcess(UINT uExitCode)
{
	log("ExitProcess", uExitCode);
	return origExitProcess(uExitCode);
}

/*	VOID WINAPI Sleep(
	_In_ DWORD dwMilliseconds
	);*/
static VOID(WINAPI* origSleep)(DWORD dwMilliseconds) = Sleep;
VOID WINAPI fakeSleep(DWORD dwMilliseconds)
{
	log("Sleep", dwMilliseconds);
	return origSleep(dwMilliseconds);
}

/*	FARPROC WINAPI GetProcAddress(
	_In_ HMODULE hModule,
	_In_ LPCSTR  lpProcName
	);*/
static FARPROC(WINAPI* origGetProcAddress)(HMODULE hModule, LPCSTR lpProcName) = GetProcAddress;
FARPROC WINAPI fakeGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	log("GetProcAddress", hModule, lpProcName);
	return origGetProcAddress(hModule, lpProcName);
}

/*	HMODULE WINAPI LoadLibraryA(
	_In_ LPCTSTR lpFileName
	);*/
static HMODULE(WINAPI* origLoadLibraryA)(LPCSTR lpFileName) = LoadLibraryA;
HMODULE WINAPI fakeLoadLibraryA(LPCSTR lpFileName)
{
	log("LoadLibraryA", lpFileName);
	return origLoadLibraryA(lpFileName);
}
