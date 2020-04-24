//---------------------------------------------------------------------------

#pragma hdrstop

#include "HashTable.h"
HashTable::HashTable()
{
	for (int i=0; i < size; i++)
		table[i] = Stack<AnsiString>();
}

int HashTable::hkey(AnsiString data)
{
	double key = 0;
	for (int i = 1; i <= data.Length(); i++)
		if (i&1)
			key += data[i] / pow(2.0, (double)(i % 10)) - pow(5, 0.2);
		else
			key -= data[i] / pow(2.0, (double)(i % 10)) + pow(5, 0.2);
	int ikey = (int)round(key);
	if (ikey < 0)
		ikey = ikey % 10 + 10;

	return 1 + ikey % 10;
}

bool HashTable::Has(AnsiString data)
{
	 int key = hkey(data) - 1;
	 bool has = false;
	 Stack<AnsiString> tmp;
	 while(!table[key].isEmpty())
	 {
		 if (table[key].headInfo() != data)
			tmp.push(table[key].pop());
		 else
		 {
			has = true;
			break;
		 }
	 }
	 while(!tmp.isEmpty())
         table[key].push(tmp.pop());

     return has;
}

void HashTable::Add(AnsiString data)
{
    int key = hkey(data) - 1;
	//проверить на существование
	if(Has(data))
		return;
	table[key].push(data);
}

void HashTable::Delete(AnsiString data)
{
	 int key = hkey(data) - 1;
	 Stack<AnsiString> tmp;
	 while(!table[key].isEmpty())
	 {
		 if (table[key].headInfo() != data)
			tmp.push(table[key].pop());
		 else
		 {
            table[key].pop();
			break;
		 }
	 }
	 while(!tmp.isEmpty())
		 table[key].push(tmp.pop());
}

void HashTable::Print(TMemo* Memo)
{
	Memo->Lines->Clear();
	Stack<AnsiString> tmp;
	AnsiString s;
	for (int i = 0; i < size; i++)
	{
		Memo->Lines->Add(IntToStr(i + 1) + " : ");

		while(!table[i].isEmpty())
		{
            s = table[i].pop();
			tmp.push(s);
			Memo->Lines->Strings[i] += s + "; ";
		}
		while(!tmp.isEmpty())
            table[i].push(tmp.pop());
	}
}
#pragma package(smart_init)
