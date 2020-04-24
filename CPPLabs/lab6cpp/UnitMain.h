//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *SG;
	TLabel *LabelInfo;
	TTreeView *TV;
	TLabel *Label1;
	TEdit *FIOEdit;
	TEdit *PassNumEdit;
	TLabel *Label2;
	TLabel *Label3;
	TButton *AddButton;
	TEdit *KeyEdit;
	TLabel *Label4;
	TButton *DelButton;
	TButton *ReflectButton;
	TLabel *ReflectLabel;
	TButton *PreorderButton;
	TMemo *Memo;
	TButton *PostorderButton;
	TButton *CenteredButton;
	TButton *ExitButton;
	TButton *LSButton;
	TLabel *LSLabel;
	void __fastcall PreorderButtonClick(TObject *Sender);
	void __fastcall PostorderButtonClick(TObject *Sender);
	void __fastcall CenteredButtonClick(TObject *Sender);
	void __fastcall AddButtonClick(TObject *Sender);
	void __fastcall DelButtonClick(TObject *Sender);
	void __fastcall ReflectButtonClick(TObject *Sender);
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall LSButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
