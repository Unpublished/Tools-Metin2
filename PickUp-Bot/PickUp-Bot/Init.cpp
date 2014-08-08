#include "..\..\Classes\Init Class.h"

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);
	DWORD PEOffset = *(DWORD*)(Base + 0x3C);
	DWORD SizeOfCode = *(DWORD*)(Base + PEOffset + 0x1C) + Base;

	switch (GetSearchPattern())
	{
		case 1:// Hamachi
		{
			BYTE P_PickCloseItem [] = { 0xCC, 0xCC, 0xCC, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00 };
			char M_PickCloseItem [] = "xxxxx---xx----x---x";
			DWORD B_PickCloseItem = FindPattern(StartBase, SizeOfCode, P_PickCloseItem, M_PickCloseItem, 11);
			PlayerPointer = *(DWORD*) (B_PickCloseItem + 5);
			PickCloseItemCall = RelativeToAbsolute(B_PickCloseItem + 10);

#if (DbgSession)
			DbgOutput = "Debug - Zeile ", std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer & PickCloseItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_InstantPickUp [] = { 0x8B, 0x4D, 0x08, 0x05, 0xF4, 0x01, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0x00, 0x8D, 0x45, 0xFC };
			char M_InstantPickUp [] = "xxxxxxxxx---xxxx";
			DWORD B_InstantPickUp = FindPattern(StartBase, SizeOfCode, P_InstantPickUp, M_InstantPickUp, 0);
			InstantPickUpAddie = B_InstantPickUp + 3;
			break;
		}
		default:
		{
			BYTE P_PickCloseItem [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0xFF, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x51, 0x8B, 0x4C, 0x24, 0x00, 0x8D, 0x04, 0x24, 0x50 };
			char M_PickCloseItem [] = "xx---xx---xx----xxxx-xxxx";
			DWORD B_PickCloseItem = FindPattern(StartBase, SizeOfCode, P_PickCloseItem, M_PickCloseItem, 1);
			PlayerPointer = *(DWORD*) (B_PickCloseItem + 2);
			PickCloseItemCall = RelativeToAbsolute(B_PickCloseItem + 7);

			if (PickCloseItemCall < 0x44DB00)//43A840 (XtremeMt2) # 0x44DA40 PlayWorld3
			{
				DWORD B_PickCloseItem = FindPattern(StartBase, SizeOfCode, P_PickCloseItem, M_PickCloseItem, 2);
				PlayerPointer = *(DWORD*) (B_PickCloseItem + 2);
				PickCloseItemCall = RelativeToAbsolute(B_PickCloseItem + 7);
			}

#if (DbgSession)
			DbgOutput = "Debug - Zeile ", std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer & PickCloseItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			switch (PickCloseItemCall)
			{
				case 0x465490://if XtremeMt2
				{
					switch (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]))//if Instant-PickUp is deactivated
					{
						case BST_UNCHECKED:
						{
							if (PathFindExtension(IniFullPath) == sExt && PathFileExists(IniFullPath))
							{
								WritePrivateProfileString(PickUp_Bot, "Instant-PickUp", "1", IniFullPath);//automatically activate
								CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Load, 0, 0, 0);
								break;
							}
						}
					}
					EnableWindow(PickUpBotButton[0], false);
					break;
				}
				default:
				{
					BYTE P_InstantPickUp[] = {0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x05, 0xF4, 0x01, 0x00, 0x00, 0x00, 0x8B, 0x00, 0x24, 0x10, 0xA3, 0x00, 0x00, 0x00, 0x00};
					char M_InstantPickUp[] = "xx---xxxxxx-x-xxx---x";
					DWORD B_InstantPickUp = FindPattern(StartBase, SizeOfCode, P_InstantPickUp, M_InstantPickUp, 0);
					InstantPickUpAddie = B_InstantPickUp + 6;
					break;
				}
			}
			break;
		}
	}
	DWORD Buffer = 0;
	ReadProcessMemory(hProcess, (void*)(InstantPickUpAddie), &InstantPickUpInitialBytes, sizeof(InstantPickUpInitialBytes), &Buffer);
	Buffer = 0;
#if (DbgSession)
	DbgOutput = "Debug - Zeile ", std::to_string(__LINE__);
	MessageBox(0, "InstantPickUpAddie gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
	DbgOutput = "PlayerPointer: " + to_hexstring(PlayerPointer) + win_endl
		"PickCloseItemCall: " + to_hexstring(PickCloseItemCall) + win_endl
		"InstantPickUpAddie: " + to_hexstring(InstantPickUpAddie);
	MessageBox(0, DbgOutput.c_str(), sDbgOutput, MB_ICONASTERISK);
#endif
	ExitThread(0);
}

BOOL WINAPI DllMain (HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)InitComponents, 0, 0, 0);
			break;

		case DLL_PROCESS_DETACH:
			break;
 
		case DLL_THREAD_ATTACH:
			break;
 
		case DLL_THREAD_DETACH:
			break;
	}
	return true;
}