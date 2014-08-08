void DropItems()
{
	for (int i = 0;i < 90;i++)
	{
		if (GetItemIndex(i))
			SendDropItem(i, 200);
	}
}