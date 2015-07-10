#if !defined(InviDropper)
#include <direct.h>
#endif
#include <Windows.h>
#if !defined(InviDropper)
#include <stdio.h>
#include <Shlwapi.h>
#include <Psapi.h>
#endif

char TBD[256];
#if !defined(InviDropper)
#include <algorithm>
#include <string>
#include <regex>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

char IniPath[2048], IniFullPath[2048];
char ServerName[2048], WorkingDir[2048];
int iClientMod;
HANDLE hProcess;
DWORD ProcessID;

std::string GetEditText(HWND hControl);
#endif
std::string to_hexstring(unsigned int _Val);


__forceinline bool DataCompare(const unsigned char* address, const unsigned char* signature, const char* mask);
DWORD FindPatternInternal(const unsigned char* address, size_t size, const unsigned char* signature, const char* mask, unsigned short ignore);
DWORD FindPattern(const unsigned char* address, size_t size, const unsigned char* signature, const char* mask, unsigned short ignore);
DWORD RelativeToAbsolute(DWORD Offset);

#if !defined(InviDropper)
BOOL CheckIni(BOOL Loading);
bool ForceValidation(bool bAsk);
bool ValidateIni();
void SetNewIniLocation(char OldLocation[2048]);
#endif
void PrintDbg(std::string sText, std::string sTitle);
void InitComponents();
void SetAddies();

#include "..\..\Classes\GUI Class.h"
#include "..\..\Classes\Metin2 Class.h"
#include "GUI.h"

#if !defined(InviDropper)
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "Psapi.lib")
#endif
#pragma comment(lib, "Version.lib")

#if (!XP)
	#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

__declspec(dllexport) BOOL WINAPI Init()
{
    return 0;
}

std::string to_hexstring(unsigned int _Val)
{
	char _Buf[2 * _MAX_INT_DIG];
	_CSTD _TOSTRING(_Buf, "%x", _Val);
	return (std::string(_Buf));
}

#if (DbgSession)
void PrintDbg(std::string sText, std::string sTitle)
{
	MessageBox(0, sText.c_str(), sTitle.c_str(), MB_ICONASTERISK);
	return;
}
#endif

#if !defined(InviDropper)
std::string GetEditText(HWND hControl)
{
	char tValue[2048];
	GetWindowText(hControl, tValue, 2048);
	return (std::string)tValue;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam)
{
	char *toIgnore[] = {"", "DIEmWin"};
	char buffer[256];
	DWORD id = 0;
	GetWindowThreadProcessId(hwnd, &id);
	if (ProcessID == id)
	{
		GetWindowText(hwnd, buffer, 255);
		for (int i = 0; i < _countof(toIgnore);i++)
		{
			if (StrCmp(buffer, toIgnore[i]) == 0)
				return true;

		}
		GetWindowText(hwnd, ServerName, 2048);
		return false;
	}

	return true;
}

bool GetServerNameByModule()
{
								//forbidden
	const char *Replacements[] = {"metin2", "mt2", " ", ",", "64bit", "client", "starter", "vista", "win7", "win8", "-"};
	std::regex e = (std::regex)"^\\S{3,}mt\\d?$";
	//bool bReplaced = false;
	std::string PName, tPName;
	std::smatch m;

	GetModuleFileName(0, ServerName, 2048);
	PathStripPath(ServerName);
	PathRemoveExtension(ServerName);

	PName = ServerName;
	sprintf_s(TBD, "M-%s", PName.c_str());
	tPName = PName;
	std::transform(tPName.begin(), tPName.end(), tPName.begin(), tolower);
	if (std::regex_search(PName, m, e))
	{
		sprintf_s(ServerName, 2048, "%s\0", PName.c_str());
		sprintf_s(TBD, "#M-%s", PName.c_str());
		return true;
	}
	if (tPName.find(Replacements[0]) == std::string::npos && tPName.find(Replacements[1]) == std::string::npos)
	{
		for (int i = 0;i < _countof(Replacements);i++)
		{
			if (tPName.length())
			{
				int Pos = tPName.find(Replacements[i]);
				if (Pos != std::string::npos)
				{
					if (i == _countof(Replacements) - 1 && Pos != PName.length() - 1)//last replacement and not last pos
						break;
					PName.erase(Pos, strlen(Replacements[i]));
					tPName = PName;
					std::transform(tPName.begin(), tPName.end(), tPName.begin(), tolower);
					//bReplaced = true;
					i--;
				}
			}
			else
				return false;
		}
		PName[0] = toupper(PName[0]);
		sprintf_s(ServerName, 2048, "%s\0", PName.c_str());

		sprintf_s(TBD, "#M-%s", PName.c_str());
		return true;
	}
	return false;
}

