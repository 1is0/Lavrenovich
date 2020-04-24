// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMain.h"
#include "Stack.h"
#include <SysUtils.hpp>
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	Sysutils::FormatSettings.DecimalSeparator = _T('.');
	//��������� ����������� �� ����� ������ �������
}

// ---------------------------------------------------------------------------
bool isoper(const char &c) {
	if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' ||
		c == '^')
		return true;
	return false;
}

int prio(const char &op) // ��������� ���������� � ���
{
	switch (op) {
	case '(':
	case ')':
		return 1;
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '^':
		return 4;
	default:
		return -1;
	}
}

double operate(double a, double b, const char &op)
{
	switch(op)
	{
	case '+':   return a + b;
	case '-':   return a - b;
	case '*':   return a * b;
	case '/':   return a / b;
	case '^':   return pow(a, b);
    default:    return -1;//error
	}
}

void RPN(const AnsiString &formula, char* polska)
{
	Stack<char> *operStack = new Stack<char>();
    int len = 0;
	// algo
	for (int i = 1; i <= formula.Length(); i++) {
		if (isoper(formula[i])) {
			if (operStack->isEmpty()) {
				operStack->push(formula[i]);
				continue;
			}

			if (formula[i] == '(') {
				operStack->push('(');
				continue;
			}

			if (formula[i] == ')') {
				while (operStack->headInfo() != '(')
					polska[len++] = operStack->pop();
				operStack->pop();
				continue;
			}

			if (prio(formula[i]) > prio(operStack->headInfo()))
				operStack->push(formula[i]);
			else if (prio(formula[i]) <= prio(operStack->headInfo())) {
				while (operStack->headInfo() != '(')
					polska[len++] = operStack->pop();
				operStack->push(formula[i]);
				// ��������� ������
			}
		}
		else if (formula[i] == '#')
			while (!operStack->isEmpty())
				polska[len++] = operStack->pop();
		else
			polska[len++] = formula[i]; // �� ������ ���� ��� ����������
	}
	Form1->PostfixFormEdit->Text = polska; // ����� �� ����� �������� ����� ������
	delete operStack;
}

void calc(char* polska, double a, double b, double c, double d, double e)
{
    // ��� ������
	Stack<double> *numStack = new Stack<double>();

	for (int i = 0; i < strlen(polska); i++) {
		if (isoper(polska[i]))
		{
			double a, b;
			b = numStack->pop();
			a = numStack->pop();
            numStack->push(operate(a, b, polska[i]));
		}
		else {
			switch (polska[i]) {
			case 'a':
				numStack->push(a);
				break;
			case 'b':
				numStack->push(b);
				break;
			case 'c':
				numStack->push(c);
				break;
			case 'd':
				numStack->push(d);
				break;
			default:
				numStack->push(e);
				break;
			}
        }
	}

	Form1->ansEdit->Text = FloatToStrF(numStack->pop(), ffFixed, 6, 5);
	delete numStack;
}

void __fastcall TForm1::ExecButtonClick(TObject *Sender) {
	AnsiString formula;
	Stack<char> *scopeChecker;

	double a, b, c, d, e;

	try {
		formula = "(" + FormulaInput->Text.Trim() + ")#";

		for (int i = 1; i < formula.Length(); i++) {
			if (formula[i] != 'a' && formula[i] != 'b' && formula[i]
				!= 'c' && formula[i] != 'd' && formula[i] != 'e' && formula[i]
				!= '+' && formula[i] != '-' && formula[i] != '*' && formula[i]
				!= '/' && formula[i] != '(' && formula[i] != ')' && formula
				[i] != '^')
				throw -1;
		}
		scopeChecker = new Stack<char>();
		for (int i = 1; i < formula.Length(); i++) {
			if (formula[i] == '(')
				scopeChecker->push('(');
			if (formula[i] == ')')
				scopeChecker->pop();
		}
		if (!scopeChecker->isEmpty())
			throw -1;

		a = StrToFloat(aInput->Text);
		b = StrToFloat(bInput->Text);
		c = StrToFloat(cInput->Text);
		d = StrToFloat(dInput->Text);
		e = StrToFloat(eInput->Text);
	}
	catch (EConvertError &e) {
		ShowMessage("������� �������� ���������� ���������.");
		delete scopeChecker;
		return;
	}
	catch (...) {
		ShowMessage("����������� ������ �������.");
		delete scopeChecker;
		return;
	}


	// ������� � �������� �������� ������
	char polska[1024] = {'\0'};
	RPN(formula, polska);

	// ��� ������
	calc(polska, a, b, c, d, e);
}
// ---------------------------------------------------------------------------
//**********************DONE**************************************************
