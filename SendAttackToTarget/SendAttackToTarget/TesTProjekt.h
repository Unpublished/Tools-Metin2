void TesTProjekt()
{
	char	szSleep[8];
	int		iSleep;
	while (true)
	{
		if (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_CHECKED)
		{
			int TargetVID = GetTargetVID();
			SendAttack(TargetVID);
		}
		GetWindowText(SleepEdit, szSleep, 8);
		iSleep = atoi(szSleep);
		Sleep((iSleep < 250) ? 250 : iSleep);
	}
}