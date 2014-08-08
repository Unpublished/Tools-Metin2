#include "Switch-Bot.h"
#include "GUI-Funcs.h"

int WINAPI MainWindow()
{
	std::string Title;
	Title = (std::string)sSwitchBot + " " + (std::string)Version + " Preview © by Unpublished";
	hPInstance = GetModuleHandle(0);
	InitCommonControls();
	RegisterClasses();
	hFont = CreateFont(11, 0, 0, 0, 575, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, sFont);
	WindowHandle = CreateWindowEx(WS_EX_TOPMOST, WND_CLASS_NAME, Title.c_str(), WS_SYSMENU + WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 505, 370, 0, 0, hPInstance, 0);
	ShowWindow(WindowHandle, SW_SHOWNORMAL);
	UpdateWindow(WindowHandle);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GUI, 0, 0, 0);
	return MessageLoop();
}

void CreateWindowContent(HWND parent)
{
	int IDC = 0, IDC2 = 0;
	int StartPos = 40, Abstand = 25;
	int SwitchBotStartenX = 10, SwitchBotStoppenX = 255, SwitchBotStarten_StoppenY = 191;
	int SwitchBot6_7StoppenX = 255, SwitchBot6_7Starten_StoppenY = 312;
	int SwitchBotButtonWeight = 232, SwitchBotButtonHeight = 25;

	TC_ITEM tci;
	tci.mask = TCIF_TEXT | TCIF_IMAGE | TCIF_PARAM;
	tci.iImage = -1;
	SwitchBotTab[0]	= CreateWindowEx(0x00000000, WC_TABCONTROLA, "", 0x54010040, 0, 0, 511, 343, parent, (HMENU) IDC_TAB[0], hPInstance, 0);
	SendMessage(SwitchBotTab[0], WM_SETFONT, (WPARAM) hFont, TRUE);
	for (int i = 0;i < 5;i++)
	{
		char Temp[8];
		sprintf_s(Temp, "Slot #%i", i + 1);
		tci.pszText	= Temp;
		tci.lParam	= 5002 + i;
		SendMessage(SwitchBotTab[0], TCM_INSERTITEMA, i, (LPARAM) &tci);
	}
	tci.pszText = SwitchBotOptions;
	tci.lParam	= 5007;
	SendMessage(SwitchBotTab[0], TCM_INSERTITEMA, 5, (LPARAM) &tci);
	
	SwitchBotLabel[0] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotFirstCat, 0x50000300, 222, 18, 67, 16, parent, (HMENU) IDC_STATIC[0], hPInstance, 0);
	SwitchBotLabel[1] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotSettingOne, 0x50000300, 71, 24, 74, 16, parent, (HMENU) IDC_STATIC[1], hPInstance, 0);
	SwitchBotLabel[2] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotSettingTwo, 0x50000300, 345, 24, 74, 16, parent, (HMENU) IDC_STATIC[2], hPInstance, 0);
	SwitchBotLabel[3] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotSecondCat, 0x50000300, 225, 215, 82, 16, parent, (HMENU) IDC_STATIC[3], hPInstance, 0);
	SwitchBotLabel[4] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotSettingOne, 0x50000300, 71, 221, 74, 16, parent, (HMENU) IDC_STATIC[4], hPInstance, 0);
	SwitchBotLabel[5] = CreateWindowEx(0x00000000, WC_STATIC, SwitchBotSettingTwo, 0x50000300, 345, 221, 74, 16, parent, (HMENU) IDC_STATIC[5], hPInstance, 0);
	for (int i = 0;i < 5;i++)
	{
		AlternativBoni[i][0]			= CreateWindowEx(0x00000000, WC_BUTTON, "", 0x50010003, 331, 25, 12, 12, parent, (HMENU) IDC_BUTTON[i], hPInstance, 0);
		SwitchBotButtonSave[i][0]		= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, SwitchBotStartenX, 163, 114, 25, parent, (HMENU) IDC_BUTTON[i + 5], hPInstance, 0);
		SwitchBotButtonReset[i][0]		= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 127, 163, 113, 25, parent, (HMENU) IDC_BUTTON[i + 10], hPInstance, 0);
		SwitchBotButtonSave[i][1]		= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 255, 163, 114, 25, parent, (HMENU) IDC_BUTTON[i + 15], hPInstance, 0);
		SwitchBotButtonReset[i][1]		= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 374, 163, 113, 25, parent, (HMENU) IDC_BUTTON[i + 20], hPInstance, 0);
		SwitchBotButtonStarten[i][0]	= CreateWindowEx(0x00000000, WC_BUTTON, sStart, 0x50012F00, SwitchBotStartenX, SwitchBotStarten_StoppenY, SwitchBotButtonWeight, SwitchBotButtonHeight, parent, (HMENU) IDC_BUTTON[i + 25], hPInstance, 0);
		SwitchBotButtonStoppen[i][0]	= CreateWindowEx(0x00000000, WC_BUTTON, sStart, 0x50012F00, SwitchBotStoppenX, SwitchBotStarten_StoppenY, SwitchBotButtonWeight, SwitchBotButtonHeight, parent, (HMENU) IDC_BUTTON[i + 30], hPInstance, 0);
		for (int j = 0;j < 7;j++)
		{
			if (j < 5)
			{
				SwitchBotBonusCombo[i][j]		= CreateWindowEx(0x00000000, WC_COMBOBOX, "", 0x50010203 + WS_VSCROLL, SwitchBotStartenX, StartPos + Abstand * j, 180, 19 + XP * 331, parent, (HMENU) IDC_COMBO[IDC], hPInstance, 0);
				SetWindowLong(SwitchBotBonusCombo[i][j], GWL_USERDATA, 5002 + i);
				SwitchBotBonusEdit[i][j]		= CreateWindowEx(0x00000200, WC_EDIT, "", 0x50012080, 195, StartPos + Abstand * j, 45, 19, parent, (HMENU) IDC_EDIT[IDC], hPInstance, 0);
				SendMessage(SwitchBotBonusEdit[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
				SetWindowLong(SwitchBotBonusEdit[i][j], GWL_USERDATA, 5002 + i);
				SwitchBotBonusCombo[i][j + 7]	= CreateWindowEx(0x00000000, WC_COMBOBOX, "", 0x50010203 + WS_VSCROLL, 255, StartPos + Abstand * j, 180, 19 + XP * 331, parent, (HMENU) IDC_COMBO[IDC + 25], hPInstance, 0);
				SetWindowLong(SwitchBotBonusCombo[i][j + 7], GWL_USERDATA, 5002 + i);
				SwitchBotBonusEdit[i][j + 7]	= CreateWindowEx(0x00000200, WC_EDIT, "", 0x50012080, 442, StartPos + Abstand * j, 45, 19, parent, (HMENU) IDC_EDIT[IDC + 25], hPInstance, 0);
				SendMessage(SwitchBotBonusEdit[i][j + 7], WM_SETFONT, (WPARAM) hFont, TRUE);
				SetWindowLong(SwitchBotBonusEdit[i][j + 7], GWL_USERDATA, 5002 + i);
				IDC += 1;
			}
			else
			{
				SwitchBotBonusCombo[i][j]		= CreateWindowEx(0x00000000, WC_COMBOBOX, "", 0x50010203 + WS_VSCROLL, SwitchBotStartenX, (212) + Abstand * (j - 4), 180, 19 + XP * 331, parent, (HMENU) IDC_COMBO[IDC2 + 50], hPInstance, 0);
				SetWindowLong(SwitchBotBonusCombo[i][j], GWL_USERDATA, 5002 + i);
				SwitchBotBonusEdit[i][j]		= CreateWindowEx(0x00000200, WC_EDIT, "", 0x50012080, 195, (212) + Abstand * (j - 4), 45, 19, parent, (HMENU) IDC_EDIT[IDC2 + 50], hPInstance, 0);
				SendMessage(SwitchBotBonusEdit[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
				SetWindowLong(SwitchBotBonusEdit[i][j], GWL_USERDATA, 5002 + i);
				SwitchBotBonusCombo[i][j + 7]	= CreateWindowEx(0x00000000, WC_COMBOBOX, "", 0x50010203 + WS_VSCROLL, 255, (212) + Abstand * (j - 4), 180, 19 + XP * 331, parent, (HMENU) IDC_COMBO[IDC2 + 60], hPInstance, 0);
				SetWindowLong(SwitchBotBonusCombo[i][j + 7], GWL_USERDATA, 5002 + i);
				SwitchBotBonusEdit[i][j + 7]	= CreateWindowEx(0x00000200, WC_EDIT, "", 0x50012080, 442, (212) + Abstand * (j - 4), 45, 19, parent, (HMENU) IDC_EDIT[IDC2 + 60], hPInstance, 0);
				SendMessage(SwitchBotBonusEdit[i][j + 7], WM_SETFONT, (WPARAM) hFont, TRUE);
				SetWindowLong(SwitchBotBonusEdit[i][j + 7], GWL_USERDATA, 5002 + i);
				IDC2 += 1;
			}
		}
		AlternativBoni[i][1]			= CreateWindowEx(0x00000000, WC_BUTTON, "", 0x50010003, 331, 222, 12, 12, parent, (HMENU) IDC_BUTTON[i + 35], hPInstance, 0);
		SwitchBotButtonSave[i][2]		= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, SwitchBotStartenX, 282, 114, 25, parent, (HMENU) IDC_BUTTON[i + 40], hPInstance, 0);
		SwitchBotButtonReset[i][2]		= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 127, 282, 113, 25, parent, (HMENU) IDC_BUTTON[i + 45], hPInstance, 0);
		SwitchBotButtonSave[i][3]		= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 255, 282, 114, 25, parent, (HMENU) IDC_BUTTON[i + 50], hPInstance, 0);
		SwitchBotButtonReset[i][3]		= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 374, 282, 113, 25, parent, (HMENU) IDC_BUTTON[i + 55], hPInstance, 0);
		SwitchBotButtonStarten[i][1]	= CreateWindowEx(0x00000000, WC_BUTTON, sStart, 0x50012F00, SwitchBotStartenX, SwitchBot6_7Starten_StoppenY, SwitchBotButtonWeight, SwitchBotButtonHeight, parent, (HMENU) IDC_BUTTON[i + 60], hPInstance, 0);
		SwitchBotButtonStoppen[i][1]	= CreateWindowEx(0x00000000, WC_BUTTON, sStart, 0x50012F00, SwitchBot6_7StoppenX, SwitchBot6_7Starten_StoppenY, SwitchBotButtonWeight, SwitchBotButtonHeight, parent, (HMENU) IDC_BUTTON[i + 65], hPInstance, 0);
	}
	SwitchBotLabel[6]	= CreateWindowEx(0x00000000, WC_STATIC, "Sleep-Zeit in ms:", 0x50000300, SwitchBotStartenX, 26, 86, 17, parent, (HMENU) IDC_STATIC[6], hPInstance, 0);
	SwitchBotEdit[0]	= CreateWindowEx(0x00000200, WC_EDIT, "500", 0x50012080, 99, 25, 60, 19, parent, (HMENU) IDC_EDIT[70], hPInstance, 0);

	SwitchBotLabel[7]	= CreateWindowEx(0x00000000, WC_STATIC, "\"Gegenstand verzaubern\" Value:", 0x50000300, SwitchBotStartenX, 50, 166, 17, parent, (HMENU) IDC_STATIC[7], hPInstance, 0);
	SwitchBotEdit[1]	= CreateWindowEx(0x00000200, WC_EDIT, "71084", 0x50012080, 179, 48, 60, 19, parent, (HMENU) IDC_EDIT[71], hPInstance, 0);
	SwitchBotButton[0]	= CreateWindowEx(0x00000000, WC_BUTTON, "Auslesen", 0x50012F00, 242, 48, 75, 20, parent, (HMENU) IDC_BUTTON[70], hPInstance, 0);

	SwitchBotLabel[8]	= CreateWindowEx(0x00000000, WC_STATIC, "\"Gegenstand segnen\" Value:", 0x50000300, 29, 74, 145, 17, parent, (HMENU) IDC_STATIC[8], hPInstance, 0);
	SwitchBotEdit[2]	= CreateWindowEx(0x00000200, WC_EDIT, "71052", 0x50012080, 179, 72, 60, 19, parent, (HMENU) IDC_EDIT[72], hPInstance, 0);
	SwitchBotButton[1]	= CreateWindowEx(0x00000000, WC_BUTTON, "Auslesen", 0x50012F00, 242, 72, 75, 20, parent, (HMENU) IDC_BUTTON[71], hPInstance, 0);

	SwitchBotButton[2]	= CreateWindowEx(0x00000000, WC_BUTTON, "", 0x50010003, SwitchBotStartenX, 98, 12, 12, parent, (HMENU) IDC_BUTTON[72], hPInstance, 0);
	SwitchBotLabel[9]	= CreateWindowEx(0x00000000, WC_STATIC, "Nachkäufer", 0x50000300, 25, 97, 58, 16, parent, (HMENU) IDC_STATIC[9], hPInstance, 0);

	SwitchBotButton[3]	= CreateWindowEx(0x00000000, WC_BUTTON, "", 0x50010003, SwitchBotStartenX, 119, 12, 12, parent, (HMENU) IDC_BUTTON[73], hPInstance, 0);
	SwitchBotLabel[10]	= CreateWindowEx(0x00000000, WC_STATIC, "Item-Schutz", 0x50000300, 25, 118, 62, 16, parent, (HMENU) IDC_STATIC[10], hPInstance, 0);

	SwitchBotLabel[11]	= CreateWindowEx(0x00000000, WC_STATIC, "Definiere den Slot für Slot #1:", 0x50000300, SwitchBotStartenX, SwitchBot6_7Starten_StoppenY - 25, 156, 17, parent, (HMENU) IDC_STATIC[11], hPInstance, 0);
	SwitchBotEdit[4]	= CreateWindowEx(0x00000200, WC_EDIT, "1", 0x50012080, 169, SwitchBot6_7Starten_StoppenY - 26, 25, 19, parent, (HMENU) IDC_EDIT[73], hPInstance, 0);

	SwitchBotButton[4]	= CreateWindowEx(0x00000000, WC_BUTTON, sLoad, 0x50012F00, 5, SwitchBot6_7Starten_StoppenY, 160, 25, parent, (HMENU)IDC_BUTTON[74], hPInstance, 0);
	SwitchBotButton[5]	= CreateWindowEx(0x00000000, WC_BUTTON, sSave, 0x50012F00, 5 + 160 + 5, SwitchBot6_7Starten_StoppenY, 160, 25, parent, (HMENU) IDC_BUTTON[75], hPInstance, 0);
	SwitchBotButton[6]	= CreateWindowEx(0x00000000, WC_BUTTON, sReset, 0x50012F00, 5 + 160*2 + 5*2, SwitchBot6_7Starten_StoppenY, 160, 25, parent, (HMENU)IDC_BUTTON[76], hPInstance, 0);

	for (int i = 0;i < sizeof(SwitchBotLabel)/sizeof(SwitchBotLabel[0]);i++)
	{
		SendMessage(SwitchBotLabel[i], WM_SETFONT, (WPARAM) hFont, TRUE);
		if (i > 5)
		{
			SetWindowLong(SwitchBotLabel[i], GWL_USERDATA, 5007);
			ShowWindow(SwitchBotLabel[i], SW_HIDE);
		}
			
	}
	for (int i = 0;i < sizeof(SwitchBotButton)/sizeof(SwitchBotButton[0]);i++)
	{
		SendMessage(SwitchBotButton[i], WM_SETFONT, (WPARAM) hFont, TRUE);
		SetWindowLong(SwitchBotButton[i], GWL_USERDATA, 5007);
		ShowWindow(SwitchBotButton[i], SW_HIDE);
	}
	for (int i = 0;i < sizeof(SwitchBotEdit)/sizeof(SwitchBotEdit[0]);i++)
	{
		SendMessage(SwitchBotEdit[i], WM_SETFONT, (WPARAM) hFont, TRUE);
		SetWindowLong(SwitchBotEdit[i], GWL_USERDATA, 5007);
		ShowWindow(SwitchBotEdit[i], SW_HIDE);
	}
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			SendMessage(AlternativBoni[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			SetWindowLong(AlternativBoni[i][j], GWL_USERDATA, 5002 + i);
			SendMessage(SwitchBotButtonStarten[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			SetWindowLong(SwitchBotButtonStarten[i][j], GWL_USERDATA, 5002 + i);
			SendMessage(SwitchBotButtonStoppen[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			SetWindowLong(SwitchBotButtonStoppen[i][j], GWL_USERDATA, 5002 + i);

			if (!i)
				continue;

			ShowWindow(AlternativBoni[i][j], SW_HIDE);
			ShowWindow(SwitchBotButtonStarten[i][j], SW_HIDE);
			ShowWindow(SwitchBotButtonStoppen[i][j], SW_HIDE);
		}
		for (int j = 0;j < 4;j++)
		{
			SendMessage(SwitchBotButtonSave[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			SetWindowLong(SwitchBotButtonSave[i][j], GWL_USERDATA, 5002 + i);
			SendMessage(SwitchBotButtonReset[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			SetWindowLong(SwitchBotButtonReset[i][j], GWL_USERDATA, 5002 + i);

			if (!i)
				continue;

			ShowWindow(SwitchBotButtonSave[i][j], SW_HIDE);
			ShowWindow(SwitchBotButtonReset[i][j], SW_HIDE);
		}
	}

	InitSwitchBot();
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetAddies, 0, 0, 0);
}

LRESULT CALLBACK WndThread(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wparam))
		{
		case 2005:
			SaveBonis(0, 0, 1);
			break;
			
		case 2006:
			SaveBonis(1, 0, 1);
			break;
			
		case 2007:
			SaveBonis(2, 0, 1);
			break;

		case 2008:
			SaveBonis(3, 0, 1);
			break;

		case 2009:
			SaveBonis(4, 0, 1);
			break;

		case 2010:
			ResetBonis(0, 0, 1);
			break;
			
		case 2011:
			ResetBonis(1, 0, 1);
			break;

		case 2012:
			ResetBonis(2, 0, 1);
			break;

		case 2013:
			ResetBonis(3, 0, 1);
			break;

		case 2014:
			ResetBonis(4, 0, 1);
			break;

		case 2015:
			SaveBonis(0, 0, 2);
			break;
			
		case 2016:
			SaveBonis(1, 0, 2);
			break;

		case 2017:
			SaveBonis(2, 0, 2);
			break;

		case 2018:
			SaveBonis(3, 0, 2);
			break;

		case 2019:
			SaveBonis(4, 0, 2);
			break;

		case 2020:
			ResetBonis(0, 0, 2);
			break;
			
		case 2021:
			ResetBonis(1, 0, 2);
			break;

		case 2022:
			ResetBonis(2, 0, 2);
			break;

		case 2023:
			ResetBonis(3, 0, 2);
			break;

		case 2024:
			ResetBonis(4, 0, 2);
			break;

		case 2040:
			SaveBonis(0, 1, 1);
			break;
			
		case 2041:
			SaveBonis(1, 1, 1);
			break;

		case 2042:
			SaveBonis(2, 1, 1);
			break;

		case 2043:
			SaveBonis(3, 1, 1);
			break;

		case 2044:
			SaveBonis(4, 1, 1);
			break;

		case 2045:
			ResetBonis(0, 1, 1);
			break;

		case 2046:
			ResetBonis(1, 1, 1);
			break;

		case 2047:
			ResetBonis(2, 1, 1);
			break;

		case 2048:
			ResetBonis(3, 1, 1);
			break;

		case 2049:
			ResetBonis(4, 1, 1);
			break;

		case 2050:
			SaveBonis(0, 1, 2);
			break;
			
		case 2051:
			SaveBonis(1, 1, 2);
			break;

		case 2052:
			SaveBonis(2, 1, 2);
			break;

		case 2053:
			SaveBonis(3, 1, 2);
			break;

		case 2054:
			SaveBonis(4, 1, 2);
			break;

		case 2055:
			ResetBonis(0, 1, 2);
			break;
			
		case 2056:
			ResetBonis(1, 1, 2);
			break;

		case 2057:
			ResetBonis(2, 1, 2);
			break;

		case 2058:
			ResetBonis(3, 1, 2);
			break;

		case 2059:
			ResetBonis(4, 1, 2);
			break;

		case 2025: //Switch-Bot 1-5 Slot #1 starten
#if (DbgSession)
			//NetPointer = 0x70A0BC; Shiro???
			NetPointer = 0x11121D0;//World of Metin2
			SendItemUseToItemCall = 0x4E2420;//World of Metin2
			SendItemUseToItem(10, 49);
#endif
			ActivateSwitchBot(0, 0);
			break;

		case 2030: //Switch-Bot 1-5 Slot #1 stoppen
			DeactivateSwitchBot(0, 0);
			break;
			
		case 2060: //Switch-Bot 6-7 Slot #1 starten
			ActivateSwitchBot(0, 1);
			break;

		case 2065: //Switch-Bot 6-7 Slot #1 stoppen
			DeactivateSwitchBot(0, 1);
			break;

		case 2026: //Switch-Bot 1-5 Slot #2 starten
			ActivateSwitchBot(1, 0);
			break;

		case 2031: //Switch-Bot 1-5 Slot #2 stoppen
			DeactivateSwitchBot(1, 0);
			break;

		case 2061: //Switch-Bot 6-7 Slot #2 starten
			ActivateSwitchBot(1, 1);
			break;

		case 2066: //Switch-Bot 6-7 Slot #2 stoppen
			DeactivateSwitchBot(1, 1);
			break;

		case 2027: //Switch-Bot 1-5 Slot #3 starten
			ActivateSwitchBot(2, 0);
			break;

		case 2032: //Switch-Bot 1-5 Slot #3 stoppen
			DeactivateSwitchBot(2, 0);
			break;
			
		case 2062: //Switch-Bot 6-7 Slot #3 stoppen
			ActivateSwitchBot(2, 1);
			break;

		case 2067: //Switch-Bot 6-7 Slot #3 stoppen
			DeactivateSwitchBot(2, 1);
			break;

		case 2028: //Switch-Bot 1-5 Slot #4 starten
			ActivateSwitchBot(3, 0);
			break;

		case 2033: //Switch-Bot 1-5 Slot #4 stoppen
			DeactivateSwitchBot(3, 0);
			break;

		case 2063: //Switch-Bot 6-7 Slot #4 starten
			ActivateSwitchBot(3, 1);
			break;

		case 2068: //Switch-Bot 6-7 Slot #4 stoppen
			DeactivateSwitchBot(3, 1);
			break;
			
		case 2029: //Switch-Bot 1-5 Slot #5 starten
			ActivateSwitchBot(4, 0);
			break;

		case 2034: //Switch-Bot 1-5 Slot #5 stoppen
			DeactivateSwitchBot(4, 0);
			break;

		case 2064: //Switch-Bot 6-7 Slot #5 starten
			ActivateSwitchBot(4, 1);
			break;

		case 2069: //Switch-Bot 6-7 Slot #5 stoppen
			DeactivateSwitchBot(4, 1);
			break;

		case 2070:
			SwitchItemAuslesen(0);
			break;

		case 2071:
			SwitchItemAuslesen(1);
			break;

		case 2074:
			Load(1);
			break;

		case 2075:
			Save();
			break;

		case 2076:
			Reset();
			break;
		}
		break;

	case WM_NOTIFY:
		switch (((LPNMHDR) lparam)->code)
		{
		case TCN_SELCHANGING:
		case TCN_SELCHANGE:
			{
				TC_ITEM tci = {TCIF_PARAM};
				LPNMHDR pnmh = (LPNMHDR) lparam;
				int show = (pnmh->code == TCN_SELCHANGE) ? SW_SHOW : SW_HIDE;
				HWND ctl = GetWindow(hwnd, GW_CHILD);
				TabCtrl_GetItem(pnmh->hwndFrom, TabCtrl_GetCurSel(pnmh->hwndFrom), &tci);
				for (; ctl; ctl = GetWindow(ctl, GW_HWNDNEXT))
					if (GetWindowLong(ctl, GWL_USERDATA) == tci.lParam) ShowWindow(ctl, show);
			}
			break;
		}
		break;

#if (!XP)
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wparam, TRANSPARENT);
		return (int)GetStockObject(COLOR_WINDOW);
#endif

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
