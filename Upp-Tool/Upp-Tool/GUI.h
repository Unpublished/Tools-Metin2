#include "Upp-Tool.h"
#include "GUI-Funcs.h"

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI MainWindow()
{
	std::string Title;
	Title = (std::string)WND_CLASS_NAME + " " + (std::string)Version + " © by Unpublished";
	hPInstance = GetModuleHandleA(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFontA(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 450, 170, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	return MessageLoop();
}

void CreateWindowContent(HWND parent)
{
	int ButtonWidth[2] = {215, 141}, ButtonHeight = 25, PaddingButtons = 5;
	UppToolButton[0]	= CreateWindowEx(0x00000000, WC_BUTTON, "Anzahl der Upp-Vorgänge:", 0x50010003, 7, 6, 150, 20, parent, (HMENU)IDC_BUTTON[0], hPInstance, 0);
	UppToolEdit[0]		= CreateWindowEx(0x00000200, WC_EDIT, "1", 0x50010080, 160, 6, 20, 19, parent, (HMENU)IDC_EDIT[0], hPInstance, 0);
	UppToolLabel[0]		= CreateWindowEx(0x00000000, WC_STATIC, "Segi ID:", 0x50000300, 185, 8, 43, 16, parent, (HMENU)IDC_STATIC[0], hPInstance, 0);
	UppToolEdit[1]		= CreateWindowEx(0x00000200, WC_EDIT, "25040", 0x50010080, 231, 6, 60, 19, parent, (HMENU)IDC_EDIT[1], hPInstance, 0);
	UppToolLabel[1]		= CreateWindowEx(0x00000000, WC_STATIC, "Mag. Metall ID:", 0x50000300, 295, 8, 81, 16, parent, (HMENU)IDC_STATIC[1], hPInstance, 0);
	UppToolEdit[2]		= CreateWindowEx(0x00000200, WC_EDIT, "25041", 0x50010080, 379, 6, 60, 19, parent, (HMENU)IDC_EDIT[2], hPInstance, 0);
	UppToolButton[1]	= CreateWindowEx(0x00000000, WC_BUTTON, "Uppen auf Slot 1 bis:", 0x50010003, 7, 30, 124, 20, parent, (HMENU)IDC_BUTTON[1], hPInstance, 0);
	UppToolEdit[3]		= CreateWindowEx(0x00000200, WC_EDIT, "45", 0x50010080, 134, 30, 20, 19, parent, (HMENU)IDC_EDIT[3], hPInstance, 0);
	UppToolButton[2]	= CreateWindowEx(0x00000000, WC_BUTTON, "Uppen (Schmied)", 0x50012F00, 5, 53, ButtonWidth[0], ButtonHeight, parent, (HMENU)IDC_BUTTON[2], hPInstance, 0);
	UppToolButton[3]	= CreateWindowEx(0x00000000, WC_BUTTON, "Uppen (Segi)", 0x50012F00, 5 + ButtonWidth[0] + PaddingButtons, 53, ButtonWidth[0], ButtonHeight, parent, (HMENU)IDC_BUTTON[3], hPInstance, 0);
	UppToolButton[4]	= CreateWindowEx(0x00000000, WC_BUTTON, "Uppen (Mag. Metall)", 0x50012F00, 5, 83, ButtonWidth[0], ButtonHeight, parent, (HMENU)IDC_BUTTON[4], hPInstance, 0);
	UppToolButton[5]	= CreateWindowEx(0x00000000, WC_BUTTON, "DT-Uppen (1x - Slot 1)", 0x50012F00, 5 + ButtonWidth[0] + PaddingButtons, 83, ButtonWidth[0], ButtonHeight, parent, (HMENU)IDC_BUTTON[5], hPInstance, 0);
	UppToolButton[6]	= CreateWindowEx(0x00000000, WC_BUTTON, sLoad, 0x50012F00, 5, 113, ButtonWidth[1], ButtonHeight, parent, (HMENU)IDC_BUTTON[6], hPInstance, 0);
	UppToolButton[7]	= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 5 + ButtonWidth[1] + PaddingButtons, 113, ButtonWidth[1] + 1, ButtonHeight, parent, (HMENU)IDC_BUTTON[7], hPInstance, 0);
	UppToolButton[8]	= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 5 + ButtonWidth[1] * 2 + 1 + PaddingButtons * 2, 113, ButtonWidth[1], ButtonHeight, parent, (HMENU)IDC_BUTTON[8], hPInstance, 0);

	for (int i = 0;i < _countof(UppToolButton);i++)
		SendMessage(UppToolButton[i], WM_SETFONT, (WPARAM)hFont, TRUE);
	for (int i = 0; i < _countof(UppToolEdit); i++)
		SendMessage(UppToolEdit[i], WM_SETFONT, (WPARAM)hFont, TRUE);
	for (int i = 0;i < _countof(UppToolLabel);i++)
		SendMessage(UppToolLabel[i], WM_SETFONT, (WPARAM)hFont, TRUE);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetAddies, 0, 0, 0);
}

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case 2002:
			Uppen();
			break;
			
		case 2003:
			Uppen(2);
			break;

		case 2004:
			Uppen(3);
			break;

		case 2005:
			SendRefine(4, 0);
			break;

		case 2006:
			Load(1);
			break;

		case 2007:
			Save();
			break;

		case 2008:
			Reset();
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
