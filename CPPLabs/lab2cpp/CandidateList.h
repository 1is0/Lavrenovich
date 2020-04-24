//---------------------------------------------------------------------------

#ifndef CandidateListH
#define CandidateListH
#include "Candidate.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <System.Classes.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.StrUtils.hpp>
class CandidateList
{
	Candidate *list;
	int capacity, num;
public:
	CandidateList();
	CandidateList(const CandidateList& rhs);
	~CandidateList();

	Candidate& operator[](int offset);
	int GetNum(){return num;}
	void ShowAll(TListBox* LB);
	void AddNew(Candidate &cand);
	void SortByName(TListBox* LB);
	void Delete();
	void Clear();
	void Save();
	void Load();
	bool isEmpty(){return (num)?false:true; }
};
#endif
