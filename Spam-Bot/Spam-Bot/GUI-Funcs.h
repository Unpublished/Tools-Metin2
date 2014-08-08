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
	tValue = GetEditText(SpamBotEdit[0]);
	WritePrivateProfileString(Spam_Bot, sSpamText, tValue.c_str(), IniFullPath);

	tValue = std::to_string(SendMessage(SpamBotCombo[0], CB_GETCURSEL, (WPARAM)0, (LPARAM)0));
	WritePrivateProfileString(Spam_Bot, sChatTyp, tValue.c_str(), IniFullPath);

	tValue = GetEditText(SpamBotEdit[1]);
	WritePrivateProfileString(Spam_Bot, sAnzahl, (std::stoi(tValue) == 0) ? "0" : tValue.c_str(), IniFullPath);
	
	tValue = GetEditText(SpamBotEdit[2]);
	WritePrivateProfileString(Spam_Bot, "Sleep-Zeit", (std::stoi(tValue) < iDefMinSleep) ? sDefMinSleep : tValue.c_str(), IniFullPath);
	return 0;
}

int Load(int iMode)
{
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

	char Wert[2048];

	GetPrivateProfileString(Spam_Bot, "ChatOccurrence", "-1", Wert, 128, IniFullPath);
	ChatOccurrence = atoi(Wert);

	GetPrivateProfileString(Spam_Bot, sSpamText, "", Wert, 128, IniFullPath);
	SetWindowText(SpamBotEdit[0], Wert);
	
	GetPrivateProfileString(Spam_Bot, sChatTyp, "0", Wert, 128, IniFullPath);
	SendMessage(SpamBotCombo[0], CB_SETCURSEL, atoi(Wert), 0);

	GetPrivateProfileString(Spam_Bot, sAnzahl, "0", Wert, 128, IniFullPath);
	SetWindowText(SpamBotEdit[1], Wert);
	
	GetPrivateProfileString(Spam_Bot, "Sleep-Zeit", "750", Wert, 128, IniFullPath);
	SetWindowText(SpamBotEdit[2], Wert);
	return 0;
}

void Reset()
{
	WritePrivateProfileString(Spam_Bot, "ChatOccurrence", "-1", IniFullPath);
	WritePrivateProfileString(Spam_Bot, sSpamText, "", IniFullPath);
	WritePrivateProfileString(Spam_Bot, sChatTyp, "0", IniFullPath);
	WritePrivateProfileString(Spam_Bot, sAnzahl, "0", IniFullPath);
	WritePrivateProfileString(Spam_Bot, "Sleep-Zeit", "750", IniFullPath);

	Load(2);
}

int GetSearchPattern()
{
	char Wert[3];

	GetPrivateProfileString(sSettings, sSearchPattern, "-1", Wert, 3, IniFullPath);
	return atoi(Wert);
}

void GUI()
{
	std::string tValue;
	while (true)
	{
		if (!SpamBotThread)
		{
			SpamText = GetEditText(SpamBotEdit[0]);
			tValue = GetEditText(SpamBotEdit[2]);

			if (SpamText.empty())
			{
				EnableWindow(SpamBotButton[0], false);
				while (SpamText.empty())
				{
					SpamText = GetEditText(SpamBotEdit[0]);
					Sleep(250);
				}
			}
			else
			{
				EnableWindow(SpamBotButton[0], true);
			}
				
			if (std::stoi(tValue) < 750)
			{
				EnableWindow(SpamBotButton[0], false);
				while (std::stoi(tValue) < 750)
				{
					tValue = GetEditText(SpamBotEdit[2]);
					Sleep(250);
				}
			}
			else
			{
				EnableWindow(SpamBotButton[0], true);
			}

			SleepTime = (std::stoi(tValue) < 750) ? 750 : std::stoi(tValue);
			Sleep(200);
		}
		else
		{
			Sleep(SleepTime);
		}
	}
}