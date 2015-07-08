
#define BUFFERSIZE 256
#define VERBOSE 1
#define PCHAR char*

/*
* surcharge log()
*/
void logV(PCHAR param1, PCHAR param2) {
	char out[BUFFERSIZE];
	sprintf_s(out, BUFFERSIZE, "[Detour] %s(%s)", param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugStringA(out);
}

void log(PCHAR param1, ULONG param2) {
	char out[BUFFERSIZE];
	sprintf_s(out, BUFFERSIZE, "[Hook] %s(%d)", param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugStringA(out);
}

void log(PCHAR param1, UINT param2) {
	char out[BUFFERSIZE];
	sprintf_s(out, BUFFERSIZE, "[Hook] %s(%d)", param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugStringA(out);
}

void log(PCHAR param1, CONST PCHAR param2) {
	char out[BUFFERSIZE];
	sprintf_s(out, BUFFERSIZE, "[Hook] %s(%s)", param1, param2);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugStringA(out);
}

void log(PCHAR param1, HINSTANCE param2, CONST PCHAR param3) {
	char out[BUFFERSIZE];
	sprintf_s(out, BUFFERSIZE, "[Hook] %s(%p, %s)", param1, param2, param3);
	out[BUFFERSIZE - 1] = '\0';
	OutputDebugStringA(out);
}

/*
* friendly messages
*/
void success(PCHAR param1) {
	logV(param1, "SUCCESS");
}
void failed(PCHAR param1) {
	logV(param1, "FAILED");
}
void removed(PCHAR param1) {
	logV(param1, "REMOVED");
}

/*
* detour main functions
*/
void detourMonitorAttach(PCHAR func, PVOID* orig, PVOID fake) {
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

void detourMonitorDetach(PCHAR func, PVOID* orig, PVOID fake) {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(orig, fake);
	DetourTransactionCommit();
	if (VERBOSE)
		removed(func);
}
