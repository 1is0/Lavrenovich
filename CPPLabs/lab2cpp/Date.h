//---------------------------------------------------------------------------

#ifndef DateH
#define DateH
#include <vcl.h>
#include <string>
#include <cstring>
#include <cstdlib>
#include <time.h>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.StrUtils.hpp>
typedef unsigned int uint;

class MDate
{
	uint day;
	uint month;
	uint year;
public:
	MDate();
	MDate(uint d, uint m, uint y);
	MDate(const MDate& rhs);
	uint GetDay(){return day;}
	uint GetMonth(){return month;}
	uint GetYear(){return year;}
	MDate& operator=(const MDate& rhs);
	void MToStr(AnsiString &s);
};

MDate StrToMDate(AnsiString str)
{
	//char* cstr = str.c_str();
	if(str.Length() != 10)
	{
		//delete cstr;
		throw -1;
	}
	if(str[3] != ':' || str[6] != ':')
	{
		//delete cstr;
		throw -1;
	}
	uint d = 0, m = 0, y = 0;
	if(isdigit(str[1]) && isdigit(str[2]) && isdigit(str[4]) && isdigit(str[5])
	   && isdigit(str[7]) && isdigit(str[8]) && isdigit(str[9]) && isdigit(str[10]) )
	{
		d = (str[1] - '0') * 10 + (str[2] - '0');
		m = (str[4] - '0') * 10 + (str[5] - '0');
		y = (str[7] - '0') * 1000 + (str[8] - '0') * 100 + (str[9] - '0') * 10
			 + (str[10] - '0');
		//проверка на адекватность введённой даты

	}
	else
	{
		//delete cstr;
		throw -1;
	}

	//delete cstr;
	return MDate(d, m, y);
}

char IsLeapYear(uint& year)//проверка на високосный год
{
	if (!(year % 4))//делится на 4 без остатка
	{
		if (!(year % 100))//делится на 100 без остатка
		{
			if (!(year % 400))//делится на 400
				return 1;
			else
				return 0;
		}
		else
			return 1;//не столетие => високосный
	}
	else
		return 0;
}
char CheckDate(MDate& date)//проверка ввода даты
{
	if (date.GetYear() <= 1940 || date.GetYear() >= 2002)
		return 0;
	if (date.GetMonth() < 1 || date.GetMonth() > 12)
		return 0;
	if (date.GetDay() > 31 || date.GetDay() <= 0)
		return 0;

	if (date.GetDay() <= 31 && (date.GetMonth() & 1) && date.GetMonth() < 8)//янв март май июль
		return 1;
	else if (date.GetDay() <= 30 && !(date.GetMonth() & 1) && date.GetMonth() < 8)//апр июнь
	{
		if (date.GetMonth() == 2)
		{
			if (date.GetDay() <= 29 && IsLeapYear(date.GetYear()))//февр в високосный год
				return 1;
			else if (date.GetDay() <= 28 && !IsLeapYear(date.GetYear()))//февр в обычный год
				return 1;
			else
				return 0;
		}
		else
			return 1;
	}
	else if (date.GetDay() <= 31 && !(date.GetMonth() & 1) && date.GetMonth() >= 8)//авг окт дек
		return 1;
	else if (date.GetDay() <= 30 && (date.GetMonth() & 1) && date.GetMonth() >= 8)//сент ноя
		return 1;
	else
		return 0;
}

int JDN(MDate& d)//расчёт Юлианского дня по дате Григорианского календаря
{
	int a, y, m;
	a = (14 - (int)d.GetDay()) / 12;
	y = (int)d.GetYear() + 4800 - a;
	m = (int)d.GetMonth() + 12 * a - 3;
	return (int)d.GetDay() + ((153 * m + 2) / 5) + 365*y + y/4 - y/100 + y/400 - 32045;
}

int TotalDays(MDate &d1, MDate &d2)//рассчёт кол-ва календарных дней
{
	return JDN(d2) - JDN(d1);
}
#endif
