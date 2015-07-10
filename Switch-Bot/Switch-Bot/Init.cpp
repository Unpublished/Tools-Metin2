#include "..\..\Classes\Init Class.h"

void SetAddies()
{
	DWORD Base = (DWORD)hPInstance;
	const unsigned char* StartBase = reinterpret_cast<const unsigned char*>(Base + 0x1000);

	DWORD SizeOfCode = GetModuleSize();

	switch (GetSearchPattern())
	{
		case 1:
		{
			BYTE P_PlayerPointer [] = { 0x85, 0xC9, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x95, 0xC2, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xE5 };
			char M_PlayerPointer [] = "xxxx---xxxxxx----x---xxx";
			DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 2);
			PlayerPointer = *(DWORD*) (B_PlayerPointer + 4);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendItemUseToItem [] = { 0x8B, 0x45, 0xF8, 0x8B, 0x4D, 0xF4, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00 };
			char M_SendItemUseToItem [] = "xxxxxxxxxx---xx---xx---x";
			DWORD B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItem, M_SendItemUseToItem, 0);
			NetPointer = *(DWORD*) (B_SendItemUseToItem + 10);
			SendItemUseToItemCall = RelativeToAbsolute(B_SendItemUseToItem + 15);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendItemUseToItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SendShopBuy [] = { 0x8B, 0x55, 0xFC, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xE5 };
			char M_SendShopBuy [] = "xxxxx---xxx---xx---xxx";
			DWORD B_SendShopBuy = FindPattern(StartBase, SizeOfCode, P_SendShopBuy, M_SendShopBuy, 9);
			SendShopBuyCall = RelativeToAbsolute(B_SendShopBuy + 11);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, " SendShopBuyCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_ShopPointer[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x33, 0xC9, 0x89, 0x48, 0x04, 0x89, 0x48, 0x08, 0x89, 0x48, 0x0C, 0xE9, 0x00, 0x00, 0x00, 0x00 };
			char M_ShopPointer[] = "x---xxxxxxxxxxxxx---x";
			DWORD B_ShopPointer = FindPattern(StartBase, SizeOfCode, P_ShopPointer, M_ShopPointer, 0);
			ShopPointer = *(DWORD*) (B_ShopPointer + 1);
		}
		default:
		{
			break;
			BYTE P_EP[] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x33, 0xC4, 0x50 };
			char M_EP[] = { "x----xxx" };
			DWORD B_EP = FindPattern(StartBase, SizeOfCode, P_EP, M_EP, 0);
			DWORD EP = *(DWORD*)(B_EP + 1);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, ("EP: " + to_hexstring(EP)).c_str(), DbgOutput.c_str(), MB_ICONASTERISK);
