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
	GetPrivateProfileString(sUppTool, sCountedUpp, "0", sValue, 32, IniFullPath);
	SendMessage(UppToolButton[0], BM_SETCHECK, atoi(sValue), 0);
	GetPrivateProfileString(sUppTool, sUppCount, "", sValue, 32, IniFullPath);
	SetWindowText(UppToolEdit[0], (atoi(sValue) < 1) ? "1" : sValue);

	GetPrivateProfileString(sUppTool, sSegiValue, "25040", sValue, 32, IniFullPath);
	SetWindowText(UppToolEdit[1], sValue);
	GetPrivateProfileString(sUppTool, sMagMetallValue, "25041", sValue, 32, IniFullPath);
	SetWindowText(UppToolEdit[2], sValue);

	GetPrivateProfileString(sUppTool, sMaxSlotUpp, "0", sValue, 32, IniFullPath);
	SendMessage(UppToolButton[1], BM_SETCHECK, atoi(sValue), 0);
	GetPrivateProfileString(sUppTool, sUppMaxSlot, "45", sValue, 32, IniFullPath);
	SetWindowText(UppToolEdit[3], sValue);
#if (DbgSession)
	PrintDbg("Successfully loaded (" + (std::string)IniFullPath + ")", "Mode " + std::to_string(iMode));
#endif
	return 0;
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

	tValue = std::to_string(IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]));
	WritePrivateProfileString(sUppTool, sCountedUpp, tValue.c_str(), IniFullPath);
	tValue = GetEditText(UppToolEdit[0]);
	WritePrivateProfileString(sUppTool, sUppCount, (std::stoi(tValue) < 1) ? "1" : tValue.c_str(), IniFullPath);
	tValue = GetEditText(UppToolEdit[1]);

	WritePrivateProfileString(sUppTool, sSegiValue, tValue.c_str(), IniFullPath);
	tValue = GetEditText(UppToolEdit[2]);
	WritePrivateProfileString(sUppTool, sMagMetallValue, tValue.c_str(), IniFullPath);

	tValue = std::to_string(IsDlgButtonChecked(WindowHandle, IDC_BUTTON[1]));
	WritePrivateProfileString(sUppTool, sMaxSlotUpp, tValue.c_str(), IniFullPath);
	tValue = GetEditText(UppToolEdit[3]);
	WritePrivateProfileString(sUppTool, sUppMaxSlot, (std::stoi(tValue) > 90) ? "90" : tValue.c_str(), IniFullPath);
#if (DbgSession)
	PrintDbg("Successfully saved to (" + (std::string)IniFullPath + ")", DbgOutput);
#endif
	return 0;
}

void Reset()
{
	const char* sDefDeactivated		= "0";
	const char* sDefUppCount		= "1";
	const char* sDefSegiValue		= "25040";
	const char* sDefMagMetallValue	= "25041";
	const char* sDefUppMaxSlot		= "45";
	int iDefDeactivated		= atoi(sDefDeactivated);
	int iDefUppCount		= atoi(sDefUppCount);
	int iDefSegiValue		= atoi(sDefSegiValue);
	int iDefMagMetallValue	= atoi(sDefMagMetallValue);

	if (PathFindExtension(IniFullPath) != sExt && PathFileExists(IniFullPath))
	{
		WritePrivateProfileString(sUppTool, sCountedUpp, sDefDeactivated, IniFullPath);
		WritePrivateProfileString(sUppTool, sUppCount, sDefUppCount, IniFullPath);
		WritePrivateProfileString(sUppTool, sSegiValue, sDefSegiValue, IniFullPath);
		WritePrivateProfileString(sUppTool, sMagMetallValue, sDefMagMetallValue, IniFullPath);
		WritePrivateProfileString(sUppTool, sMaxSlotUpp, sDefDeactivated, IniFullPath);
		WritePrivateProfileString(sUppTool, sUppMaxSlot, sDefUppMaxSlot, IniFullPath);
	}

	Load(2);
	return;
}

int GetSearchPattern()
{
	char Wert[3];

	GetPrivateProfileStringA(sSettings, sSearchPattern, "-1", Wert, 3, IniFullPath);
	return atoi(Wert);
}