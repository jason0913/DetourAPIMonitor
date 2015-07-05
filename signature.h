
/*	VOID WINAPI ExitProcess(
	_In_ UINT uExitCode
	);*/
static VOID(WINAPI* origExitProcess)(UINT uExitCode) = ExitProcess;
VOID WINAPI fakeExitProcess(UINT uExitCode)
{
	log(L"ExitProcess", uExitCode);
	return origExitProcess(uExitCode);
}

/*	VOID WINAPI Sleep(
	_In_ DWORD dwMilliseconds
	);*/
static VOID(WINAPI* origSleep)(DWORD dwMilliseconds) = Sleep;
VOID WINAPI fakeSleep(DWORD dwMilliseconds)
{
	log(L"Sleep", dwMilliseconds);
	return origSleep(dwMilliseconds);
}
