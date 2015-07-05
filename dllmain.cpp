
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
		detourMonitorAttach("ExitProcess", &(PVOID&)origExitProcess, fakeExitProcess);
		detourMonitorAttach("Sleep", &(PVOID&)origSleep, fakeSleep);
		detourMonitorAttach("GetProcAddress", &(PVOID&)origGetProcAddress, fakeGetProcAddress);
		detourMonitorAttach("LoadLibrary", &(PVOID&)origLoadLibraryA, fakeLoadLibraryA);
	}
	else if (dwReason == DLL_PROCESS_DETACH) {
		detourMonitorDetach("ExitProcess", &(PVOID&)origExitProcess, fakeExitProcess);
		detourMonitorDetach("Sleep", &(PVOID&)origSleep, fakeSleep);
		detourMonitorDetach("GetProcAddress", &(PVOID&)origGetProcAddress, fakeGetProcAddress);
		detourMonitorDetach("LoadLibrary", &(PVOID&)origLoadLibraryA, fakeLoadLibraryA);
	}
	return TRUE;
}
