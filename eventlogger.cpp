// eventlogger.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "eventlogger.h"

#define MAX_LOADSTRING 100
HWND hDlgModeless;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
char szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL CALLBACK DlgProc(HWND hDlg, UINT umsg, WPARAM wParam, LPARAM lParam)
{
	RECT rtDlg;
	switch (umsg)
	{
	case WM_INITDIALOG:
		SendMessage(hDlg, WM_SIZE, 0, 0);
		return TRUE;
	case WM_COMMAND:
		if (lParam == 0 && LOWORD(wParam)==ID_ESC)
			PostQuitMessage(0);
		if (lParam == 0 && LOWORD(wParam) == ID_CLEAR)
			SetDlgItemText(hDlg, IDC_EDIT1, "");
		break;
	case WM_SIZE:
		GetClientRect(hDlg, &rtDlg);
		MoveWindow(GetDlgItem(hDlg, IDC_EDIT1), rtDlg.left, rtDlg.top, rtDlg.right - rtDlg.left, rtDlg.bottom - rtDlg.top, 0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    MyRegisterClass(hInstance);

    // Perform application initialization:
	HWND hMain = InitInstance(hInstance, nCmdShow);
    if (!hMain)
    {
        return FALSE;
    }
	hDlgModeless = CreateDialogParam(hInstance, "display", hMain, (DLGPROC)DlgProc, NULL);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EVENTLOGGER));

    MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
//		if (!IsDialogMessage(hDlgModeless, &msg))
		{
			if (!TranslateAccelerator(hDlgModeless, hAccelTable, &msg))
			{
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			//else
			//{
			//	IsDialogMessage(hDlgModeless, &msg);
			//	DWORD w = msg.wParam;
			//	DWORD l = msg.lParam;
			//	int jj = 2;
			//}
		}
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EVENTLOGGER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCE(IDC_EVENTLOGGER);
    wcex.lpszClassName  = "EventLogger";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassEx(&wcex);
}

HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindow("EventLogger", "", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return NULL;
   }

//   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return hWnd;
}


void EditPrintf(HWND hwndEdit, const char * szFormat, ...);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	PCOPYDATASTRUCT pcd;
	HDC hdc;
	switch (message)
    {
    case WM_COMMAND:
		return DefWindowProc(hWnd, message, wParam, lParam);
	case WM_COPYDATA:
		pcd = (PCOPYDATASTRUCT)lParam;
		EditPrintf(GetDlgItem(hDlgModeless, IDC_EDIT1), (char*)pcd->lpData);
//		EditPrintf(GetDlgItem(hDlgModeless, IDC_EDIT1), "\n");
		break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
