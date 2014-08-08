bool AlternativBonis[5][2];

bool SwitchBotActive[2];
int SlotDefinition;
int SwitchBotPointer[5][2], SwitchBotModeCount[2];
int WunschBoniValue[5][14];
int WunschBoniType[5][14];
int RealBoni[5][7][2];
int ItemID[5];

int MinSwitchZeit = 500, SwitchItemValue[2];
int BoniTypeValues[80] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81};
void Switchen(), Optionen();
void DeactivateSwitchBot(int Slot, int Mode);

bool CheckBoni(int Slot, int WunschType, int WunschValue, int Mode)
{
	int Start, Ende;
	if (!Mode)
		Start = 0, Ende = 5;
	else
		Start = 5, Ende = 7;

	for (int Zeile = Start; Zeile < Ende; Zeile++)
	{
		if (RealBoni[Slot][Zeile][0] == WunschType)
		{
			if (RealBoni[Slot][Zeile][1] >= WunschValue)
				return true;
		}
	}
	return false;
}

void ActivateSwitchBot(int Slot, int Mode)
{
	int Counter = 0;
	char BoniValue[8];
	int BoniType;
	int Start, Ende, StartButton;

	if (Mode == 0)
		Start = 0, Ende = 5, StartButton = 0;
	else
		Start = 5, Ende = 7, StartButton = 35;

	EnableWindow(SwitchBotButtonStarten[Slot][Mode], false);
	EnableWindow(SwitchBotButtonStoppen[Slot][Mode], true);
	while (Start < 13)
	{
		for (int i = Start; i < Ende; i++)
		{
			WunschBoniValue[Slot][i] = 0;
			WunschBoniType[Slot][i] = 0;
			GetWindowText(SwitchBotBonusEdit[Slot][i], BoniValue, 8);

			if (atoi(BoniValue) == 0)
				continue;

			BoniType = SendMessage(SwitchBotBonusCombo[Slot][i], CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);

			if (BoniType == -1 || BoniType == 50 || BoniType == 56 || BoniType == 68)
				continue;

			WunschBoniValue[Slot][Start + Counter] = atoi(BoniValue);
			WunschBoniType[Slot][Start + Counter] = BoniTypeValues[BoniType];
			/*char Debug[4];
			sprintf(Debug, "Counter: %i\n%i\n%i", Counter, WunschBoniType[Slot][Counter], BoniType);
			MessageBox(0, Debug, "", 0);*/
			Counter += 1;
		}
		Start += 7, Ende += 7, Counter = 0;
		if (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[StartButton + Slot]) == TRUE)
		{
			AlternativBonis[Slot][Mode] = 1;
			continue;
		}

		AlternativBonis[Slot][Mode] = 0;
		break;
	}

	if (WunschBoniValue[Slot][Start - 7] == 0)
	{
		DeactivateSwitchBot(Slot, Mode);
	}
	else
	{
		if (SwitchBotPointer[Slot][Mode] == 1)
		{
			DeactivateSwitchBot(Slot, Mode);
			return;
		}
		if (!SwitchBotActive[Mode])
			SwitchBotActive[Mode] = true;

		SwitchBotModeCount[Mode] += 1;
		SwitchBotPointer[Slot][Mode] = 1;
		SwitchBots += 1;
		if (SwitchBots == 1)
		{
			GetWindowText(SwitchBotEdit[4], BoniValue, 8);
			SlotDefinition = atoi(BoniValue) - 1;
			SlotDefinition = (SlotDefinition > 84) ? 84 : SlotDefinition;
			SwitchBotThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Switchen, 0, 0, 0);
			Sleep(250);
			OptionenThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Optionen, 0, 0, 0);
		}
	}
	Start = DELETE, Ende = DELETE, BoniType = DELETE, StartButton = DELETE, Counter = DELETE;
}

