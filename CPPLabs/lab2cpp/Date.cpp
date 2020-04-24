//---------------------------------------------------------------------------


#pragma hdrstop
#include "Date.h"

MDate::MDate(uint d, uint m, uint y)
{
	day = d;
	month = m;
	year = y;
}

MDate::MDate(const MDate& rhs)
{
	this->day = rhs.day;
	this->month = rhs.month;
	this->year = rhs.year;
}

MDate::MDate()
{
	time_t now = time(0);
	tm* lctm = localtime(&now);

	year = 1900 + lctm->tm_year;
	month = 1 + lctm->tm_mon;
	day = lctm->tm_mday;
}

MDate& MDate::operator=(const MDate& rhs)
{
	day = rhs.day;
	month = rhs.month;
	year = rhs.year;
	return *this;
}

void MDate::MToStr(AnsiString &s)
{
	char* ctmp = new char[11];
	ctmp[0] = (char)(day / 10 + '0');
	ctmp[1] = (char)(day % 10 + '0');
	ctmp[2] = ':';
	ctmp[3] = (char)(month / 10 + '0');
	ctmp[4] = (char)(month % 10 + '0');
	ctmp[5] = ':';
	int y = year, i = 9;
	while(y)
	{
		ctmp[i--] = (char)(y % 10 + '0');
		y /= 10;
	}
	ctmp[10] = '\0';
	s = ctmp;
	delete[] ctmp;
}

#pragma package(smart_init)
