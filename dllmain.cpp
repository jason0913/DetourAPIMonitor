
#include <stdio.h>
#include <windows.h>
#include "stdafx.h"
#include "detours.h"
#include "header.h"
#include "signature.h"

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved)
{
	(void)hinst;
	(void)reserved;

	if (dwReason == DLL_PROCESS_ATTACH) {
		detourMonitorAttach(L"ExitProcess", &(PVOID&)origExitProcess, fakeExitProcess);
		detourMonitorAttach(L"Sleep", &(PVOID&)origSleep, fakeSleep);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		detourMonitorDetach(L"ExitProcess", &(PVOID&)origExitProcess, fakeExitProcess);
		detourMonitorDetach(L"Sleep", &(PVOID&)origSleep, fakeSleep);
	}
	return TRUE;
}
