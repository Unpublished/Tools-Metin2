void ActivateSpamBot();
void DeactivateSpamBot();
void Spammen();

void ActivateSpamBot()
{
	if (ChatOccurrence == -1)
	{
		ChatOccurrence = 2;
		WritePrivateProfileString(Spam_Bot, "ChatOccurrence", "1", IniFullPath);
	}

	SpamBotThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Spammen, 0, 0, 0);
	EnableWindow(SpamBotButton[0], false);
	EnableWindow(SpamBotButton[1], true);
}

void DeactivateSpamBot()
{
	EnableWindow(SpamBotButton[0], true);
	EnableWindow(SpamBotButton[1], false);
	if (SpamBotThread)
	{
		TerminateThread(SpamBotThread, 0);
		CloseHandle(SpamBotThread);
		SpamBotThread = 0;
	}
	if (ChatOccurrence == 2)
	{
		WritePrivateProfileString(Spam_Bot, "ChatOccurrence", "0", IniFullPath);
	}
}

void Spammen()
{
	char Temp[8];
	int ChatModus = SendMessage(SpamBotCombo[0], CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	switch (ChatModus)
	{
	case 1:
		ChatModus = 6;
		break;
	case 2:
		ChatModus = 4;
		break;
	}
	GetWindowText(SpamBotEdit[1], Temp, 8);
	int Anzahl = atoi(Temp);
	int Counter = 1;
	memset(&Temp[0], 0, sizeof(Temp));
	while(true)
	{
		SendChat(SpamText.c_str(), ChatModus);
		if (Anzahl > 0)
		{
			if (Counter == Anzahl)
			{
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DeactivateSpamBot, 0, 0, 0);
				break;
			}

			Counter++;
		}
		Sleep(SleepTime);
	}
}