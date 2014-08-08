void LoadBonis(int Slot, int Mode, int Setting);

int Save()
{
#if (DbgSession)
	PrintDbg("Saving ini", DbgOutput);
#endif
	if (!ValidateIni())
	{
#if (DbgSession)
		PrintDbg("Error while validating ini to be saved (" + (std::string)IniFullPath + ")", DbgOutput);
#endif
		return 1;
	}

	std::string tValue;

	tValue = GetEditText(SwitchBotEdit[0]);
	WritePrivateProfileString(sSwitchBot, "Sleep-Zeit", (std::stoi(tValue) < iDefSleep) ? sDefSleep : tValue.c_str(), IniFullPath);
	tValue = GetEditText(SwitchBotEdit[1]);
	WritePrivateProfileString(sSwitchBot, "Switch-Item 1-5 Value", tValue.c_str(), IniFullPath);
	tValue = GetEditText(SwitchBotEdit[2]);
	WritePrivateProfileString(sSwitchBot, "Switch-Item 6 & 7 Value", tValue.c_str(), IniFullPath);
	tValue = std::to_string(IsDlgButtonChecked(WindowHandle, IDC_BUTTON[72]));
	WritePrivateProfileString(sSwitchBot, "Nachkäufer", tValue.c_str(), IniFullPath);
	tValue = std::to_string(IsDlgButtonChecked(WindowHandle, IDC_BUTTON[73]));
	WritePrivateProfileString(sSwitchBot, "Item-Schutz", tValue.c_str(), IniFullPath);
	return 0;
}

void SaveBonis(int Slot, int Mode, int Setting)
{
	char Eintrag[128], sValue[8];
	CheckIni(false);

	if (Setting == 1)
	{
		for (int j = 0 + 5 * Mode; j < 5 + 2 * Mode; j++)
		{
			int Auswahl = (SendMessage(SwitchBotBonusCombo[Slot][j], CB_GETCURSEL, 0, 0));
			sprintf_s(sValue, 8, "%i", Auswahl);
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus #%i", Slot + 1, Mode + 1, j + 1);
			WritePrivateProfileString(sSwitchBot, Eintrag, sValue, IniFullPath);
			GetWindowText(SwitchBotBonusEdit[Slot][j], sValue, 8);
			sprintf_s(sValue, 8, "%i", atoi(sValue));
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus-Wert #%i", Slot + 1, Mode + 1, j + 1);
			WritePrivateProfileString(sSwitchBot, Eintrag, sValue, IniFullPath);
		}
	}
	else
	{
		sprintf_s(Eintrag, "Slot #%i Alternativ j #%i", Slot + 1, Mode + 1);
		sprintf_s(sValue, "%i", IsDlgButtonChecked(WindowHandle, IDC_BUTTON[Slot + 35 * Mode]));
		WritePrivateProfileString(sSwitchBot, Eintrag, sValue, IniFullPath);
		for (int j = 7 + 5 * Mode; j < 12 + 2 * Mode; j++)
		{
			int Auswahl = (SendMessage(SwitchBotBonusCombo[Slot][j], CB_GETCURSEL, 0, 0));
			sprintf_s(sValue, 8, "%i", Auswahl);
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus #%i", Slot + 1, Mode + 1, j - 6);
			WritePrivateProfileString(sSwitchBot, Eintrag, sValue, IniFullPath);
			GetWindowText(SwitchBotBonusEdit[Slot][j], sValue, 8);
			sprintf_s(sValue, 8, "%i", atoi(sValue));
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus-Wert #%i", Slot + 1, Mode + 1, j - 6);
			WritePrivateProfileString(sSwitchBot, Eintrag, sValue, IniFullPath);
		}
	}
	memset(&Eintrag[0], 0, sizeof(Eintrag));
	memset(&sValue[0], 0, sizeof(sValue));
}

