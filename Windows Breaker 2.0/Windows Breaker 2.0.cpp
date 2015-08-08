// Windows Breaker 2.0.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include <CommCtrl.h>
#pragma comment (lib,"comctl32.lib")

#include "Windows Breaker 2.0.h"
#include "Breaker.h"

#define MAX_LOADSTRING 100

//Turn on windows thems
#ifdef UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle [MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass [MAX_LOADSTRING];			// the main window class name
HWND hMainWindow;

// Forward declarations of functions included in this code module:
INT_PTR CALLBACK	MainDialog (HWND, UINT, WPARAM, LPARAM);
BOOL				CenterWindow (HWND hwndWindow);

//
CBreaker *pBreaker;

int APIENTRY _tWinMain (_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	InitCommonControls();

	MSG msg;
	HACCEL hAccelTable;

	//Init CBreaker object
	pBreaker = new CBreaker();

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSBREAKER20));

	//Open dialog
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAINBOX), 0, MainDialog);

	//Release memory
	delete pBreaker;
	return 0;
}

/*
	Message handler for about box
*/
INT_PTR CALLBACK MainDialog (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message) {
		case WM_INITDIALOG:
			//Mover window to the center
			CenterWindow(hDlg);

			//
			SetWindowText(GetDlgItem(hDlg, IDC_EDIT_NAME), "cmd");
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			//User click start button
			if (LOWORD(wParam) == IDC_START) {
				//Get application name
				char tmp[256];
				GetWindowTextA(GetDlgItem(hDlg, IDC_EDIT_NAME), tmp, sizeof (tmp));

				//Let`s get access
				if (pBreaker->start(tmp)) {
					SetWindowTextA(GetDlgItem(hDlg, IDC_WAIT_LABEL), "Please wait...");
				} else {
					SetWindowTextA(GetDlgItem(hDlg, IDC_WAIT_LABEL), "Error");
				}
				ShowWindow(GetDlgItem(hDlg, IDC_WAIT_LABEL), SW_SHOWNOACTIVATE);
				return (INT_PTR)TRUE;
			}
			break;
		case WM_CTLCOLORSTATIC:
			//Set color to the help label
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_HELP_VIEW)) {
				SetBkMode((HDC)wParam, TRANSPARENT);

				//I prefer a gray color
				SetTextColor((HDC)wParam, RGB(100, 100, 100));
				return (BOOL)CreateSolidBrush(GetSysColor(COLOR_MENU));
			}
			break;
	}
	return (INT_PTR)FALSE;
}

/*
	Move window to the center of screen
*/
BOOL CenterWindow (HWND hwndWindow) {
	int w = GetSystemMetrics(SM_CXSCREEN),
		h = GetSystemMetrics(SM_CYSCREEN);

	//Get screen size
	RECT rectWindow;
	GetWindowRect(hwndWindow, &rectWindow);

	int nWidth = rectWindow.right - rectWindow.left;
	int nHeight = rectWindow.bottom - rectWindow.top;

	int nX = (w - nWidth) >> 1;
	int nY = (h - nHeight) >> 1;

	//Move window
	MoveWindow(hwndWindow, nX, nY - 100, nWidth, nHeight, FALSE);
	return true;
}