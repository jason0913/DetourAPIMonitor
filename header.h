
#define BUFFERSIZE 256
#define VERBOSE 1

/*
 * friendly messages
 */
void success(wchar_t* param1) {
	wchar_t out[BUFFERSIZE];
	swprintf_s(out, BUFFERSIZE, TEXT("[Detour] %s (SUCCESS)"), param1);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugString(out);
}
void failed(wchar_t* param1) {
	wchar_t out[BUFFERSIZE];
	swprintf_s(out, BUFFERSIZE, TEXT("[Detour] %s (FAILED)"), param1);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugString(out);
}
void removed(wchar_t* param1) {
	wchar_t out[BUFFERSIZE];
	swprintf_s(out, BUFFERSIZE, TEXT("[Detour] %s (REMOVED)"), param1);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugString(out);
}

/*
 * detour main functions
 */

void detourMonitorAttach(wchar_t* func, PVOID* orig, PVOID fake) {
	DetourRestoreAfterWith();
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(orig, fake);
	if (DetourTransactionCommit() == 0) {
		if (VERBOSE)
			success(func);
	}
	else {
		if (VERBOSE)
			failed(func);
	}
}

void detourMonitorDetach(wchar_t* func, PVOID* orig, PVOID fake) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(orig, fake);
	DetourTransactionCommit();
	if (VERBOSE)
		removed(func);
}

/*
 *	surcharge monitor()
 */

void log(wchar_t* param1, unsigned long param2) {
	wchar_t out[BUFFERSIZE];
	swprintf_s(out, BUFFERSIZE, TEXT("[Hook] %s(%d)"), param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugString(out);
}

void log(wchar_t* param1, unsigned int param2) {
	wchar_t out[BUFFERSIZE];
	swprintf_s(out, BUFFERSIZE, TEXT("[Hook] %s(%d)"), param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugString(out);
}