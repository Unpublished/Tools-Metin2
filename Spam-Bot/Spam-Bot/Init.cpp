#include "..\..\Classes\Init Class.h"

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);

	DWORD SizeOfCode = GetModuleSize();

	switch (GetSearchPattern())
	{
		case 1:// Hamachi
			{
				BYTE P_SendChat[] = {0x8B, 0x55, 0xFC, 0x8B, 0x45, 0xF8, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E};
				char M_SendChat[] = "xxxxxxxx---xxxx---xx---xx";
				DWORD B_SendChat = FindPattern(StartBase, SizeOfCode, P_SendChat, M_SendChat, 5);
				NetPointer = *(DWORD*)(B_SendChat + 8);
				SendChatCall = RelativeToAbsolute(B_SendChat + 15);
			break;
		}
		default:
			{

				BYTE P_SlotAndItemIndexOffset[] = {0x8B, 0x44, 0x24, 0x04, 0x83, 0xF8, 0x00, 0x72, 0x05, 0x33, 0xC0, 0xC2, 0x04, 0x00, 0x6B, 0xC0, 0x00, 0x8D, 0x00, 0x08};
				char M_SlotAndItemIndexOffset[] = "xxxxxx-xxxxxxxxx-x-x";
				DWORD B_SlotAndItemIndexOffset = FindPattern(StartBase, SizeOfCode, P_SlotAndItemIndexOffset, M_SlotAndItemIndexOffset, 0);
				SlotOffset = *(BYTE*)(B_SlotAndItemIndexOffset + 16);

#if (DbgSession)
				DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
				MessageBox(0, "SlotOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

				BYTE P_SendChat[] = {0x8B, 0x54, 0x24, 0x04, 0x8B, 0x44, 0x24, 0x08, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E};
				char M_SendChat[] = "xxxxxxxxxx---xxxx---xx---xx";
				DWORD B_SendChat = FindPattern(StartBase, SizeOfCode, P_SendChat, M_SendChat, 5);
				if (SlotOffset == 0x2E)
					B_SendChat = FindPattern(StartBase, SizeOfCode, P_SendChat, M_SendChat, 7);

				NetPointer = *(DWORD*)(B_SendChat + 10);
				SendChatCall = RelativeToAbsolute(B_SendChat + 17);
			break;
		}
	}
#if (DbgSession)
	DbgOutput = "NetPointer: " + to_hexstring(NetPointer) + win_endl
		"SendChatCall: " + to_hexstring(SendChatCall);
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