#include "TesTProjekt.h"
#include "GUI-Funcs.h"

int WINAPI MainWindow()
{
	std::string Title;
	Title = (std::string)sSendAttackToTarget + " " + (std::string)Version + " © by Unpublished";
	hPInstance = GetModuleHandle(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFont(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 230, 50, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	return MessageLoop();
}

void CreateWindowContent(HWND parent)
{
	CheckButton = CreateWindowEx(0x00000000, WC_BUTTON, "SendAttack to target", 0x50010003, 8, 3, 122, 17, parent, (HMENU) IDC_BUTTON[0], hPInstance, 0);
	SleepLabel	= CreateWindowEx(0x00000000, WC_STATIC, "Sleep:", 0x50000300, 140, 3, 32, 16, parent, (HMENU) IDC_STATIC[0], hPInstance, 0);
	SleepEdit	= CreateWindowEx(0x00000200, WC_EDIT, "300", 0x50010080, 175, 3, 43, 16, parent, (HMENU) IDC_EDIT[0], hPInstance, 0);

	SendMessage(CheckButton, WM_SETFONT, (WPARAM) hFont, TRUE);
	SendMessage(SleepLabel, WM_SETFONT, (WPARAM) hFont, TRUE);
	SendMessage(SleepEdit, WM_SETFONT, (WPARAM) hFont, TRUE);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetAddies, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TesTProjekt, 0, 0, 0);
}

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
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
