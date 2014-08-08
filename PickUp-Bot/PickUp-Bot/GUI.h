#include "PickUp-Bot.h"
#include "GUI-Funcs.h"

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI MainWindow()
{
	std::string Title;
	Title = "PickUp-Bot " + (std::string)Version + " Preview © by Unpublished";
	hPInstance = GetModuleHandle(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFont(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 345, 125, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	GUIThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GUI, 0, 0, 0);
	Initialize();
	return MessageLoop();
}

void CreateWindowContent(HWND parent)
{
	PickUpBotLabel[0]	= CreateWindowEx(0x00000000, WC_STATIC, "Sleep-Zeit:", 0x50000300, 10, 10, 55, 14, parent, (HMENU) IDC_STATIC[0], hPInstance, 0);
	PickUpBotEdit[0]	= CreateWindowEx(0x00000200, WC_EDIT, sDefSleep, 0x50010080, 69, 7, 40, 19, parent, (HMENU) IDC_EDIT[0], hPInstance, 0);
	PickUpBotButton[0]	= CreateWindowEx(0x00000000, WC_BUTTON, "Instant-PickUp", 0x50010003, 10, 40, 91, 20, parent, (HMENU) IDC_BUTTON[0], hPInstance, 0);
	PickUpBotButton[1]	= CreateWindowEx(0x00000000, WC_BUTTON, sStart, 0x50012F00, 9, 68, 158, 25, parent, (HMENU) IDC_BUTTON[1], hPInstance, 0);
	PickUpBotButton[2]	= CreateWindowEx(0x00000000, WC_BUTTON, sStop, 0x50012F00, 172, 68, 158, 25, parent, (HMENU) IDC_BUTTON[2], hPInstance, 0);
	PickUpBotButton[3]	= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 172, 8, 158, 25, parent, (HMENU) IDC_BUTTON[3], hPInstance, 0);
	PickUpBotButton[4]	= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 172, 38, 158, 25, parent, (HMENU) IDC_BUTTON[4], hPInstance, 0);

	SendMessage(PickUpBotLabel[0], WM_SETFONT, (WPARAM) hFont, TRUE);
	SendMessage(PickUpBotEdit[0], WM_SETFONT, (WPARAM) hFont, TRUE);
	for (int i = 0;i < _countof(PickUpBotButton);i++)
		SendMessage(PickUpBotButton[i], WM_SETFONT, (WPARAM) hFont, TRUE);

	DeactivatePickUpBot();

	DeleteUnused("PickFix");
	DeleteUnused("PickOccurrence");
	if (Load(0) == 1)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Load, (LPVOID)1, 0, 0);

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
			if (IsDlgButtonChecked(hwnd, IDC_BUTTON[0]) == BST_CHECKED)
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ActivateInstantPickUp, 0, 0, 0);
			else
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DeactivateInstantPickUp, 0, 0, 0);
			break;

		case 2001:
			ActivatePickUpBot();
			break;

		case 2002:
			DeactivatePickUpBot();
			break;

		case 2003:
			Save();
			break;

		case 2004:
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Reset, 0, 0, 0);
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
		{
			DeactivatePickUpBot();
			CloseHandle(hProcess);
			ExitProcess(0);
		}
		break;

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return FALSE;
}
