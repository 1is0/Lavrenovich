//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "ForwList.h"
#include "Data.h"
#include <cstring>
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
ForwList* list;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	list = new ForwList();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
	try
	{
		if(NameEdit->Text.Trim() == "")
			throw -1;

		std::string name = AnsiString(NameEdit->Text.Trim().c_str()).c_str();
		int cost = StrToInt(CostEdit->Text.Trim()),
			amount = StrToInt(AmountEdit->Text.Trim());
		TDateTime tmpDate = DateTimePicker->Date;
		Data tmp(name, amount, cost, tmpDate);
		list->PushBack(tmp);
	}
	catch(EConvertError &e)
	{
		ShowMessage("Bad input.");
		return;
	}
	catch(...)
	{
		ShowMessage("Bad input.");
		return;
	}
	list->ShowAll();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
	if(list)
		delete list;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ExitButtonClick(TObject *Sender)
{
	Form1->DestroyComponents();
	Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FindByNameClick(TObject *Sender)
{
	std::string name;
	try
	{
		if(ToFindEdit->Text.Trim() == "")
			throw -1;
		name = AnsiString(ToFindEdit->Text.Trim().c_str()).c_str();
		list->FindName(REInfoBoard, name);
	}
	catch(...)
	{
		ShowMessage("Bad input.");
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindByAmountClick(TObject *Sender)
{
	int amount;
	try
	{
		if(ToFindEdit->Text.Trim() == "")
			throw -1;
		amount = StrToInt(ToFindEdit->Text.Trim());
		if(amount < 0)
			throw -1;
		list->FindAmountInStock(REInfoBoard, amount);
	}
	catch(EConvertError &e)
	{
		ShowMessage("Bad input.");
		return;
	}
	catch(...)
	{
		ShowMessage("Bad input.");
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindByCostClick(TObject *Sender)
{
	int cost;
	try
	{
		if(ToFindEdit->Text.Trim() == "")
			throw -1;
		cost = StrToInt(ToFindEdit->Text.Trim());
		if(cost < 5)//5$ �������
			throw -1;
		list->FindCost(REInfoBoard, cost);
	}
	catch(EConvertError &e)
	{
		ShowMessage("Bad input.");
		return;
	}
	catch(...)
	{
		ShowMessage("Bad input.");
		return;
	}
}
//---------------------------------------------------------------------------