void DeactivateSwitchBot(int Slot, int Mode)
{
	int Start, Ende;
	bool IsSwitchBot = false;
	if (!Mode)
		Start = 0, Ende = 5;
	else
		Start = 5, Ende = 7;

	EnableWindow(SwitchBotButtonStarten[Slot][Mode], true);
	EnableWindow(SwitchBotButtonStoppen[Slot][Mode], false);
	if (SwitchBotPointer[Slot][Mode] == 1)
	{
		SwitchBotPointer[Slot][Mode] = 0;
		SwitchBotModeCount[Mode] -= 1;
		SwitchBots -= 1;
	}
	for (int i = 0; i < 5; i++)
	{
		RealBoni[Slot][i][0] = 0;
		RealBoni[Slot][i][1] = 0;
		if (SwitchBotPointer[i][Mode] == 1)
			IsSwitchBot = true;
	}
	if (!IsSwitchBot)
		SwitchBotActive[Mode] = false;

	ItemID[Slot] = 0, Start = 0, Ende = 0;
}

void SwitchBotFailure(const int Parameter[2])
{
	if (IsInGame() == true)
	{
		char MessageText[128];
		DeactivateSwitchBot(Parameter[0], Parameter[1]);
		if (GetItemIndex(Parameter[0]) == 0)
		{
			sprintf_s(MessageText, "Auf dem Slot #%i befindet sich kein Item, der Switch-Bot wurde auf diesem Slot deaktiviert.", SlotDefinition + Parameter[0] + 1);
			DeactivateSwitchBot(Parameter[0], (Parameter[1] == 0) ? 1 : 0);
		}
		else
		{
			char sModus[8];
			if (Parameter[1] == 0)
				sprintf_s(sModus, "%s", "1. - 5");
			else
				sprintf_s(sModus, "%s", "6. && 7");

			sprintf_s(MessageText, "Das Item auf Slot #%i hat keine Bonis, der Switch-Bot wurde auf diesem Slot für den %s. Bonus deaktiviert.", Parameter[0] + 1, sModus);
		}
		MessageBox(0, MessageText, sError, MB_SYSTEMMODAL + MB_ICONERROR);
	}
}

