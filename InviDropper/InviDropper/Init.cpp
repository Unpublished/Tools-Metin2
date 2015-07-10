#include "..\..\Classes\Init Class.h"

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);

	DWORD SizeOfCode = GetModuleSize();

	switch (GetSearchPattern())
	{
		case 1: //Hamachi
			{
				BYTE P_PickCloseItem [] = { 0xCC, 0xCC, 0xCC, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00 };
				char M_PickCloseItem [] = "xxxxx---xx----x---x";
				DWORD B_PickCloseItem = FindPattern(StartBase, SizeOfCode, P_PickCloseItem, M_PickCloseItem, 11);
				PlayerPointer = *(DWORD*)(B_PickCloseItem + 5);

#if (DbgSession)
				DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
				MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

				BYTE P_SendDropItem [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x6A, 0x00, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00 };
				char M_SendDropItem [] = "xx---xxxxxx---xx---x";
				DWORD B_SendDropItem = FindPattern(StartBase, SizeOfCode, P_SendDropItem, M_SendDropItem, 0);
				NetPointer = *(DWORD*)(B_SendDropItem + 2);
				SendDropItemCall = RelativeToAbsolute(B_SendDropItem + 11);
				break;
		}
		default:
		{
			BYTE P_PickCloseItem [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0xFF, 0xE9, 0x00, 0x00, 0x00, 0x00, 0x51, 0x8B, 0x4C, 0x24, 0x00, 0x8D, 0x04, 0x24, 0x50 };
			char M_PickCloseItem [] = "xx---xx---xx----xxxx-xxxx";
			DWORD B_PickCloseItem = FindPattern(StartBase, SizeOfCode, P_PickCloseItem, M_PickCloseItem, 2);
			PlayerPointer = *(DWORD*)(B_PickCloseItem + 2);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SlotAndItemIndexOffset [] = { 0x8B, 0x44, 0x24, 0x04, 0x83, 0xF8, 0x00, 0x72, 0x05, 0x33, 0xC0, 0xC2, 0x04, 0x00, 0x6B, 0xC0, 0x00, 0x8D, 0x00, 0x08 };
			char M_SlotAndItemIndexOffset [] = "xxxxxx-xxxxxxxxx-x-x";
			DWORD B_SlotAndItemIndexOffset = FindPattern(StartBase, SizeOfCode, P_SlotAndItemIndexOffset, M_SlotAndItemIndexOffset, 0);
			SlotOffset = *(BYTE*)(B_SlotAndItemIndexOffset + 16);
			ItemIndexOffset = *(BYTE*)(B_SlotAndItemIndexOffset + 20);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "SlotOffset & ItemIndexOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendDropItem [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x6A, 0x00, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00 };
			char M_SendDropItem [] = "xx---xxxxxx---xx---x";
			DWORD B_SendDropItem = FindPattern(StartBase, SizeOfCode, P_SendDropItem, M_SendDropItem, 0);
			NetPointer = *(DWORD*)(B_SendDropItem + 2);
			SendDropItemCall = RelativeToAbsolute(B_SendDropItem + 11);
			break;
		}
	}
#if (DbgSession)
	DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
	MessageBox(0, "NetPointer & SendDropItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
	DbgOutput = "PlayerPointer: " + to_hexstring(PlayerPointer) + win_endl
		"SlotOffset: " + to_hexstring(SlotOffset) + win_endl
		"ItemIndexOffset: " + to_hexstring(ItemIndexOffset) + win_endl
		"NetPointer: " + to_hexstring(NetPointer) + win_endl
		"SendDropItemCall: " + to_hexstring(SendDropItemCall);
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
	}
	return true;
}