int Load(int iMode)
{
#if (DbgSession)
	PrintDbg("Loading ini", sDbgOutput);
#endif
	switch (iMode)
	{
		case 0:
		{
			if (PathFindExtension(IniFullPath) != sExt)
			{
				std::string sPathEx;
				sPathEx = (std::string)IniFullPath + (std::string)sExt;
				if (!PathFileExists(sPathEx.c_str()))
					return 1;
				PathAddExtension(IniFullPath, sExt);
			}
			break;
		}
		case 1:
		{
			if (!CheckIni(TRUE))
				return 2;
			break;
		}
	}

	char sValue[32];
	GetPrivateProfileString(sSwitchBot, "Sleep-Zeit", "", sValue, 32, IniFullPath);
	SetWindowText(SwitchBotEdit[0], (!atoi(sValue)) ? "500" : sValue);
	
	GetPrivateProfileString(sSwitchBot, "Switch-Item 1-5 Value", "71084", sValue, 32, IniFullPath);
	SetWindowText(SwitchBotEdit[1], sValue);

	GetPrivateProfileString(sSwitchBot, "Switch-Item 6 & 7 Value", "71052", sValue, 32, IniFullPath);
	SetWindowText(SwitchBotEdit[2], sValue);
	
	GetPrivateProfileString(sSwitchBot, "Nachkäufer", "0", sValue, 32, IniFullPath);
	SendMessage(SwitchBotButton[2], BM_SETCHECK, atoi(sValue), 0);
	GetPrivateProfileString(sSwitchBot, "Item-Schutz", "0", sValue, 32, IniFullPath);
	SendMessage(SwitchBotButton[3], BM_SETCHECK, atoi(sValue), 0);

	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 2;j++)
		{
			for (int k = 1; k <= 2; k++)
				LoadBonis(i, j, k);
		}
	}
	return 0;
}

void LoadBonis(int Slot, int Mode, int Setting)
{
	switch (0)
	{
		case 0:
		{
			if (PathFindExtension(IniFullPath) != sExt)
			{
				std::string sPathEx;
				sPathEx = (std::string)IniFullPath + (std::string)sExt;
				if (!PathFileExists(sPathEx.c_str()))
					/*return;*/
				PathAddExtension(IniFullPath, sExt);
			}
			break;
		}
		case 1:
		{
			if (!CheckIni(TRUE))
				return;
			break;
		}
	}
	char Eintrag[128], sValue[8];
	if (Setting == 1)
	{
		for (int j = 0 + 7 * Mode;j < 5 + 2 * Mode;j++)
		{
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus #%i", Slot + 1, Mode + 1, j + 1);
			GetPrivateProfileString(sSwitchBot, Eintrag, "-1", sValue, 8, IniFullPath);
			SendMessage(SwitchBotBonusCombo[Slot][j], CB_SETCURSEL, atoi(sValue), 0);
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus-Wert #%i", Slot + 1, Mode + 1, j + 1);
			GetPrivateProfileString(sSwitchBot, Eintrag, 0, sValue, 8, IniFullPath);
			SetWindowText(SwitchBotBonusEdit[Slot][j], (atoi(sValue) == 0) ? "" : sValue);
		}
	}
	else
	{
		sprintf_s(Eintrag, "Slot #%i Alternativ j #%i", Slot + 1, Mode + 1);
		GetPrivateProfileString(sSwitchBot, Eintrag, "0", sValue, 8, IniFullPath);
		SendMessage(AlternativBoni[Slot][Mode], BM_SETCHECK, atoi(sValue), 0);
		for (int j = 7 + 5 * Mode;j < 12 + 2 * Mode;j++)
		{
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus #%i", Slot + 1, Mode + 1, j - 6);
			GetPrivateProfileString(sSwitchBot, Eintrag, "-1", sValue, 8, IniFullPath);
			SendMessage(SwitchBotBonusCombo[Slot][j], CB_SETCURSEL, atoi(sValue), 0);
			sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus-Wert #%i", Slot + 1, Mode + 1, j - 6);
			GetPrivateProfileString(sSwitchBot, Eintrag, 0, sValue, 8, IniFullPath);
			SetWindowText(SwitchBotBonusEdit[Slot][j], (atoi(sValue) == 0) ? "" : sValue);
		}
	}
	return;
}

