void Initialize()
{
	switch (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]))
	{
		case BST_CHECKED:
			ActivateInstantPickUp();
			break;

		default:
			DeactivateInstantPickUp();
			break;
	}
}

void DeleteUnused(char *KeyName)
{
	const char *sNotFound = "<not found>";
	char sValue[8];
	if (PathFileExists(IniFullPath))
	{
		GetPrivateProfileString(PickUp_Bot, KeyName, sNotFound, sValue, 8, IniFullPath);
		if (strcmp(sValue, sNotFound))
			WritePrivateProfileString(PickUp_Bot, KeyName, 0, IniFullPath);
	}
}

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
	tValue = GetEditText(PickUpBotEdit[0]);
	WritePrivateProfileString(PickUp_Bot, "Sleep-Zeit", (std::stoi(tValue) < iDefMinSleep) ? sDefMinSleep : tValue.c_str(), IniFullPath);
	tValue = std::to_string(IsDlgButtonChecked(WindowHandle, IDC_BUTTON[1]));
	WritePrivateProfileString(PickUp_Bot, "Instant-PickUp", tValue.c_str(), IniFullPath);
	return 0;
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

	char sValue[2048];
	GetPrivateProfileString(PickUp_Bot, "Sleep-Zeit", sDefSleep, sValue, 8, IniFullPath);
	SetWindowText(PickUpBotEdit[0], sValue);
	
	GetPrivateProfileString(PickUp_Bot, "Instant-PickUp", "0", sValue, 8, IniFullPath);
	SendMessage(PickUpBotButton[0], BM_SETCHECK, atoi(sValue), 0);

	Initialize();
	return 0;
}

void Reset()
{
	if (PathFindExtension(IniFullPath) != sExt && PathFileExists(IniFullPath))
	{
		WritePrivateProfileString(PickUp_Bot, "Sleep-Zeit", sDefSleep, IniFullPath);
		WritePrivateProfileString(PickUp_Bot, "Instant-PickUp", "0", IniFullPath);
	}

	Load(2);
	return;
}

int GetSearchPattern()
{
	char sValue[3];

	GetPrivateProfileString(sSettings, sSearchPattern, "-1", sValue, 3, IniFullPath);
	return atoi(sValue);
}

void GUI()
{
	char sValue[8];
	while (true)
	{
		if (!PickUpBotThread)
		{
			GetWindowText(PickUpBotEdit[0], sValue, 8);
			
			if (atoi(sValue) < iDefSleep && IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_UNCHECKED)
			{
				EnableWindow(PickUpBotButton[1], false);
				while (atoi(sValue) < iDefSleep && IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_UNCHECKED)
				{
					GetWindowText(PickUpBotEdit[0], sValue, 8);
					Sleep(250);
				}
			}
			else if (atoi(sValue) < iDefMinSleep && IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_CHECKED)
			{
				EnableWindow(PickUpBotButton[1], false);
				while (atoi(sValue) < iDefMinSleep && IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_CHECKED)
				{
					GetWindowText(PickUpBotEdit[0], sValue, 8);
					Sleep(250);
				}
			}
			else
			{
				EnableWindow(PickUpBotButton[1], true);
			}

			SleepTime = (atoi(sValue) < iDefSleep) ? iDefSleep : atoi(sValue);
			Sleep(250);
		}
		else
		{
			Sleep(SleepTime);
		}
	}
}