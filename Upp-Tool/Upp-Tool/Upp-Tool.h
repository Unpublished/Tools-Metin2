void Uppen(int iMode = 0)
{
	char szTemp[8];
	std::string tValue;
	int iToSlot = 1, iEnde = 1;

	if (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[0]) == BST_CHECKED)
	{
		GetWindowText(UppToolEdit[0], szTemp, 8);
		iEnde = atoi(szTemp);
		if (iEnde == 0)
		{
			MessageBox(0, "Die Anzahl der Upp-Vorgänge muss mindestens 1 betragen!", sError, MB_SYSTEMMODAL + MB_ICONERROR);
			return;
		}
	}

	if (IsDlgButtonChecked(WindowHandle, IDC_BUTTON[1]) == BST_CHECKED)
	{
		GetWindowText(UppToolEdit[3], szTemp, 8);
		iToSlot = atoi(szTemp);
		if (iToSlot == 0)
		{
			MessageBox(0, "Der begrenzende Slot muss mindestens 1 betragen!", sError, MB_SYSTEMMODAL + MB_ICONERROR);
			return;
		}
	}

	for (int i = 0;i < iToSlot;i++)
	{
		for (int j = 0;j < iEnde;j++)
		{
			if (iMode > 0)
			{
				GetWindowText(UppToolEdit[iMode - 1], szTemp, 8);
				int Slot = SearchItem(atoi(szTemp));
				if (Slot == -1)
				{
					MessageBox(0, "Keine Segis/kein magisches Metall gefunden!", sError, MB_SYSTEMMODAL + MB_ICONERROR);
					return;
				}
				SendItemUseToItem(i, Slot);
				SendRefine(iMode, i);
			}
			else
				SendRefine(0, i);
			Sleep(250);
		}
	}
	return;
}