#endif
			if (EP > 0x70A000)//Shiro2
			{
				BYTE P_PlayerPointer[] = { 0x55, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x5D, 0xC3 };
				char M_PlayerPointer[] = "xxxx---xxx";
				DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 3);
				PlayerPointer = *(DWORD*)(B_PlayerPointer + 4);
			}
			else
			{
				BYTE P_PlayerPointer [] = { 0x8B, 0x4C, 0x24, 0x0C, 0x8D, 0x54, 0x24, 0x08, 0x52, 0x8B, 0x54, 0x24, 0x14, 0x8D, 0x44, 0x24, 0x0B, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xBF, 0x44, 0x24, 0x08, 0x0F, 0xB6, 0x4C, 0x24, 0x07 };
				char M_PlayerPointer [] = "xxxxxxxxxxxxxxxxxxxxx---xxx----xxxxxxxxxx";
				DWORD B_PlayerPointer = FindPattern(StartBase, SizeOfCode, P_PlayerPointer, M_PlayerPointer, 0);
				PlayerPointer = *(DWORD*)(B_PlayerPointer + 21);
			}

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "PlayerPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			DWORD B_SendItemUseToItem;
			if (iClientMod)
			{
				//LongDong2 modification
				BYTE P_NetPointer[] = { 0x55, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x5D, 0xC3 };
				char M_NetPointer[] = "xxxx---x";
				DWORD B_NetPointer = FindPattern(StartBase, SizeOfCode, P_NetPointer, M_NetPointer, 17);
				NetPointer = *(DWORD*)(B_NetPointer + 4);

#if DbgSession
				//DbgOutput = "Debug - Zeile " + std::to_string(i);
				MessageBox(0, ("NetPointer: " + to_hexstring(NetPointer)).c_str(), DbgOutput.c_str(), MB_ICONASTERISK);
#endif
				BYTE P_SendItemUseToItemLD2[] = {0x8B, 0x4C, 0xE4, 0x0C, 0x8B, 0x44, 0xE4, 0x08, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E};
				char M_SendItemUseToItemLD2[] = "xxxxxxxxxxxx---xx---xx---xx";
				B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItemLD2, M_SendItemUseToItemLD2, 0);
			}
			else
			{
				if (EP > 0x70A000)//Shiro2
				{
					BYTE P_NetPointer[] = { 0x55, 0x8B, 0xEC, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x5D, 0xC3 };
					char M_NetPointer[] = "xxxx---xxx";
					DWORD B_NetPointer = FindPattern(StartBase, SizeOfCode, P_NetPointer, M_NetPointer, 18);
					NetPointer = *(DWORD*)(B_NetPointer + 4);
					BYTE P_SendItemUseToItem[] = { 0x51, 0x8B, 0xCC, 0x66, 0x8B, 0x55, 0xF4, 0x66, 0x89, 0x11, 0x8A, 0x45, 0xF6, 0x88, 0x41, 0x02, 0x8B, 0x4D, 0xFC, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x8B, 0xE5, 0x5D, 0xC3 };
					char M_SendItemUseToItem[] = "xxxxxxxxxxxxxxxxxxxx---xx---xxxxx";
					B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItem, M_SendItemUseToItem, 0);
					SendItemUseToItemCall = RelativeToAbsolute(B_SendItemUseToItem + 25);
				}
				else
				{
					BYTE P_SendItemUseToItem[] = { 0x8B, 0x44, 0x24, 0x08, 0x8B, 0x4C, 0x24, 0x0C, 0x50, 0x51, 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x5E };
					char M_SendItemUseToItem[] = "xxxxxxxxxxxx---xx---xx---xx";
					B_SendItemUseToItem = FindPattern(StartBase, SizeOfCode, P_SendItemUseToItem, M_SendItemUseToItem, 0);
					SendItemUseToItemCall = RelativeToAbsolute(B_SendItemUseToItem + 17);
					NetPointer = *(DWORD*)(B_SendItemUseToItem + 12);
				}
			}
			BYTE NetPointerBytes[3];
			NetPointerBytes[0] = *(BYTE*) (B_SendItemUseToItem + 12);
			NetPointerBytes[1] = *(BYTE*) (B_SendItemUseToItem + 13);
			NetPointerBytes[2] = *(BYTE*) (B_SendItemUseToItem + 14);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "NetPointer & SendItemUseToItemCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_SlotAndItemIndexOffset [] = { 0x8B, 0x44, 0x24, 0x04, 0x83, 0xF8, 0x00, 0x72, 0x05, 0x33, 0xC0, 0xC2, 0x04, 0x00, 0x6B, 0xC0, 0x00, 0x8D, 0x00, 0x08 };
			char M_SlotAndItemIndexOffset [] = "xxxxxx-xxxxxxxxx-x-x";
			//DWORD B_SlotAndItemIndexOffset = FindPattern(StartBase, SizeOfCode, P_SlotAndItemIndexOffset, M_SlotAndItemIndexOffset, 0);
			//SlotOffset = *(BYTE*) (B_SlotAndItemIndexOffset + 16);
			//ItemIndexOffset = *(BYTE*) (B_SlotAndItemIndexOffset + 20);