bool GetServerNameByWindow()
{
	const char *Replacements[] = {"metin2", "client", "starter", "pvp", "fun", ",", ":", ".", "!"};
	const char *e[4] = {"\\d{2,}", "\\s\\S{1}\\s", "\\s", "\\S{2,}\\-\\S{3,}"};
	std::smatch m;
	//bool bReplaced = false;
	std::string PName, tPName;
	sprintf_s(ServerName, "");
	while (StrCmp(ServerName, "") == 0)
	{
		EnumDesktopWindows(0, &EnumWindowsProc, 0);
		Sleep(1000);
	}

	sprintf_s(TBD, "W-%s", PName.c_str());
	PName = ServerName;
	tPName = PName;
	std::transform(tPName.begin(), tPName.end(), tPName.begin(), tolower);
	if (tPName.find(Replacements[0]) == std::string::npos)
	{
		for (int i = 0;i < _countof(Replacements);i++)
		{
			if (tPName.length())
			{
				int Pos = tPName.find(Replacements[i]);
				if (Pos != std::string::npos)
				{
					PName.erase(Pos, Pos + strlen(Replacements[i]));
					tPName = PName;
					std::transform(tPName.begin(), tPName.end(), tPName.begin(), tolower);
					//bReplaced = true;
				}
			}
			else
				return false;
		}

		if (std::regex_search(PName, m, (std::regex)e[3]))
			PName = m[0];
		PName[0] = toupper(PName[0]);
		sprintf_s(ServerName, 2048, "%s\0", PName.c_str());

		sprintf_s(TBD, "#W-%s", PName.c_str());
		return true;
	}
	return false;
}

bool GetServerName()
{
	if (GetServerNameByModule())
		return true;
	else if (GetServerNameByWindow())
		return true;

	return false;
}
#endif

DWORD GetModuleSize()
{
	DWORD ModuleSize;

	DWORD Base = (DWORD)hPInstance;
	DWORD PEOffset = *(DWORD*)(Base + 0x3C);
	
	MODULEINFO module_info;
	memset(&module_info, 0, sizeof(module_info));
	if (GetModuleInformation(GetCurrentProcess(), hPInstance, &module_info, sizeof(module_info)))
		ModuleSize = module_info.SizeOfImage;
	else
		ModuleSize = *(DWORD*)(Base + PEOffset + 0x1C) + Base;

	return ModuleSize - 0x1000;
}

__forceinline bool DataCompare(const unsigned char* address, const unsigned char* signature, const char* mask)
{
	while (*mask)
	{
		if (*reinterpret_cast<const unsigned int*>(mask) == 'xxxx')
		{
			if (*reinterpret_cast<const unsigned int*>(address) != *reinterpret_cast<const unsigned int*>(signature))
				return false;

			address += 4;
			signature += 4;
			mask += 4;
			continue;
		}
		else if (*reinterpret_cast<const unsigned short*>(mask) == 'xx')
		{
			if (*reinterpret_cast<const unsigned short*>(address) != *reinterpret_cast<const unsigned short*>(signature))
				return false;

			address += 2;
			signature += 2;
			mask += 2;
			continue;		
		}
		else if(*mask == 'x' && *address != *signature)
		{
			return false;
		}

		++address;
		++signature;
		++mask;
	}

	return *mask == 0;
}

DWORD FindPatternInternal(const unsigned char* address, size_t size, const unsigned char* signature, const char* mask, unsigned short ignore)
{
	WORD Ign = 0;
	for(size_t i = 0; i < size; i++)
	{
		if(DataCompare(address + i, signature, mask))
		{
			if (Ign < ignore)
				Ign++;
			else
				return (DWORD)address + i;
		}
	}
	return 0;
}

DWORD FindPattern(const unsigned char* address, size_t size, const unsigned char* signature, const char* mask, unsigned short ignore)
{
	size_t mask_length = strlen(mask);
	return FindPatternInternal(address, size - mask_length, signature, mask, ignore);
}

