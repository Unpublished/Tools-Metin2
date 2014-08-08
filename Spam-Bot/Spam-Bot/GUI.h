#include "GUI-Funcs.h"
#include "Spam-Bot.h"

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI MainWindow()
{
	std::string Title;
	Title = (std::string)Spam_Bot + " " + (std::string)Version + " © by Unpublished";
	hPInstance = GetModuleHandle(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFont(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 440, 165, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GUI, 0, 0, 0);
	return MessageLoop();
}

void CreateSpamBotContent(HWND parent)
{
	SpamBotLabel[0] = CreateWindowEx(0x00000000, WC_STATIC, ((std::string)sSpamText + ":").c_str(), 0x50000300, 10, 11, 58, 14, parent, (HMENU)IDC_STATIC[0], hPInstance, 0);
	SpamBotEdit[0]	= CreateWindowEx(0x00000200, WC_EDIT, "", 0x50010080, 72, 8, 350, 20, parent, (HMENU) IDC_EDIT[0], hPInstance, 0);
	SpamBotLabel[1] = CreateWindowEx(0x00000000, WC_STATIC, ((std::string)sChatTyp + ":").c_str(), 0x50000300, 16, 35, 52, 14, parent, (HMENU)IDC_STATIC[1], hPInstance, 0);
	SpamBotCombo[0] = CreateWindowEx(0x00000000, WC_COMBOBOX, "", 0x50010203, 72, 32, 100, 20 + XP * 60, parent, (HMENU) IDC_COMBO[0], hPInstance, 0);
	SpamBotLabel[2] = CreateWindowEx(0x00000000, WC_STATIC, ((std::string)sAnzahl + ":").c_str(), 0x50000300, 30, 59, 38, 14, parent, (HMENU)IDC_STATIC[2], hPInstance, 0);
	SpamBotEdit[1]	= CreateWindowEx(0x00000200, WC_EDIT, "0", 0x50012080, 72, 56, 60, 20, parent, (HMENU) IDC_EDIT[1], hPInstance, 0);
	SpamBotLabel[3] = CreateWindowEx(0x00000000, WC_STATIC, "Sleep-Zeit:", 0x50000300, 13, 83, 55, 14, parent, (HMENU) IDC_STATIC[3], hPInstance, 0);
	SpamBotEdit[2]	= CreateWindowEx(0x00000200, WC_EDIT, sDefMinSleep, 0x50012080, 72, 80, 60, 20, parent, (HMENU) IDC_EDIT[2], hPInstance, 0);
	SpamBotButton[0] = CreateWindowEx(0x00000000, WC_BUTTON, sSpammen, 0x50012F00, 10, 109, 205, 24, parent, (HMENU)IDC_BUTTON[0], hPInstance, 0);
	SpamBotButton[1] = CreateWindowEx(0x00000000, WC_BUTTON, sStop, 0x50012F00, 220, 109, 205, 24, parent, (HMENU)IDC_BUTTON[1], hPInstance, 0);
	SpamBotButton[2] = CreateWindowEx(0x00000000, WC_BUTTON, sLoad, 0x50012F00, 220, 31, 205, 24, parent, (HMENU)IDC_BUTTON[2], hPInstance, 0);
	SpamBotButton[3] = CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 220, 57, 205, 24, parent, (HMENU) IDC_BUTTON[3], hPInstance, 0);
	SpamBotButton[4] = CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 220, 83, 205, 24, parent, (HMENU)IDC_BUTTON[4], hPInstance, 0);

	for (int i = 0;i < _countof(SpamBotLabel);i++)
		SendMessage(SpamBotLabel[i], WM_SETFONT, (WPARAM) hFont, TRUE);
	
	SendMessage(SpamBotCombo[0], WM_SETFONT, (WPARAM)hFont, TRUE);
	for (int i = 0;i < _countof(sChatModes);i++)
		SendMessage(SpamBotCombo[0], CB_ADDSTRING, 0, (LPARAM)sChatModes[i]);
	SendMessage(SpamBotCombo[0], CB_SETCURSEL, 0, 0);

	for (int i = 0;i < _countof(SpamBotEdit);i++)
		SendMessage(SpamBotEdit[i], WM_SETFONT, (WPARAM) hFont, TRUE);

	for (int i = 0;i < _countof(SpamBotButton);i++)
		SendMessage(SpamBotButton[i], WM_SETFONT, (WPARAM) hFont, TRUE);

	DeactivateSpamBot();
	if (PathFindExtension(IniFullPath) == sExt)
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Load, 0, 0, 0);
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
			ActivateSpamBot();
			break;

		case 2001:
			DeactivateSpamBot();
			break;

		case 2002:
			Load(1);
			break;

		case 2003:
			Save();
			break;
			
		case 2004:
			Reset();
			break;
		}
		break;

	case WM_CREATE:
		CreateSpamBotContent(hwnd);
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
