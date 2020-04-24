//---------------------------------------------------------------------------

#ifndef UnitMainH
#define UnitMainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox;
	TLabel *Label1;
	TLabel *CandidateChoiceLabel;
	TLabel *FNLabel;
	TLabel *SpecLabel;
	TComboBox *FirmsComboBox;
	TButton *ShowCandidatesButton;
	TButton *AddNewCandidateButton;
	TButton *SortByNameButton;
	TButton *DeleteCandidateButton;
	TButton *SaveCandidatesButton;
	TButton *LoadCandidatesButton;
	TButton *ExitButton;
	TButton *CreateNewCandidateListButton;
	TComboBox *CandidateChoiceComboBox;
	TButton *PickFirmListButton;
	TButton *ScarceVacButton;
	TButton *ScarceFirmsButton;
	TEdit *FNEdit;
	TEdit *SpecEdit;
	TComboBox *PositionComboBox;
	TLabel *DOBLabel;
	TLabel *MinRateLabel;
	TEdit *DOBEdit;
	TEdit *MinRateEdit;
	TCheckBox *HighEdCheckBox;
	void __fastcall ShowCandidatesButtonClick(TObject *Sender);
	void __fastcall AddNewCandidateButtonClick(TObject *Sender);
	void __fastcall SortByNameButtonClick(TObject *Sender);
	void __fastcall PickFirmListButtonClick(TObject *Sender);
	void __fastcall CandidateChoiceComboBoxChange(TObject *Sender);
	void __fastcall ScarceVacButtonClick(TObject *Sender);
	void __fastcall ScarceFirmsButtonClick(TObject *Sender);
	void __fastcall DeleteCandidateButtonClick(TObject *Sender);
	void __fastcall SaveCandidatesButtonClick(TObject *Sender);
	void __fastcall LoadCandidatesButtonClick(TObject *Sender);
	void __fastcall CreateNewCandidateListButtonClick(TObject *Sender);
	void __fastcall ExitButtonClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