#if (DbgSession)
			DbgOutput = "Debug - Zeile  " + std::to_string(__LINE__);
			MessageBox(0, "SlotOffset & ItemIndexOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			//ItemIndexOffset = 0x78, SlotOffset = 0x2A;
			//ItemIndexOffset = 0x8C, SlotOffset = 0x2E;

			BYTE P_SendShopBuy [] = { 0x8B, 0x14, 0x24, 0x8B, 0x0D, 0x00, 0x00, 0x7D, 0x00, 0x52, 0xE8, 0x00, 0x00, 0x00, 0x00, 0xE8, 0x00, 0x00, 0x00, 0x00, 0x59 };
			/*P_SendShopBuy[5] = NetPointerBytes[0];
			P_SendShopBuy[6] = NetPointerBytes[1];
			P_SendShopBuy[7] = NetPointerBytes[2];
			char M_SendShopBuy [] = "xxxxxxxxxxx---xx---xx";
			DWORD B_SendShopBuy = FindPattern(StartBase, SizeOfCode, P_SendShopBuy, M_SendShopBuy, (SlotOffset == 0x2E) ? 9 : 8);
			SendShopBuyCall = RelativeToAbsolute(B_SendShopBuy + 11);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, " SendShopBuyCall gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			BYTE P_ItemAttributeOffset [] = { 0x88, 0x00, 0x00, 0x00, 0x00, 0x66, 0x8B, 0x94 };
			char M_ItemAttributeOffset [] = "x----xxx";
			DWORD B_ItemAttributeOffset = FindPattern(StartBase, SizeOfCode, P_ItemAttributeOffset, M_ItemAttributeOffset, 0);
			ItemAttributeValueOffset = *(BYTE*) (B_ItemAttributeOffset + 9);
			ItemAttributeTypeOffset = ItemAttributeValueOffset - 0x1;
			
			if (ItemAttributeValueOffset == 0xDD)
			{
				BYTE P_ItemAttributeOffsetNew[] = { 0x88, 0x0E, 0x66, 0x8B, 0x90 };
				char M_ItemAttributeOffsetNew[] = "xxxx";
				DWORD B_ItemAttributeOffsetNew = FindPattern(StartBase, SizeOfCode, P_ItemAttributeOffsetNew, M_ItemAttributeOffsetNew, 0);
				ItemAttributeValueOffset = *(BYTE*)(B_ItemAttributeOffsetNew + 5);
				ItemAttributeTypeOffset = ItemAttributeValueOffset - 0x1;

#if (DbgSession)
				DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
				MessageBox(0, "ItemAttributeValueOffset & ItemAttributeTypeOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif
				BYTE P_ShopItemCountOffset[] = { 0x0F, 0xB6, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0xFF };
				char M_ShopItemCountOffset[] = "xx---x---xx";
				DWORD B_ShopItemCountOffset = FindPattern(StartBase, SizeOfCode, P_ShopItemCountOffset, M_ShopItemCountOffset, 14);
				ShopItemCountOffset = *(BYTE*)(B_ShopItemCountOffset + 3);

#if (DbgSession)
				DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
				MessageBox(0, "ShopItemCountOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif
			}

			BYTE P_ShopSlotAndItemIDOffset [] = { 0x6B, 0xC0, 0x00, 0x8D, 0x44, 0x00, 0x00, 0x8B };
			char M_ShopSlotAndItemIDOffset [] = "xx-xx--x";
			DWORD B_ShopSlotAndItemIDOffset = FindPattern(StartBase, SizeOfCode, P_ShopSlotAndItemIDOffset, M_ShopSlotAndItemIDOffset, 0);
			ShopSlotOffset = *(BYTE*) (B_ShopSlotAndItemIDOffset + 2);
			ShopItemIDOffset = *(BYTE*)(B_ShopSlotAndItemIDOffset + 6);

#if (DbgSession)
			DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
			MessageBox(0, "ShopSlotOffset & ShopItemIDOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif

			if (!ShopItemCountOffset)
			{
				ShopItemCountOffset = 0x8;
				// Following not compatible with Karidarah2
				/*for (int i = 0; i < 20; i++)
				{
					BYTE P_ShopItemCountOffset[] = { 0x0F, 0xB6, 0x00, 0x00, 0x00, 0x68, 0x00, 0x00, 0x00, 0x00, 0xFF };
					char M_ShopItemCountOffset[] = "xx---x---xx";
					DWORD B_ShopItemCountOffset = FindPattern(StartBase, SizeOfCode, P_ShopItemCountOffset, M_ShopItemCountOffset, 12);
					ShopItemCountOffset = *(BYTE*)(B_ShopItemCountOffset + 3);
					//if (ShopItemCountOffset == 0x8)
					//{
						DbgOutput = "Debug - Zeile " + std::to_string(i);
						MessageBox(0, ("ShopItemCountOffset: " + to_hexstring(ShopItemCountOffset)).c_str(), DbgOutput.c_str(), MB_ICONASTERISK);
					//}

				}*/
				/*
#if (DbgSession)
				DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
				MessageBox(0, "ShopItemCountOffset gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
#endif
			}


			BYTE P_ShopPointer [] = { 0xA1, 0x00, 0x00, 0x00, 0x00, 0x8B, 0x4C, 0x24, 0x1C, 0x8B, 0x54, 0x24, 0x20 };
			char M_ShopPointer [] = "x---xxxxxxxxx";
			BYTE P_ShopPointerNew [] = { 0x8B, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x83, 0xC4, 0x18, 0x52, 0x50 };
			char M_ShopPointerNew [] = "xx---xxxxxx";
			switch (SlotOffset)
			{
			case 0x2E://8B 0D ?? ?? ?? 00 83 C4 18 52 50
				switch (*(BYTE*)(B_ItemAttributeOffset + 9))
				{
				case 0xDD:
					ShopPointer = *(DWORD*)((DWORD)FindPattern(StartBase, SizeOfCode, P_ShopPointer, M_ShopPointer, 0) + 1);
					break;
				default:
					ShopPointer = *(DWORD*)((DWORD)FindPattern(StartBase, SizeOfCode, P_ShopPointerNew, M_ShopPointerNew, 0) + 2);
					break;
				}

				break;

			default:
				ShopPointer = *(DWORD*)((DWORD)FindPattern(StartBase, SizeOfCode, P_ShopPointer, M_ShopPointer, 0) + 1);
				break;
			}*/
		}
	}
