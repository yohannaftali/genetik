//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitDialog.h"
#include "UnitGenetik.h"   // Header unit genetik
#include "UnitAlgoritma.h" // Header unit algoritma
#include "UnitTulis.h"     // Header unit tulis
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma resource "*.dfm"

#define TabelData FormMain->StringGridData
#define VariabelBebas FormDialog->ListBoxVariabelBebas->Items

TFormDialog *FormDialog;
//---------------------------------------------------------------------------

__fastcall TFormDialog::TFormDialog(TComponent* Owner):TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::ButtonCancelPolyOptimasiClick(TObject *Sender)
{
FormMain->Visible = true;
Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::ButtonPolyOptimasiClick(TObject *Sender)
{
// Get Data
int JumlahGenerasi  = StrToInt(EditJumlahGenerasi->Text);
int JumlahPopulasi  = StrToInt(EditJumlahPopulasi->Text);
int JumlahVariabel  = ListBoxVariabelBebas->Count+1;
int JumlahObservasi = HitungJumlahObservasi();
long double BatasAtas  = StrToFloat(FormDialog->EditRuangAtas->Text);
long double BatasBawah = StrToFloat(FormDialog->EditRuangBawah->Text);
long double XOAwal = StrToFloat(FormDialog->EditStartProbXO->Text);
long double XOAkhir = StrToFloat(FormDialog->EditEndProbXO->Text);
long double MutasiAwal = StrToFloat(FormDialog->EditStartProbMutasi->Text);
long double MutasiAkhir = StrToFloat(FormDialog->EditEndProbMutasi->Text);
bool PakaiOptimasiSebelum = FormDialog->CheckBoxBest->Checked;
bool IntegerOnly = FormDialog->CheckBoxInteger->Checked;
// Check Data
if (JumlahObservasi - JumlahVariabel < 1) {
	ShowMessage("Error, Check Data!");
	return;
}

// Get Dependent Variable's Data
long double *VariabelY;
VariabelY = new long double [JumlahObservasi];
AmbilVariabelTakBebas(VariabelY, JumlahObservasi);

// Get Independent Variables' Data
int (*IndeksX) = new int [JumlahVariabel];
long double (*VariabelX)[MaxObservasi];
VariabelX = new long double [JumlahVariabel][MaxObservasi];
AmbilVariabelBebas (
	VariabelX,
	JumlahVariabel,
	JumlahObservasi,
	IndeksX
);

// Write Header and Variable Data
TulisHeaderReport(JumlahPopulasi);
TulisVariabel(JumlahVariabel, JumlahObservasi);

// Variable Declaration
long double *KoefisienCBest;
KoefisienCBest = new long double [JumlahVariabel-1];
long double *AvgFitness   = new long double [JumlahGenerasi];
long double *BestFitness  = new long double [JumlahGenerasi];
long double *WorstFitness = new long double [JumlahGenerasi];
int Generasi = 0;

FormDialog->ProgressBarTotal->Max = JumlahGenerasi;
FormDialog->ProgressBarTotal->Position = 0;

// Optimization with Genetics Algorithms
AlgoritmaGenetik (
	JumlahGenerasi,
	JumlahPopulasi,
	JumlahVariabel,
	JumlahObservasi,
	VariabelY ,
	VariabelX,
	IndeksX,
	BatasAtas,
	BatasBawah,
	XOAwal,
	XOAkhir,
	MutasiAwal,
	MutasiAkhir,
	PakaiOptimasiSebelum,
	KoefisienCBest,
	Generasi,
	AvgFitness,
	BestFitness,
	WorstFitness,
	IntegerOnly
);

// Write Optimization History
TulisOptimasi (
	JumlahPopulasi,
	JumlahGenerasi,
	Generasi,
	BestFitness,
	AvgFitness,
	WorstFitness,
	IntegerOnly
);

delete [] BestFitness;
BestFitness = 0;
delete [] AvgFitness;
AvgFitness = 0;
delete [] WorstFitness;
WorstFitness = 0;

// Perform Statistical Test
long double *Residual = new long double [JumlahObservasi];
long double *RamalanBest = new long double [JumlahObservasi];
long double *KoefisienB = new long double [JumlahVariabel];
long double SSReg;
long double SSRes;
long double SSTotal;
long double MeanRegression;
long double MeanResidual;
long double FVALUE;
long double PROBF;
long double StandardError;
long double RSQUARE;
long double ADJRSQUARE;
long double DWStat;
long double LogLike;
long double AIC;
long double SC;
int PeriodeTest;
long double* AutoCorr = new long double [JumlahObservasi];
long double* QStat = new long double [JumlahObservasi];
long double* ProbQ = new long double [JumlahObservasi];
long double RSQUAREWhite;
long double ProbWhite;
long double SSRegWhite;
long double SSResWhite;
long double SSTotalWhite;
long double MeanRegressionWhite;
long double MeanResidualWhite;
long double FVALUEWhite;
long double PROBFWhite;

Statistik (
	JumlahPopulasi,
	JumlahVariabel,
	JumlahObservasi,
	VariabelY ,
	VariabelX,
	IndeksX,
	KoefisienB,
	KoefisienCBest,
	Residual,
	RamalanBest,
	SSReg,
	SSRes,
	SSTotal,
	MeanRegression,
	MeanResidual,
	FVALUE,
	PROBF,
	StandardError,
	RSQUARE,
	ADJRSQUARE,
	DWStat,
	LogLike,
	AIC,
	SC,
	PeriodeTest,
	AutoCorr,
	QStat,
	ProbQ,
	RSQUAREWhite,
	ProbWhite,
	SSRegWhite,
	SSResWhite,
	SSTotalWhite,
	MeanRegressionWhite,
	MeanResidualWhite,
	FVALUEWhite,
	PROBFWhite);

// Write Heteroschedasticity Test
TulisUjiWhite(
	RSQUAREWhite,
	JumlahObservasi,
	ProbWhite,
	SSRegWhite,
	SSResWhite,
	SSTotalWhite,
	MeanRegressionWhite,
	MeanResidualWhite,
	FVALUEWhite,
	PROBFWhite);

// Write Autocorrelation Test with Q Stat
TulisQStat(
	PeriodeTest,
	AutoCorr,
	QStat,
	ProbQ);

// Write Statistics
TulisHasilStatistik (
	StandardError,
	RSQUARE,
	ADJRSQUARE,
	DWStat,
	LogLike,
	AIC,
	SC);

// Write ANOVA Table
TulisTabelAnova (
	JumlahObservasi,
	JumlahVariabel,
	SSReg,
	SSRes,
	SSTotal,
	MeanRegression,
	MeanResidual,
	FVALUE,
	PROBF);

// Write Equation
TulisPersamaan(JumlahVariabel, JumlahPopulasi, KoefisienB, KoefisienCBest);
TulisTabelResidual(JumlahObservasi, VariabelY, Residual, RamalanBest);
TulisKoefisienCBest(JumlahVariabel, KoefisienCBest);

delete [] Residual;
Residual = 0;
delete [] RamalanBest;
RamalanBest = 0;
delete [] VariabelX;
VariabelX = 0;
delete [] VariabelY;
VariabelY = 0;
delete [] IndeksX;
IndeksX = 0;
delete [] KoefisienB;
KoefisienB = 0;
delete [] KoefisienCBest;
KoefisienCBest = 0;

// Write Footer
TulisFooterReport();

// Show Report
FormMain->Visible = true;
FormMain->PageControlGenetik->ActivePage = FormMain->TabSheetHasil;

MessageBeep(2);
Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::BitBtnKurangClick(TObject *Sender)
{
ListBoxVariabelBebas->CopySelection(ListBoxVariabel);
ListBoxVariabelBebas->CopySelection(ComboBoxVariabelTakBebas);
ListBoxVariabelBebas->DeleteSelected();
ListBoxVariabelBebas->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::BitBtnTambahClick(TObject *Sender)
{
String VarY;

ListBoxVariabel->CopySelection(ListBoxVariabelBebas);
ListBoxVariabel->DeleteSelected();
VarY = ComboBoxVariabelTakBebas->Text;
ComboBoxVariabelTakBebas->Items->Clear();
ComboBoxVariabelTakBebas->Items->Add(VarY);
for (int i = 0; i < StrToInt(ListBoxVariabel->Items->Count); i++) {
	ComboBoxVariabelTakBebas->Items->Add(
		ListBoxVariabel->Items->operator [](i));
}
ListBoxVariabelBebas->Update();
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::ListBoxVariabelBebasClick(TObject *Sender)
{
ListBoxVariabel->ClearSelection();
BitBtnKurang->Visible = true;
BitBtnTambah->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::ListBoxVariabelClick(TObject *Sender)
{
ListBoxVariabelBebas->ClearSelection();
BitBtnKurang->Visible = false;
BitBtnTambah->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::ComboBoxVariabelTakBebasChange(TObject *Sender)
{
ListBoxVariabel->Clear();
String VarPilihan;
VarPilihan = ComboBoxVariabelTakBebas->Text;
int nDepVariable = StrToInt(ComboBoxVariabelTakBebas->Items->Count);
for (int i = 0; i < nDepVariable; i++) {
	String Var = ComboBoxVariabelTakBebas->Items->operator [](i);
	if (Var != VarPilihan) {
		ListBoxVariabel->Items->Add(Var);
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::FormClose(TObject *Sender, TCloseAction &Action)
{
FormMain->Visible = true;
}
//---------------------------------------------------------------------------

int __fastcall TFormDialog::HitungJumlahObservasi()
{
int IndeksY = CariIndeksY();
int JumlahObservasi;
for (int obs = 0; obs < TabelData->RowCount; obs++) {
	if (TabelData->Cells[IndeksY][obs+1] == "") {
		JumlahObservasi = obs;
		break;
	}
}
return JumlahObservasi;
}
//---------------------------------------------------------------------------

int __fastcall TFormDialog::CariIndeksY()
{
int Indeks;
int TotalVariabel = StrToInt(FormMain->EditJumlahVariabel->Text);
String VarTakBebas = ComboBoxVariabelTakBebas->Text;

for (int var = 0; var < TotalVariabel; var++) {
	if (TabelData->Cells[var+1][0] == VarTakBebas) {
		Indeks = var+1;
		break;
	}
}
return Indeks;
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::AmbilVariabelTakBebas (
	long double *VariabelY, int JumlahObservasi
)
{
int IndeksY = CariIndeksY();
for (int obs = 0; obs < JumlahObservasi; obs++) {
	VariabelY[obs] = StrToFloat(
		TabelData->Cells[IndeksY][obs+1]);
}
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::AmbilVariabelBebas
  (
  long double (*VariabelX)[MaxObservasi],
  int         JumlahVariabel,
  int         JumlahObservasi,
  int         *IndeksX
  )
{
int TotalVariabel = StrToInt(FormMain->EditJumlahVariabel->Text);

CariIndeksX(IndeksX);

for (int obs = 0; obs < JumlahObservasi; obs++) {
	VariabelX[0][obs] = 1.;
}
for (int var = 0; var < JumlahVariabel-1; var++) {
	for (int col = 1; col < TotalVariabel+1; col++) {
		if (IndeksX[var] == col) {
			for (int obs = 0; obs < JumlahObservasi;
				obs++) {
				VariabelX[var+1][obs] = StrToFloat(
					TabelData->Cells[col][obs+1]);
			}
			col = TotalVariabel+1;
		}
	}
}
}
//---------------------------------------------------------------------------

void __fastcall TFormDialog::CariIndeksX(int *IndeksX)
{
int TotalVariabel  = StrToInt(FormMain->EditJumlahVariabel->Text);
int JumlahVariabel = FormDialog->ListBoxVariabelBebas->Count+1;

for (int i = 0; i < JumlahVariabel-1; i++) {
	String VarBebas = VariabelBebas->operator [](i);
	for (int j = 0; j < TotalVariabel; j++) {
		String NamaTabel = TabelData->Cells[j+1][0];
		if (NamaTabel == VarBebas) {
			IndeksX[i] = j+1;
			j = TotalVariabel;
		}
	}
}
}
//---------------------------------------------------------------------------







