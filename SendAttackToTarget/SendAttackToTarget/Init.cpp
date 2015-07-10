#include "..\..\Classes\Init Class.h"

HANDLE hSearchPatternThread;

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);

	DWORD SizeOfCode = GetModuleSize();

	DWORD dwSeachPattern;
	GetExitCodeThread(hSearchPatternThread, &dwSeachPattern);
	CloseHandle(hSearchPatternThread);

	//TargetVIDOffset (0)F24C(Metin2 DE), 0x4148 (Cyperia/Metin2 DE Binary 2013/14?), 0x41AC/0x454C (PServer 2013)/Metin2 DE Binary (2013/12?), 0x3E10 (Other)
	switch (dwSeachPattern)
	{
		case 1:// Hamachi
		{
			BYTE P_PlayerPointer [] = { 0x85, 0xC9, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x95, 0xC2, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xE5 };
			char M_PlayerPointer [] = "xxxx---xxxxxx----x---xxx";
			DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 2);
			PlayerPointer = *(DWORD*) (B_PlayerPointer + 4);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendAttack [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x57, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xCE, 0xE8, 0x00, 0x00, 0x00, 0x00 };
			char M_SendAttack [] = "xx---xxxx----xxx---x";
			DWORD B_SendAttack = FindPattern(StartBase, SizeOfCode, P_SendAttack, M_SendAttack, 0);
			NetPointer = *(DWORD*) (B_SendAttack + 2);
			SendAttackCall = RelativeToAbsolute(B_SendAttack + 9);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendAttackCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			TargetVIDOffset = 0x3E10;
			break;
		}

		default:// Metin2 PServer 2010 - 2013
		{
			BYTE P_PlayerPointer [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x84, 0xC0, 0x74, 0x00, 0x32, 0xC0 };
			char M_PlayerPointer [] = "xx---xx---xxxx-xx";
			DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 0);
			PlayerPointer = *(DWORD*) (B_PlayerPointer + 2);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendAttack [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x53, 0x50, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xCE, 0xE8, 0x00, 0x00, 0x00, 0x00 };
			char M_SendAttack [] = "xx---xxxx----xxx---x";
			DWORD B_SendAttack = FindPattern(StartBase, SizeOfCode, P_SendAttack, M_SendAttack, 0);
			NetPointer = *(DWORD*) (B_SendAttack + 2);
			SendAttackCall = RelativeToAbsolute(B_SendAttack + 9);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendAttackCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_TargetVIDOffset [] = { 0x8B, 0x44, 0x24, 0x00, 0x89, 0x81, 0x00, 0x00, 0x00, 0x00, 0xC2, 0x04 };
			char M_TargetVIDOffset [] = "xxx-xx----xx";
			for (int i = 3; i < 5; i++)
			{
				DWORD B_TargetVIDOffset = FindPattern(StartBase, SizeOfCode, P_TargetVIDOffset, M_TargetVIDOffset, i);
				TargetVIDOffset = (*(BYTE*)(B_TargetVIDOffset + 6)) | (*(BYTE*)(B_TargetVIDOffset + 7) << 8) | (0x00 << 16) | (0x00 << 24);
				if (TargetVIDOffset == 0x41AC) break;
			}

			if (TargetVIDOffset != 0x41AC)
			{
				BYTE P_TargetVIDOffset[] = { 0x8B, 0x81, 0x00, 0x00, 0x00, 0x00, 0xC3 };
				char M_TargetVIDOffset[] = "xx----x";
				DWORD B_TargetVIDOffset = FindPattern(StartBase, SizeOfCode, P_TargetVIDOffset, M_TargetVIDOffset, 11);
				TargetVIDOffset = (*(BYTE*)(B_TargetVIDOffset + 2)) | (*(BYTE*)(B_TargetVIDOffset + 3) << 8) | (0x00 << 16) | (0x00 << 24);
				//B_TargetVIDOffset = FindPattern(StartBase, SizeOfCode, P_TargetVIDOffset, M_TargetVIDOffset, 11);
				//TargetVIDOffset = (*(BYTE*) (B_TargetVIDOffset + 6)) | (*(BYTE*) (B_TargetVIDOffset + 7) << 8) | (0x00 << 16) | (0x00 << 24);
				//if (TargetVIDOffset != 0x3E10)
				//{
				//	
				//	BYTE P_TargetVIDOffsetXtreme [] = { 0x8B, 0x81, 0x00, 0x00, 0x00, 0x00, 0xC3};
				//	char M_TargetVIDOffsetXtreme [] = "xx----x";
				//	B_TargetVIDOffset = FindPattern(StartBase, SizeOfCode, P_TargetVIDOffsetXtreme, M_TargetVIDOffsetXtreme, 12);
				//	TargetVIDOffset = (*(BYTE*) (B_TargetVIDOffset + 2)) | (*(BYTE*) (B_TargetVIDOffset + 3) << 8) | (0x00 << 16) | (0x00 << 24);
				//}
				if ((*(BYTE*)(B_TargetVIDOffset + 3)) < 0x40 || (*(BYTE*)(B_TargetVIDOffset + 3)) > 0x50)//i = 11
					TargetVIDOffset = 0x3E10;
#if (DbgSession)
				else
				{
					DbgOutput = to_hexstring((*(BYTE*)(B_TargetVIDOffset + 3)));
					MessageBox(0, DbgOutput.c_str(), "Erster gefundener Byte (TargetVIDOffset)", 0);
				}
#endif
			}
#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "TargetVIDOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif
			break;
		}
	}
#if (DbgSession)
	DbgOutput = "PlayerPointer: " + to_hexstring(PlayerPointer) + win_endl
		"NetPointer: " + to_hexstring(NetPointer) + win_endl
		"SendAttackCall: " + to_hexstring(SendAttackCall) + win_endl
		"TargetVIDOffset: " + to_hexstring(TargetVIDOffset);
	MessageBox(0, DbgOutput.c_str(), "DbgOutput", MB_ICONASTERISK);
#endif
	ExitThread(0);
}

BOOL WINAPI DllMain(HANDLE hDll, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		hSearchPatternThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GetSearchPattern, 0, 0, 0);
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