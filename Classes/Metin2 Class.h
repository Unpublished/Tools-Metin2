DWORD NetPointer, PlayerPointer, ShopPointer;

DWORD PickCloseItemCall;
DWORD SendChatCall;
DWORD SendAttackCall;
DWORD SendDropItemCall;
DWORD SendItemUseCall;
DWORD SendItemUseToItemCall, SendShopBuyCall;
DWORD SendRefineCall;

DWORD ItemIndexOffset, SlotOffset;
DWORD TargetVIDOffset;
DWORD ItemAttributeValueOffset, ItemAttributeTypeOffset, ShopSlotOffset, ShopItemIDOffset, ShopItemCountOffset;

bool IsInGame();
int SearchItem(int ID);
int ShopSearchItem(int ID);

int GetItemIndex(int Slot);
int ShopGetItemID(int Slot);

//simplified functions
bool IsInGame()
{
	bool i = false;
	for (int j = 0; j < 20; j++)
	{
		if (GetItemIndex(j) == 0)
			continue;

		i = true;
	}
	return i;
}

int SearchItem(int ID)
{
	for (int i = 0; i < 90; i++)
	{
		if (GetItemIndex(i) == ID)
			return i;
	}
	return -1;
}

int ShopSearchItem(int ID)
{
	for (int i = 0; i < 40; i++)
	{
		if (ShopGetItemID(i) == ID)
			return i;
	}
	return -1;
}


//returning Standard-Functions
//Inventar
int GetItemAttributeValue(int Slot, int Zeile)
{
	if (Slot > 89 && Slot < 0)
		return -1;
	else if (Zeile > 6 && Zeile < 0)
		return -1;

	DWORD *SlotPointer = (DWORD*) (PlayerPointer);
	DWORD Offset = ItemAttributeValueOffset + SlotOffset*Slot + 0x3 * Zeile;
	DWORD SlotPointerValue = *SlotPointer;
	short *SlotAdresse = (short*) (SlotPointerValue + Offset);

	return *SlotAdresse;
}

int GetItemAttributeType(int Slot, int Zeile)
{
	if (Slot > 89 && Slot < 0)
		return -1;
	else if (Zeile > 6 && Zeile < 0)
		return -1;

	DWORD *SlotPointer = (DWORD*) (PlayerPointer);
	DWORD Offset = ItemAttributeTypeOffset + SlotOffset*Slot + 0x3*Zeile;
	DWORD SlotPointerValue = *SlotPointer;
	char *SlotAdresse = (char*) (SlotPointerValue + Offset);

	return *SlotAdresse;
}

int GetItemIndex(int Slot)
{
	if (Slot > 89 && Slot < 0)
		return -1;

	DWORD	*SlotPointer = (DWORD*) (PlayerPointer);
	DWORD	Offset = ItemIndexOffset + SlotOffset*Slot;
	DWORD	PointerValue = *SlotPointer;
	DWORD	*SlotAdresse = (DWORD*) (PointerValue + Offset);

	return *SlotAdresse;
}

//Environment
int GetTargetVID()
{
	DWORD	*SlotPointer		= (DWORD*)(PlayerPointer);
    DWORD	SlotPointerValue	= *SlotPointer;
	DWORD	*SlotAdresse		= (DWORD*) (SlotPointerValue + TargetVIDOffset);

	//char dbg[8];
	//sprintf_s(dbg, 8, "%i", *SlotAdresse);
	//MessageBox(0, dbg, "D", 0);

	return *SlotAdresse;
}

//Shop
int ShopGetItemID(int Slot)
{
    if (Slot > 40 && Slot < 0)
        return -1;
	
	DWORD *SlotPointer		= (DWORD*)(ShopPointer);
	DWORD Offset			= ShopItemIDOffset + ShopSlotOffset*Slot;
	DWORD SlotPointerValue	= *SlotPointer;
	DWORD *SlotAdresse		= (DWORD*)(SlotPointerValue + Offset);

	return *SlotAdresse;
}

