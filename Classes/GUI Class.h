#include <CommCtrl.h>

#include "Variables.h"
#include "..\..\Classes\Strings.h"
#include "GUI-Variables.h"

#pragma comment(lib, "comctl32.lib")

HFONT hFont;
HINSTANCE hPInstance;
HWND WindowHandle;

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int MessageLoop()
{
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(hFont);
	return msg.wParam;
}

void RegisterClasses()
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
	wc.hInstance = hPInstance;
	wc.lpszMenuName = 0;
	wc.style = CS_PARENTDC | CS_DBLCLKS;
	wc.lpfnWndProc = WndThread;
	wc.lpszClassName = WND_CLASS_NAME;

	RegisterClass(&wc);
}