void SwitchBotItemChanged(int Slot)
{
	char MessageText[128];
	bool OldStatus[2] = { false, false };
	for (int i = 0; i < 2; i++)
	{
		if (SwitchBotPointer[Slot][i])
		{
			DeactivateSwitchBot(Slot, i);
			OldStatus[i] = true;
			EnableWindow(SwitchBotButtonStarten[Slot][i], false);
			EnableWindow(SwitchBotButtonStarten[Slot][i], false);
		}
	}
	sprintf_s(MessageText, "Auf dem Slot #%i befindet sich ein anderes Item!\n\nSoll der Switch-Bot auf diesem Slot deaktiviert werden?", Slot + 1);
	if (MessageBox(0, MessageText, sWarning, MB_YESNO | MB_ICONQUESTION + MB_SYSTEMMODAL) == IDNO)
	{
		for (int i = 0; i < 2; i++)
		{
			if (OldStatus[i] == true)
				ActivateSwitchBot(Slot, i);
			else
				DeactivateSwitchBot(Slot, i);
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
			DeactivateSwitchBot(Slot, i);
	}
}

void SwitchBotSuccess(const int Parameter[3])
{
	char title[128], content[128];
	DeactivateSwitchBot(Parameter[0], Parameter[1]);
	sprintf_s(title, "Slot #%i erfolgreich!", Parameter[0] + 1);
	if (Parameter[1] == 0)
		sprintf_s(content, "Slot #%i: 1. - 5. Bonus Einstellung #%i erreicht.", Parameter[0] + 1, Parameter[2]);
	else
		sprintf_s(content, "Slot #%i: 6. und 7. Bonus Einstellung #%i erreicht.", Parameter[0] + 1, Parameter[2]);

	MessageBox(0, content, title, MB_SYSTEMMODAL + MB_ICONINFORMATION);
}

void Switchen()
{
	int SwitchZeitFormel, ItemIDNew;
	char szEdit[8];
	bool CheckItem;
	while (SwitchBots)
	{
		SwitchZeitFormel = MinSwitchZeit + (100 * (SwitchBots - 1) - 150);
		GetWindowText(SwitchBotEdit[0], szEdit, 8);
		SleepTime = (atoi(szEdit) - 150 < SwitchZeitFormel) ? SwitchZeitFormel : atoi(szEdit) - 150;
		if (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[73]) == BST_CHECKED)
			CheckItem = true;
		else
			CheckItem = false;

		for (int Slot = 0; Slot < 5; Slot++)
		{
			if (SwitchBotActive[0])
			{
				if (SwitchBotPointer[Slot][0])
				{
					if (CheckItem == true)
					{
						//Prüfen ob sich die ID geändert hat
						ItemIDNew = GetItemIndex(Slot);
						if (ItemID[Slot] && ItemID[Slot] != ItemIDNew && ItemIDNew)
						{
							CreateThread(0, 0, (LPTHREAD_START_ROUTINE) SwitchBotItemChanged, (LPVOID) Slot, 0, 0);
							ItemID[Slot] = ItemIDNew;
							continue;
						}
						ItemID[Slot] = ItemIDNew;
					}

					for (int i = 0; i < 5; i++)
					{
						RealBoni[Slot][i][0] = GetItemAttributeType(SlotDefinition + Slot, i);
						RealBoni[Slot][i][1] = GetItemAttributeValue(SlotDefinition + Slot, i);
					}
					if (RealBoni[Slot][0][0] >= BoniTypeValues[0] && RealBoni[Slot][0][0] <= BoniTypeValues[79])
					{
						for (int j = 0; j < 2; j++)
						{
							bool Check[5] = { false, false, false, false, false };
							for (int i = 0; i < 5; i++)
							{
								if (!WunschBoniType[Slot][i + j * 7] || !WunschBoniValue[Slot][i + j * 7])
								{
									Check[i] = true;
									continue;
								}
								Check[i] = CheckBoni(Slot, WunschBoniType[Slot][i + j * 7], WunschBoniValue[Slot][i + j * 7], 0);
							}
							if (Check[0] == true && Check[1] == true && Check[2] == true && Check[3] == true && Check[4] == true)
							{
								int Parameter[3] = { Slot, 0, j + 1 };
								CreateThread(0, 0, (LPTHREAD_START_ROUTINE) SwitchBotSuccess, (LPVOID) Parameter, 0, 0);
								break;
							}
							if (AlternativBonis[Slot][0] == true && j == 0)
								continue;

							int ItemSlot = SearchItem(SwitchItemValue[0]);
							if (ItemSlot > -1)
								SendItemUseToItem(SlotDefinition + Slot, ItemSlot);

							break;
						}
					}
					else
					{
						int Parameter[2] = { Slot, 0 };
						CreateThread(0, 0, (LPTHREAD_START_ROUTINE) SwitchBotFailure, (LPVOID) Parameter, 0, 0);
					}
				}
			}
			if (SwitchBotActive[1])
			{
				if (SwitchBotPointer[Slot][1])
				{
					for (int i = 5; i < 7; i++)
					{
						RealBoni[Slot][i][0] = GetItemAttributeType(SlotDefinition + Slot, i);
						RealBoni[Slot][i][1] = GetItemAttributeValue(SlotDefinition + Slot, i);
					}
					if (RealBoni[Slot][5][0] >= BoniTypeValues[0] && RealBoni[Slot][5][0] <= BoniTypeValues[79])
					{
						for (int j = 0; j < 2; j++)
						{
							bool Check6_7[2] = { false, false };
							for (int i = 5; i < 7; i++)
							{
								if (!WunschBoniType[Slot][i + j * 7] || !WunschBoniValue[Slot][i + j * 7])
								{
									Check6_7[i - 5] = true;
									continue;
								}
								Check6_7[i - 5] = CheckBoni(Slot, WunschBoniType[Slot][i + j * 7], WunschBoniValue[Slot][i + j * 7], 1);
							}
							if (Check6_7[0] == true && Check6_7[1] == true)
							{
								int Parameter[3] = { Slot, 1, j + 1 };
								CreateThread(0, 0, (LPTHREAD_START_ROUTINE) SwitchBotSuccess, (LPVOID) Parameter, 0, 0);
								break;
							}
							else if (AlternativBonis[Slot][1] == true && j == 0)
								continue;

							int ItemSlot = SearchItem(SwitchItemValue[1]);
							if (ItemSlot > -1)
								SendItemUseToItem(SlotDefinition + Slot, ItemSlot);

							break;
						}
					}
					else
					{
						int Parameter[2] = { Slot, 1 };
						CreateThread(0, 0, (LPTHREAD_START_ROUTINE) SwitchBotFailure, (LPVOID) Parameter, 0, 0);
					}
				}
			}
			Sleep(50);
		}
		Sleep(SleepTime);
	}
}