int ShopGetItemCount(int Slot)
{
    if (Slot > 40 && Slot < 0)
        return -1;

    DWORD *SlotPointer		= (DWORD*)(ShopPointer);
	DWORD Offset			= ShopItemIDOffset + ShopItemCountOffset + ShopSlotOffset*Slot;//(0x10 + 0xC)=0x1C #(Hardcore Reloaded)
    DWORD SlotPointerValue	= *SlotPointer;
    DWORD *SlotAdresse		= (DWORD*)(SlotPointerValue + Offset);

    return *SlotAdresse;
}

int ShopIsOpen()
{
	DWORD *SlotPointer		= (DWORD*)(ShopPointer);
	DWORD Offset			= 0x4;
	DWORD SlotPointerValue	= *SlotPointer;
	DWORD *SlotAdresse		= (DWORD*)(SlotPointerValue + Offset);
	
    return *SlotAdresse;
}

//void functions
void PickCloseItem()
{
	DWORD Addie = *(DWORD*) PlayerPointer;
	__asm
	{
		MOV ECX, [Addie]
			CALL PickCloseItemCall
	}
}

void SendAttack(int VID)
{
	DWORD Addie = *(DWORD*) NetPointer;
	__asm
	{
		MOV ECX, Addie
			PUSH VID
			PUSH 0
			CALL SendAttackCall
	}
}

void SendChat(const char *Text, int Modus)
{
	DWORD Addie = *(DWORD*) NetPointer;
	__asm
	{
		MOV ECX, Addie
			PUSH Modus
			PUSH Text
			CALL SendChatCall
	}
}

void SendDropItem(int Slot, int Count)
{
	DWORD Addie = *(DWORD*) NetPointer;
	__asm
	{
		MOV ECX, Addie
			PUSH Count
			PUSH 0
			PUSH Slot
			CALL SendDropItemCall
	}
}

void SendItemUse(int Slot)
{
	DWORD Addie = *(DWORD*)NetPointer;
	__asm
	{
			PUSH Slot
			MOV ECX, Addie
			CALL SendItemUseCall
	}
}

//int(*SendItemUseToItem)(int, int) = (int(*)(int, int))0x4E2420;
/* Try to make it compatible with latest binary

void SendItemUseToItem(int Target, int Slot)
{
	DWORD Addie = *(DWORD*)NetPointer;
	//DWORD dwTarget = *(DWORD*)Target;
	WORD lwTarget = *(WORD*)Target;
	BYTE lbTarget = *(BYTE*)Target;
	WORD lwSlot = *(WORD*)Slot;
	BYTE lbSlot = *(BYTE*)Slot;
	__asm
	{
		PUSH Target
		MOVZX EAX, ESP
		PUSH Target
		MOV ECX, ESP
		PUSH ECX
		MOV WORD PTR DS : [ECX], AX
		MOV AL, lbTarget
		MOV BYTE PTR DS : [ECX + 2], AL
		MOVZX EAX, lwSlot
		MOV ECX, ESP
		MOV WORD PTR DS : [ECX], AX
		MOV AL, lbSlot
		MOV BYTE PTR DS : [ECX + 2], AL
		MOV ECX, Addie
		CALL SendItemUseToItemCall	
	}
}*/

void SendItemUseToItem(int Target, int Slot)
{
	DWORD Addie = *(DWORD*)NetPointer;
	__asm
	{
		MOV ECX, Addie
		PUSH Target
		PUSH Slot
		CALL SendItemUseToItemCall
	}
	//Note: this is untested...got lost of the original function while trying the above but this should be fine
}
void SendShopBuy(int Slot)
{
	DWORD Addie = *(DWORD*)NetPointer;
	__asm
	{
		MOV ECX, Addie
		PUSH Slot
		CALL SendShopBuyCall
	}
}

void SendRefine(int iMode, int iSlot)
{
	DWORD Addie = *(DWORD*)NetPointer;
	__asm
	{
		MOV ECX, Addie
		PUSH iMode //0 = Stadt-Schmied, 2 = Segi, 4 = DT
		PUSH iSlot
		CALL SendRefineCall
	}
}
