//---------------------------------------------------------------------------

#ifndef FirmH
#define FirmH
#include "Position.h"
#include <string>
#include <string>
#include <cstdlib>
#include <vcl.h>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.StrUtils.hpp>
typedef unsigned int uint;
class Firm
{
	AnsiString name, spec;
	Position pos;
	uint rate, vacDays, minYears, maxYears;
	bool highEdNeeded;
public:
	Firm();
	Firm(AnsiString nm, AnsiString sp, uint rt, uint vD, uint mny, uint mxy,
		 bool ed, Position p);
	Firm(const char* nm, const char* sp, uint rt, uint vD, uint mny, uint mxy,
		 bool ed, Position p);
	Firm(const Firm& rhs);
	~Firm();
	const AnsiString& GetName(){return name;}
	const AnsiString& GetSpec(){return spec;}
	Position GetPos(){return pos;}
	uint GetRate(){return rate;}
	uint GetVacDays(){return vacDays;}
	uint GetMinYears(){return minYears;}
	uint GetMaxYears(){return maxYears;}
	bool GetEdNeeded(){return highEdNeeded;}
	bool operator==(const Firm& rhs);
	Firm& operator=(const Firm& rhs);
};
#endif
