#include "Converting.h"

int Converting::getASCI(Uint32 in_st,bool isCaps)
{
	if (in_st == -1 && isCaps)
		isCaps = false;
	else if (in_st == -1 && !isCaps)
		isCaps = true;
	if (in_st >= 0 && in_st < 25)
		if (!isCaps)
			in_st += 97;
		else
			in_st += 65;
	else
		if (in_st == 59)
			in_st = 8;
		else
			if (in_st > 25 && in_st < 37)
				in_st += 22;
			else
				in_st = -999;
	return in_st;
}

Text Converting::string2text(string st)
{
	Text text;
	wstringstream ost;
	wstring q;
	wchar_t Mass[255];
	MultiByteToWideChar(0, 0, st.c_str(), -1, Mass, 255);
	ost << Mass;
	q = ost.str();
	text.setString(q);
	return text;
}
string Converting::int2string(int number)
{
	string st;
	char ch;
	int TempOst, TempCel = number, i = 0;
	while (TempCel != 0)
	{
		TempOst = TempCel % 10;
		TempCel /= 10;
		ch = TempOst + '0';
		st = ch + st;
	}
	return st;
}