void Optionen()
{
	char Temp[32];
	while (SwitchBots)
	{
		GetWindowText(SwitchBotEdit[1], Temp, 32);
		SwitchItemValue[0] = (atoi(Temp) == 0) ? 71084 : atoi(Temp);
		GetWindowText(SwitchBotEdit[2], Temp, 32);
		SwitchItemValue[1] = (atoi(Temp) == 0) ? 71052 : atoi(Temp);
		bool NachkäuferChecked = (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[72]) == BST_CHECKED) ? true : false;
		bool HaveSwitchItem[2] = { false, false };
		if (!IsSwitchBotRunning)
		{
			EnableWindow(SwitchBotEdit[4], false);
			IsSwitchBotRunning = true;
		}

		for (int Mode = 0; Mode < 2; Mode++)
		{
			if (!SwitchBotActive[Mode])
				continue;

			if (SearchItem(SwitchItemValue[Mode]) == -1 && NachkäuferChecked == true)
			{
				if (ShopIsOpen())
				{
					SwitchBotActive[Mode] = false;
					for (int i = 0; i < 40; i++)
					{
						if (ShopGetItemID(i) == SwitchItemValue[Mode])
						{
							for (int k = 0; SwitchBotModeCount[Mode] > k*ShopGetItemCount(i); k++)
								SendShopBuy(i);

							do
								Sleep(500);
							while (SearchItem(SwitchItemValue[Mode]) == -1);

							SwitchBotActive[Mode] = true;
							break;
						}
					}
					if (ShopSearchItem(SwitchItemValue[Mode]) == -1)
					{
						SendMessage(SwitchBotButton[2], BM_SETCHECK, 0, 0);
						MessageBox(0, "In dem geöffneten Shop befinden sich keine Switch-Item(s)!\r\n\r\nDer Nachkäufer wird deaktiviert.", sError, MB_SYSTEMMODAL + MB_ICONERROR);
					}
				}
				else if (!ShopIsOpen())
				{
					MessageBox(0, "Der Shop mit den/dem Switch-Item(s) muss offen sein!", sError, MB_SYSTEMMODAL + MB_ICONERROR);
					do
					Sleep(1000);
					while (!ShopIsOpen());
					continue;
				}
			}
			if (SearchItem(SwitchItemValue[Mode]) == -1)
			{
				for (int i = 0; i < 5; i++)
					DeactivateSwitchBot(i, Mode);

				if (Mode == 0)
					MessageBox(0, "Das Switch-Item konnte nicht gefunden werden, der Switch-Bot wurde für den 1. - 5. Bonus deaktiviert.\n\nWenn es doch im Inventar ist dann lege es ins 1. Inventar unten rechts hin und gehe zu Optionen->Auslesen.", sError, MB_SYSTEMMODAL + MB_ICONERROR);
				else
					MessageBox(0, "Das Switch-Item konnte nicht gefunden werden, der Switch-Bot wurde für den 6. & 7. Bonus deaktiviert.\n\nWenn es doch im Inventar ist dann lege es ins 1. Inventar unten rechts hin und gehe zu Optionen->Auslesen.", sError, MB_SYSTEMMODAL + MB_ICONERROR);
			}
		}
		Sleep(1000);
	}
}

void SwitchItemAuslesen(int Mode)
{
	char C_SwitchItemValue[32];
	if (!GetItemIndex(44))
	{
		MessageBox(0, "Du musst das Switch-Item ins 1. Inventar nach ganz unten rechts legen.", "Hinweis", 0x00040000L);
	}
	else
	{
		sprintf_s(C_SwitchItemValue, "%i", GetItemIndex(44));
		SetWindowText(SwitchBotEdit[1 + Mode], C_SwitchItemValue);
	}
}