int GetSearchPattern()
{
	char Wert[3];

	GetPrivateProfileStringA(sSettings, sSearchPattern, "-1", Wert, 3, IniFullPath);
	return atoi(Wert);
}