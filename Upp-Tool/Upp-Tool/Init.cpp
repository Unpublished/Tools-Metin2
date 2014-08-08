#include "..\..\Classes\Init Class.h"

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);
	DWORD PEOffset = *(DWORD*)(Base + 0x3C);
	DWORD SizeOfCode = *(DWORD*)(Base + PEOffset + 0x1C) + Base;
	
	switch (GetSearchPattern())
	{
		case 1:
		{
			BYTE P_PlayerPointer[] = {0x85, 0xC9, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x95, 0xC2, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xE5};
			char M_PlayerPointer[] = "xxxx---xxxxxx----x---xxx";
			DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 2);
			PlayerPointer = *(DWORD*)(B_PlayerPointer + 4);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendRefine [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E };
			char M_SendRefine [] = "xx---xxxx---xx---xx";
			DWORD B_SendRefine = FindPattern(StartBase, SizeOfCode, P_SendRefine, M_SendRefine, (SlotOffset == 0x2E) ? 25 : 23);
			NetPointer = *(DWORD*) (B_SendRefine + 2);
			SendRefineCall = RelativeToAbsolute(B_SendRefine + 9);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendRefineCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendItemUseToItem[] = {0x8B, 0x45, 0xF8, 0x8B, 0x4D, 0xF4, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00};
			char M_SendItemUseToItem[] = "xxxxxxxxxx---xx---xx---x";
			DWORD B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItem, M_SendItemUseToItem, 0);
			SendItemUseToItemCall = RelativeToAbsolute(B_SendItemUseToItem + 15);
			break;
		}
		default:
		{
			BYTE P_PlayerPointer[] = {0x8B, 0x4C, 0x24, 0x0C, 0x8D, 0x54, 0x24, 0x08, 0x52, 0x8B, 0x54, 0x24, 0x14, 0x8D, 0x44, 0x24, 0x0B, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xBF, 0x44, 0x24, 0x08, 0x0F, 0xB6, 0x4C, 0x24, 0x07};
			char M_PlayerPointer[] = "xxxxxxxxxxxxxxxxxxxxx---xxx----xxxxxxxxxx";
			DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 0);
			PlayerPointer = *(DWORD*)(B_PlayerPointer + 21);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SlotAndItemIndexOffset[] = {0x8B, 0x44, 0x24, 0x04, 0x83, 0xF8, 0x00, 0x72, 0x05, 0x33, 0xC0, 0xC2, 0x04, 0x00, 0x6B, 0xC0, 0x00, 0x8D, 0x00, 0x08};
			char M_SlotAndItemIndexOffset[] = "xxxxxx-xxxxxxxxx-x-x";
			DWORD B_SlotAndItemIndexOffset = FindPattern(StartBase, SizeOfCode, P_SlotAndItemIndexOffset, M_SlotAndItemIndexOffset, 0);
			SlotOffset = *(BYTE*)(B_SlotAndItemIndexOffset + 16);
			ItemIndexOffset = *(BYTE*)(B_SlotAndItemIndexOffset + 20);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "SlotOffset & ItemIndexOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendRefine [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00 };
			char M_SendRefine [] = "xx---xxxx---x";
			DWORD B_SendRefine = FindPattern(StartBase, SizeOfCode, P_SendRefine, M_SendRefine, 26);
			if (SlotOffset == 0x2E)
				B_SendRefine = FindPattern(StartBase, SizeOfCode, P_SendRefine, M_SendRefine, 29);

			NetPointer = *(DWORD*) (B_SendRefine + 2);
			SendRefineCall = RelativeToAbsolute(B_SendRefine + 9);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendRefineCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif
			DWORD B_SendItemUseToItem;
			if (iClientMod)
			{
				//LongDong2 modification
				BYTE P_SendItemUseToItemLD2[] = {0x8B, 0x4C, 0xE4, 0x0C, 0x8B, 0x44, 0xE4, 0x08, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E};
				char M_SendItemUseToItemLD2[] = "xxxxxxxxxxxx---xx---xx---xx";
				B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItemLD2, M_SendItemUseToItemLD2, 0);
			}
			else
			{
				BYTE P_SendItemUseToItem[] = {0x8B, 0x44, 0x24, 0x08, 0x8B, 0x4C, 0x24, 0x0C, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E};
				char M_SendItemUseToItem[] = "xxxxxxxxxxxx---xx---xx---xx";
				B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItem, M_SendItemUseToItem, 0);
			}
			SendItemUseToItemCall = RelativeToAbsolute(B_SendItemUseToItem + 17);
			break;
		}
	}
#if (DbgSession)
	DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
	MessageBox(0, "SendItemUseToItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
	DbgOutput = "PlayerPointer: " + to_hexstring(PlayerPointer) + win_endl
		"SlotOffset: " + to_hexstring(SlotOffset) + win_endl
		"ItemIndexOffset: " + to_hexstring(ItemIndexOffset) + win_endl
		"NetPointer: " + to_hexstring(NetPointer) + win_endl
		"SendRefineCall: " + to_hexstring(SendRefineCall) + win_endl
		"SendItemUseToItemCall: " + to_hexstring(SendItemUseToItemCall);
	MessageBox(0, DbgOutput.c_str(), sDbgOutput, MB_ICONASTERISK);
	DbgOutput._Tidy();
#endif
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Load, 0, 0, 0);
	ExitThread(0);
}

BOOL WINAPI DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
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