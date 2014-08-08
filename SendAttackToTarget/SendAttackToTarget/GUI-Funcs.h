int GetSearchPattern()
{
	char tValue[3];

	GetPrivateProfileString(sSettings, sSearchPattern, "-1", tValue, 3, IniFullPath);
	return atoi(tValue);
}