#if (DbgSession)
	DbgOutput = "Debug - Zeile " + std::to_string(__LINE__);
	MessageBox(0, "ShopPointer gefunden", DbgOutput.c_str(), MB_ICONASTERISK);
	DbgOutput = 
		"PlayerPointer: " + to_hexstring(PlayerPointer) + win_endl
		"NetPointer: " + to_hexstring(NetPointer) + win_endl
		"SendItemUseToItemCall: " + to_hexstring(SendItemUseToItemCall) + win_endl
		"SlotOffset: " + to_hexstring(SlotOffset) + win_endl
		"ItemIndexOffset: " + to_hexstring(ItemIndexOffset) + win_endl
		"SendShopBuyCall: " + to_hexstring(SendShopBuyCall) + win_endl
		"ItemAttributeValueOffset: " + to_hexstring(ItemAttributeValueOffset) + win_endl
		"ItemAttributeTypeOffset: " + to_hexstring(ItemAttributeTypeOffset) + win_endl
		"ShopSlotOffset: " + to_hexstring(ShopSlotOffset) + win_endl
		"ShopItemIDOffset: " + to_hexstring(ShopItemIDOffset) + win_endl
		"ShopItemCountOffset: " + to_hexstring(ShopItemCountOffset) + win_endl
		"ShopPointer: " + to_hexstring(ShopPointer);
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