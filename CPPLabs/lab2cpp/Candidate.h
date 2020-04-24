//---------------------------------------------------------------------------

#ifndef CandidateH
#define CandidateH
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.StrUtils.hpp>
#include "Position.h"
#include "Date.h"
#include <vcl.h>
typedef unsigned int uint;
class Candidate
{
	AnsiString fullName, spec;
	Position pos;
	MDate dateOfBirth;
	bool highEd;
	uint minRate;
public:
	Candidate();
	Candidate(AnsiString fnm, AnsiString sp, Position p, MDate dob, bool ed, uint mr);
	Candidate(const Candidate& rhs);
	~Candidate();
	const AnsiString& GetFullName(){return fullName;}
	const AnsiString& GetSpecialization(){return spec;}
	Position GetPos(){return pos;}
	MDate& GetDateOfBirth(){return dateOfBirth;}
	bool GetEducation(){return highEd;}
	uint GetMinRate(){return minRate;}
	bool operator==(const Candidate& rhs);
	Candidate& operator=(const Candidate& rhs);
	void CandToStr(AnsiString &s);
};
#endif