DWORD RelativeToAbsolute (DWORD Offset)
{
	return *(DWORD*)(Offset) + Offset + 0x4;
}

#if !defined(InviDropper)
BOOL CheckIni(BOOL Loading)
{
	BOOL FileSelected;
	CreateDirectory(IniPath, 0);

	OPENFILENAME ofn = {0};
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = 0;
	ofn.lpstrFilter = "Einstellungen(*.ini)\0*.ini\0";
	ofn.nMaxFile = 2048;
	ofn.lpstrFile = IniFullPath;
	ofn.lpstrTitle = (Loading) ? "Konfigurationsdatei laden..." : "Konfigurationsdatei speichern";
	ofn.Flags = (Loading) ? OFN_DONTADDTORECENT + OFN_FILEMUSTEXIST + OFN_NONETWORKBUTTON : OFN_DONTADDTORECENT + OFN_NONETWORKBUTTON;
	ofn.lpstrDefExt = sExt;
	FileSelected = (Loading) ? GetOpenFileName(&ofn) : GetSaveFileName(&ofn);
	if (!FileSelected)
		PathRemoveExtension(IniFullPath);
	else
		CloseHandle(CreateFile(IniFullPath, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0));

#if (DbgSession)
		DbgOutput = "File selected:" + std::to_string(FileSelected) + " (" + (std::string)IniFullPath + ")";
		MessageBox(0, DbgOutput.c_str(), sDbgOutput, MB_ICONASTERISK);
#endif

	SetCurrentDirectory(WorkingDir);
	return FileSelected;
#if (DbgSession)
	DbgOutput = "No ini found in default dir  (" + (std::string)IniPath + ")";
	MessageBox(0, DbgOutput.c_str(), sDbgOutput, MB_ICONASTERISK);
#endif
	return 0;
}

bool ValidateIni()
{
	if (PathFindExtension(IniFullPath) != sExt)
	{
		if (!CheckIni(FALSE))
			return false;
	}
	return true;
}

bool ForceValidation(bool bAsk)
{
	if (!bAsk && (PathFindExtension(IniFullPath) != sExt))
	{
		std::string sPathEx;
		sPathEx = (std::string)IniFullPath + (std::string)sExt;
		if (PathFileExists(sPathEx.c_str()))
		{
			PathAddExtension(IniFullPath, sExt);
#if (DbgSession)
			DbgOutput = "ForceValidation returns true!";
			MessageBox(0, DbgOutput.c_str(), sDbgOutput, MB_ICONASTERISK);
#endif
			return true;
		}
	}
#if (DbgSession)
	PrintDbg("ForceValidation returns false!", DbgOutput);
#endif
	return false;
}

void GetIniFullPath()
{
	hProcess = GetCurrentProcess();
	ProcessID = GetCurrentProcessId();
	GetModuleFileName((HINSTANCE)&__ImageBase, IniPath, 2048);
	PathRemoveFileSpec(IniPath);
	PathAppend(IniPath, sSettings);
	if (GetServerName())
		PathCombine(IniFullPath, IniPath, ServerName);
	else
		PathCombine(IniFullPath, IniPath, "Servername\0");

#if (DbgSession)
	MessageBox(0, IniFullPath, "", 0);
#endif
}

