//---------------------------------------------------------------------------

#ifndef UnitDialogH
#define UnitDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormDialog : public TForm
{
__published:	// IDE-managed Components
	TButton *ButtonPolyOptimasi;
	TButton *ButtonCancelPolyOptimasi;
	TPanel *PanelProgress;
	TLabel *LabelStatus;
	TProgressBar *ProgressBarTotal;
	TPanel *PanelEquation;
	TLabel *LabelEquation;
	TLabel *LabelModelPolynomial;
	TPanel *PanelVariable;
	TLabel *LabelDepVar;
	TLabel *LabelIndepVar;
	TLabel *LabelVar;
	TComboBox *ComboBoxVariabelTakBebas;
	TListBox *ListBoxVariabelBebas;
	TListBox *ListBoxVariabel;
	TBitBtn *BitBtnTambah;
	TBitBtn *BitBtnKurang;
	TPanel *PanelParameter;
	TGroupBox *GroupBox3;
	TLabel *LabelJumlahPopulasi;
	TLabel *LabelJumlahGenerasi;
	TEdit *EditJumlahPopulasi;
	TEdit *EditJumlahGenerasi;
	TGroupBox *GroupBox1;
	TLabel *LabelRVD;
	TLabel *Label6;
	TEdit *EditRuangAtas;
	TEdit *EditRuangBawah;
	TGroupBox *GroupBox2;
	TLabel *LabelMutasi1;
	TLabel *LabelMutasi2;
	TEdit *EditStartProbMutasi;
	TEdit *EditEndProbMutasi;
	TCheckBox *CheckBoxBest;
	TCheckBox *CheckBoxInteger;
	TGroupBox *GroupBox4;
	TLabel *LabelEndProbXO;
	TLabel *LabelStartProbXO;
	TEdit *EditStartProbXO;
	TEdit *EditEndProbXO;
	void __fastcall ButtonCancelPolyOptimasiClick(TObject *Sender);
	void __fastcall ButtonPolyOptimasiClick(TObject *Sender);
	void __fastcall BitBtnKurangClick(TObject *Sender);
	void __fastcall BitBtnTambahClick(TObject *Sender);
	void __fastcall ListBoxVariabelBebasClick(TObject *Sender);
	void __fastcall ListBoxVariabelClick(TObject *Sender);
	void __fastcall ComboBoxVariabelTakBebasChange(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	int __fastcall HitungJumlahObservasi();
	int __fastcall CariIndeksY();
	void __fastcall CariIndeksX(int *IndeksX);
	void __fastcall AmbilVariabelTakBebas(long double *VariabelY,
		int JumlahObservasi);
	void __fastcall AmbilVariabelBebas(long double (*VariabelX)[1000],
		int JumlahVariabel, int JumlahObservasi, int *IndeksX);

public:		// User declarations
	__fastcall TFormDialog(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormDialog *FormDialog;
//---------------------------------------------------------------------------
#endif