void Reset()
{
	if (PathFindExtension(IniFullPath) != sExt && PathFileExists(IniFullPath))
	{
		WritePrivateProfileString(sSwitchBot, "Sleep-Zeit", "500", IniFullPath);
		WritePrivateProfileString(sSwitchBot, "Switch-Item 1-5 Value", "71084", IniFullPath);
		WritePrivateProfileString(sSwitchBot, "Switch-Item 6 & 7 Value", "71052", IniFullPath);
		WritePrivateProfileString(sSwitchBot, "Nachkäufer", "0", IniFullPath);
		WritePrivateProfileString(sSwitchBot, "Item-Schutz", "0", IniFullPath);
	}

	Load(2);
	return;
}

void ResetBonis(int Slot, int Mode, int Setting)
{
	if (PathFindExtension(IniFullPath) != sExt && PathFileExists(IniFullPath))
	{
		char Eintrag[128];
		if (Setting == 1)
		{
			for (int j = 0 + 5 * Mode; j < 5 + 2 * Mode; j++)
			{
				sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus #%i", Slot + 1, Mode + 1, j + 1);
				WritePrivateProfileString(sSwitchBot, Eintrag, "-1", IniFullPath);
				sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #1 Bonus-Wert #%i", Slot + 1, Mode + 1, j + 1);
				WritePrivateProfileString(sSwitchBot, Eintrag, "0", IniFullPath);
			}
		}
		else
		{
			sprintf_s(Eintrag, "Slot #%i Alternativ j #%i", Slot + 1, Mode + 1);
			WritePrivateProfileString(sSwitchBot, Eintrag, "0", IniFullPath);
			for (int j = 7 + 5 * Mode; j < 12 + 2 * Mode; j++)
			{
				sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus #%i", Slot + 1, Mode + 1, j - 6);
				WritePrivateProfileString(sSwitchBot, Eintrag, "-1", IniFullPath);
				sprintf_s(Eintrag, 128, "Slot #%i Modus #%i Einstellung #2 Bonus-Wert #%i", Slot + 1, Mode + 1, j - 6);
				WritePrivateProfileString(sSwitchBot, Eintrag, "0", IniFullPath);
			}
		}
	}
	LoadBonis(Slot, Mode, Setting);
}

void InitSwitchBot()
{
	for (int i = 0;i < 5;i++)
	{
		for (int j = 0;j < 14;j++)
		{
			SendMessage(SwitchBotBonusCombo[i][j], WM_SETFONT, (WPARAM) hFont, TRUE);
			for (int k = 0;k < _countof(Boni);k++)
				SendMessage(SwitchBotBonusCombo[i][j], CB_ADDSTRING, 0, (LPARAM) Boni[k]);

			if (i)
			{
				ShowWindow(SwitchBotBonusCombo[i][j], SW_HIDE);
				ShowWindow(SwitchBotBonusEdit[i][j], SW_HIDE);
			}
		}
		for (int j = 0;j < 2;j++)
		{
			for (int k = 1; k <= 2; k++)
				LoadBonis(i, j, k);

			DeactivateSwitchBot(i, j);
		}
	}
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Load, (LPVOID)0, 0, 0);
}

int GetSearchPattern()
{
	char sValue[3];

	GetPrivateProfileString(sSettings, sSearchPattern, "-1", sValue, 3, IniFullPath);
	return atoi(sValue);
}

void GUI()
{
	int iPage;
	bool TabCheck = false;
	while (true)
	{
		iPage = TabCtrl_GetCurSel(SwitchBotTab[0]);
		if (iPage == 5 && TabCheck == false)
		{
			for (int i = 0;i < 6;i++)
				ShowWindow(SwitchBotLabel[i], SW_HIDE);

			TabCheck = true;
		}
		else if (iPage < 5 && TabCheck == true)
		{
			for (int i = 0;i < 6;i++)
				ShowWindow(SwitchBotLabel[i], SW_SHOWNORMAL);

			TabCheck = false;
		}

		if ((IsSwitchBotRunning) & (SwitchBots == 0))
		{
			EnableWindow(SwitchBotEdit[4], true);
			IsSwitchBotRunning = false;
		}
		Sleep(50);
	}
}