void CleanupOldSettings()
{
	bool IsOldIncompatibleIni, IsOldCompatibleIni, IsCompatibleIni;
	std::string OldIncompatibleIni, OldCompatibleDir, OldCompatibleIni, CompatibleDir, CompatibleIni;

	if (GetCurrentDirectory(2048, WorkingDir))//check for error while getting workingdir
	{
		PathCombine(IniFullPath, WorkingDir, "Ultimate-Tool.ini");
		// Case 1
		if (PathFileExists(IniFullPath))
		{
			OldIncompatibleIni = IniFullPath;
			IsOldIncompatibleIni = true;
		}
		// Case 2
		PathCombine(IniPath, WorkingDir, "Ultimate-Tool");
		PathCombine(IniFullPath, WorkingDir, "Ultimate-Tool\\Settings.ini");
		if (PathFileExists(IniFullPath))
		{
			OldCompatibleDir = IniPath;
			OldCompatibleIni = IniFullPath;
			IsOldCompatibleIni = true;
		}
		//Case 3
		PathCombine(IniPath, WorkingDir, "Tools by Unpublished");
		PathCombine(IniFullPath, WorkingDir, "Tools by Unpublished\\Settings.ini");
		if (PathFileExists(IniFullPath))
		{
			CompatibleDir = IniPath;
			CompatibleIni = IniFullPath;
			IsCompatibleIni = true;
		}
		GetIniFullPath();
	}
	else
	{
		MessageBox(0, sErrorGettingWorkingDir, sError, MB_ICONERROR);
	}
	if (IsOldIncompatibleIni)
	{
		if (MessageBox(0, "Es wurde eine alte inkompatible Konfigurationsdatei gefunden (Ultimate-Tool.ini).\n\nSoll diese nun gelöscht werden (empfohlen)?", sConfigFile, MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DeleteFile(OldIncompatibleIni.c_str());
		}
	}
	if (IsOldCompatibleIni && !IsCompatibleIni)
	{
		SetNewIniLocation(&CompatibleIni[0]);
	}
	else if (IsOldCompatibleIni && IsCompatibleIni)
	{
		DeleteFile(OldCompatibleIni.c_str());
		RemoveDirectory(OldCompatibleDir.c_str());
	}
	if (IsCompatibleIni && PathFileExists(IniFullPath))
	{
		int Antwort = MessageBox(0, "Es wurde eine alte Konfigurationsdatei gefunden (Tools by Unpublished\\Settings.ini).\n\nJa um diese zu löschen.\n\nNein um die aktuelle Konfigurations zu ersetzen.\n\nAbbrechen um die Entscheidung zu überspringen.", sConfigFile, MB_YESNOCANCEL | MB_ICONQUESTION);
		if (Antwort == IDYES)
		{
			DeleteFile(CompatibleIni.c_str());
			RemoveDirectory(CompatibleDir.c_str());
		}
		else if (Antwort == IDNO)
		{
			MoveFileEx(CompatibleDir.c_str(), IniFullPath, MOVEFILE_WRITE_THROUGH + MOVEFILE_REPLACE_EXISTING);
		}
	}
	else if (IsCompatibleIni && PathFindExtension(IniFullPath) == sExt)
	{
		MoveFileEx(CompatibleIni.c_str(), IniFullPath, MOVEFILE_WRITE_THROUGH + MOVEFILE_REPLACE_EXISTING);
		RemoveDirectory(CompatibleDir.c_str());
	}
	else if (IsCompatibleIni)
	{
		SetNewIniLocation(&CompatibleIni[0]);
	}
	if (PathFileExists((CompatibleDir + "vote.mix").c_str()))
		iClientMod = 1;
}

void SetNewIniLocation(char OldLocation[2048])
{
	MessageBox(0, "Es wurde eine veraltete Konfigurationsdatei gefunden.\r\n\r\nIm nächsten Schritt kann ein neuer Speicherort festgelegt werden.", sConfigFile, 0);
	if (CheckIni(FALSE))
	{
		MoveFileEx(OldLocation, IniFullPath, MOVEFILE_WRITE_THROUGH + MOVEFILE_REPLACE_EXISTING);
		PathRemoveFileSpec(OldLocation);
		RemoveDirectory(OldLocation);
	}
}
#endif

void InitComponents()
{
#if !defined(InviDropper)
	CleanupOldSettings();
#endif
	int i = 2000;
	for (int j = 0; j < _countof(IDC_BUTTON); j++)
	{
		IDC_BUTTON[j] = i;
		i++;
	}
#if !defined(InviDropper)
#if defined(TAB)
	for (int j = 0;j < _countof(IDC_TAB);j++)
	{
		IDC_TAB[j] = i;
		i++;
	}
#endif
#if defined(LABEL)
	for (int j = 0; j < _countof(IDC_STATIC); j++)
	{
		IDC_STATIC[j] = i;
		i++;
	}
#endif
#if defined(COMBO)
	for (int j = 0;j < _countof(IDC_COMBO);j++)
	{
		IDC_COMBO[j] = i;
		i++;
	}
#endif
#if defined(EDIT)
	for (int j = 0; j < _countof(IDC_EDIT); j++)
	{
		IDC_EDIT[j] = i;
		i++;
	}
#endif
#endif
	i = 0;
	MainWindow();
}
