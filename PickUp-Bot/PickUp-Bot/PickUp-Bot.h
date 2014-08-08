DWORD InstantPickUpAddie;

void ActivatePickUpBot();
void DeactivatePickUpBot();
void ActivateInstantPickUp();
void DeactivateInstantPickUp();
void Picken();

void ActivatePickUpBot()
{
	PickUpBotThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Picken, 0, 0, 0);
	EnableWindow(PickUpBotButton[1], false);
	EnableWindow(PickUpBotButton[2], true);
}

void DeactivatePickUpBot()
{
	EnableWindow(PickUpBotButton[1], true);
	EnableWindow(PickUpBotButton[2], false);
	if (PickUpBotThread)
	{
		TerminateThread(PickUpBotThread, 0);
		CloseHandle(PickUpBotThread);
		PickUpBotThread = 0;
	}
}

void ActivateInstantPickUp()
{
	BYTE PatchBytes[5] = {0x83, 0xC0, 0x00, 0x90, 0x90};
	DWORD buffer = 0;
	WriteProcessMemory(hProcess, (void*)(InstantPickUpAddie), &PatchBytes, sizeof(PatchBytes), &buffer);
	buffer = 0;
	SetWindowText(PickUpBotEdit[0], sDefMinSleep);
}

void DeactivateInstantPickUp()
{
	DWORD buffer = 0;
	WriteProcessMemory(hProcess, (void*)(InstantPickUpAddie), &InstantPickUpInitialBytes, sizeof(InstantPickUpInitialBytes), &buffer);
	buffer = 0;
	SetWindowText(PickUpBotEdit[0], sDefSleep);
}

void Picken()
{
	char sValue[8];
	while(true)
	{
		PickCloseItem();
		GetWindowText(PickUpBotEdit[0], sValue, 8);
		Sleep(atoi(sValue));
	}
}