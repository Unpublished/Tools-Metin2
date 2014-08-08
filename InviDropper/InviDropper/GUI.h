#include "InviDropper.h"
#include "GUI-Funcs.h"

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI MainWindow()
{
	std::string Title;
	Title = (std::string)sInviDropper + " " + (std::string)Version + " © by Unpublished";
	hPInstance = GetModuleHandleA(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFontA(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 35, 70, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	return MessageLoop();
}

void CreateWindowContent(HWND parent)
{
	InviDroppenButton = CreateWindowEx(0x00000000, WC_BUTTON, sDroppen, 0x50012F00, 10, 10, 100, 25, parent, (HMENU)IDC_BUTTON[0], hPInstance, 0);
	SendMessage(InviDroppenButton, WM_SETFONT, (WPARAM)hFont, TRUE);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetAddies, 0, 0, 0);
}

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case 2000:
			DropItems();
			break;
		}
		break;

	case WM_CREATE:
		CreateWindowContent(hwnd);
		break;

	case WM_CLOSE:
		char ExitWarningMsg[256];
		sprintf_s(ExitWarningMsg, CloseDialog, WND_CLASS_NAME);
		if (MessageBox(hwnd, ExitWarningMsg, sWarning, MB_YESNO | MB_ICONQUESTION) == IDYES)
			ExitProcess(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return FALSE;
}
