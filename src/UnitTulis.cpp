//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitTulis.h"
#include "UnitDialog.h"
#include "UnitGenetik.h"
#include <math.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

#define Tulis FormMain->RichEditHasil->Lines->Add
#define TabelData FormMain->StringGridData
#define VariabelBebas FormDialog->ListBoxVariabelBebas->Items
//---------------------------------------------------------------------------

void TulisHeaderReport(int Populasi)
{
/****************************************************************************
  Rutin untuk Menulis Header pada Report
****************************************************************************/

TDateTime Sekarang;
Sekarang = Now();

FormMain->RichEditHasil->SelectAll();
FormMain->RichEditHasil->Clear();
if (Populasi > 1) {
	Tulis("NON LINEAR REGRESSION");
	Tulis("PARAMETER ESTIMATION WITH GENETIC ALGORITHM METHOD");
	Tulis("CREATED BY YOHAN NAFTALI");
}
else {
	Tulis("LINEAR REGRESSION");
	Tulis("CREATED BY YOHAN NAFTALI");
}
Tulis("");
Tulis(FormMain->EditTitle->Text);

/* Catat Jam Mulai Proses */
Tulis("DATE         : " + Sekarang.DateString());
Tulis("TIME STARTED : " + Sekarang.TimeString());
Tulis("");   
~Sekarang;
}
//---------------------------------------------------------------------------

void TulisVariabel
  (
  int JumlahVariabel,
  int JumlahObservasi
  )
{
/****************************************************************************
  Rutin untuk Menulis Data Variabel
****************************************************************************/

Tulis("I.   VARIABLES");
Tulis("     A. Dependent Variable : " +
	FormDialog->ComboBoxVariabelTakBebas->Text);
Tulis("     B. Independent Variables :");
for (int i = 0; i < JumlahVariabel-1; i++) {
	Tulis("        " + IntToStr(i+1) + ". "
		+ VariabelBebas->operator [](i));
}
Tulis("     C. No. of Variables    : " + IntToStr(JumlahVariabel));
Tulis("     D. No. of Observations : " + IntToStr(JumlahObservasi));
}
//---------------------------------------------------------------------------

void TulisOptimasi(
  int Populasi,
  int TotalGenerasi,
  int Generasi,
  long double *BestFitness,
  long double *AvgFitness,
  long double *WorstFitness,
  bool IntegerOnly)
{
/****************************************************************************
  Rutin untuk Menulis Laporan Optimasi
****************************************************************************/

if (Populasi > 1) {
	long double Selisih;
	String TulisGen;
	Tulis("");
	Tulis("II.  OPTIMIZATION PARAMETER");
	Tulis("     A. Method                   : Genetic Algorithm");
	Tulis("     B. No. of Population        : " + IntToStr(Populasi));
	Tulis("     C. Generation Upper Limit   : " + IntToStr(TotalGenerasi));
	Tulis("     D. Selection Method         : Roulette Wheel Selection");
	Tulis("     E. Cross Over Method        : Arithmetic Operator");
    Tulis("        1. Probability Function  : Linear");
	Tulis("        2. Begin                 : "
		+ FormDialog->EditStartProbXO->Text);
	Tulis("        3. End                   : "
		+ FormDialog->EditEndProbXO->Text);
	Tulis("     F. Mutation Method          : Real Numbers Invers");
	Tulis("        1. Probability Function  : Linear");
	Tulis("        2. Begin                 : "
		+ FormDialog->EditStartProbMutasi->Text);
	Tulis("        3. End                   : "
		+ FormDialog->EditEndProbMutasi->Text);
	Tulis("     G. Search Space of Coefficient C");
	Tulis("        1. Lower Limit  : " + FormDialog->EditRuangBawah->Text);
	Tulis("        2. Upper Limit  : " + FormDialog->EditRuangAtas->Text);
	if (IntegerOnly) {
		Tulis("        3. Integer Only : Yes");
	}
	else {
		Tulis("        3. Integer Only : No");
	}

	Tulis (
		"     H. Convergence at Generation : " + IntToStr(Generasi)
	);
	String TulisBest    = FloatToStrF(BestFitness[0], ffFixed, 8, 5);
	String TulisWorst   = FloatToStrF(WorstFitness[0], ffFixed, 8, 5);
	String TulisAvg     = FloatToStrF(AvgFitness[0], ffFixed, 8, 5);
	Selisih             = BestFitness[0]-WorstFitness[0];
	String TulisSelisih = FloatToStrF(Selisih, ffFixed, 8, 5);
	Tulis("     I. First Generation");
	Tulis("        1. Best Fitness  : " + TulisBest);
	Tulis("        2. Worst Fitness : " + TulisWorst);
	Tulis("        3. Average       : " + TulisAvg);
	Tulis("        4. Convergence   : " + TulisSelisih);
	TulisBest    = FloatToStrF(BestFitness[Generasi-1], ffFixed, 8, 5);
	TulisWorst   = FloatToStrF(WorstFitness[Generasi-1], ffFixed, 8, 5);
	TulisAvg     = FloatToStrF(AvgFitness[Generasi-1], ffFixed, 8, 5);
    Selisih      = BestFitness[Generasi-1]-WorstFitness[Generasi-1];
	TulisSelisih = FloatToStrF(Selisih, ffFixed, 8, 5);
	Tulis("     J. Last Generation");
	Tulis("        1. Best Fitness  : " + TulisBest);
	Tulis("        2. Worst Fitness : " + TulisWorst);
	Tulis("        3. Average       : " + TulisAvg);
	Tulis("        4. Convergence   : " + TulisSelisih);
	FormMain->SeriesBestFitness->Clear();
	FormMain->SeriesAvgFitness->Clear();
	FormMain->SeriesWorstFitness->Clear(); 
	FormMain->StringGridOptimasi->RowCount = Generasi + 1;
	for (int i = 0; i < Generasi; i++) {
		Selisih = BestFitness[i] - WorstFitness[i];

		FormMain->StringGridOptimasi->Cells[0][i+1] = IntToStr(i+1);
		FormMain->StringGridOptimasi->Cells[1][i+1] = FloatToStrF(
			WorstFitness[i], ffFixed, 8, 5
		);
		FormMain->StringGridOptimasi->Cells[2][i+1] = FloatToStrF(
			AvgFitness[i], ffFixed, 8, 5
		);
		FormMain->StringGridOptimasi->Cells[3][i+1] = FloatToStrF(
			BestFitness[i], ffFixed, 8, 5
		);
                FormMain->StringGridOptimasi->Cells[4][i+1] = FloatToStrF(
			Selisih, ffFixed, 8, 5
		);
		FormMain->SeriesBestFitness->Add((float)BestFitness[i]);
		FormMain->SeriesAvgFitness->Add((float)AvgFitness[i]);
		FormMain->SeriesWorstFitness->Add((float)WorstFitness[i]);
	}
}
}
//---------------------------------------------------------------------------

void TulisHasil(int Populasi)
{
/****************************************************************************
  Rutin untuk Menulis Hasil
****************************************************************************/

String SpasiKosong    = "                      ";
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;

Tulis("");
if (Populasi > 1) {
	Tulis("III. OPTIMIZATION RESULT");
}
else {
	Tulis("II.  REGRESSION RESULT");
}

Tulis("     A. Coefficient Table and t Test : ");
Tulis("        1. Null Hypothesis : Coefficient = 0 (partial test)");
Tulis("        2. Alternative Hypothesis : Coefficient not 0 (partial test)");
Tulis(Separator);
Tulis(SpasiKosong +
	"Coefficient C    Coefficient B    Standard Error  t         Sig.");
Tulis(Separator);
}
//---------------------------------------------------------------------------

void TulisTabelKoefisien(
  int	      JumlahVariabel,
  int 	      *IndeksX,
  long double *KoefisienB,
  long double *KoefisienC,
  long double *SB,
  long double *TO,
  long double *PROBT)
{
/****************************************************************************
  Rutin untuk Menulis Data pada Tabel Koefisien
****************************************************************************/

for (int Baris = 0; Baris < JumlahVariabel; Baris++) {
	int    Len1;
	int    Add1;
	String TulisB;
	String TulisSB;
	String TulisTO;
	if (fabsl(KoefisienB[Baris]) >= 0.00001 &&
		fabsl(KoefisienB[Baris]) <= 99999999) {
		TulisB = FloatToStrF(KoefisienB[Baris], ffFixed, 18, 5);
	}
	else {
		TulisB = FloatToStrF(KoefisienB[Baris], ffExponent, 6, 5);
    }
	if (fabsl(SB[Baris]) >= 0.00001 &&
		fabsl(SB[Baris]) <= 99999999) {
		TulisSB = FloatToStrF(SB[Baris], ffFixed, 18, 5);
	}
	else {
		TulisSB = FloatToStrF(SB[Baris], ffExponent, 6, 5);
	}
	if (fabsl(TO[Baris]) >= 0.00001 &&
		fabsl(TO[Baris]) <= 99999999) {
		TulisTO = FloatToStrF(TO[Baris], ffFixed, 18, 5);
	}
	else {
		TulisTO = FloatToStrF(TO[Baris], ffExponent, 6, 5);
	}
	String TulisProbT = FloatToStrF(PROBT     [Baris], ffFixed, 8, 5);
	Len1 = TulisB.Length(); Add1 = 17-Len1;
	for (int k = 0; k < Add1; k++) {TulisB = TulisB + " ";}
	Len1 = TulisSB.Length(); Add1 = 16-Len1;
	for (int k = 0; k < Add1; k++) {TulisSB = TulisSB + " ";}
	Len1 = TulisTO.Length(); Add1 = 10-Len1;
	for (int k = 0; k < Add1; k++) {TulisTO = TulisTO + " ";}
	Len1 = TulisProbT.Length(); Add1 = 12-Len1;
	for (int k = 0; k < Add1; k++) {TulisProbT = TulisProbT + " ";}
	if (Baris == 0) {
		Tulis("        (constant)                     "+ TulisB+
		TulisSB+TulisTO+TulisProbT);
    }
	else {
		String TulisVAR   = TabelData->Cells[IndeksX[Baris-1]][0];
		String TulisC     = FloatToStrF(KoefisienC[Baris-1],ffFixed, 8, 5);
		Len1 = TulisVAR.Length(); Add1 = 14 - Len1;
		for (int k = 0; k < Add1; k++) {TulisVAR = TulisVAR + " ";}
			Len1 = TulisC.Length(); Add1 = 17 - Len1;
		for (int k = 0; k < Add1; k++) {TulisC = TulisC + " ";}
			Tulis("        "+TulisVAR+TulisC+TulisB+TulisSB+TulisTO+
				TulisProbT);
	}
}
}
//---------------------------------------------------------------------------

void TulisUjiNormalitas(
  long double Mean,
  long double Maksimum,
  long double Minimum,
  long double SDResid,
  long double Skewness,
  long double Kurtosis,
  long double JarqueBera,
  long double ProbJB)
{
/****************************************************************************
  Rutin untuk Menulis Hasil Uji Normalitas Residual
****************************************************************************/

String SpasiKosong    = "                      ";
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;
Tulis(Separator);
Tulis("     B. Normality Test of Residuals : ");
Tulis("        1. Mean           : "+FloatToStrF(Mean, ffFixed, 8, 5));
Tulis("        2. Maximum        : "+FloatToStrF(Maksimum, ffFixed, 8, 5));
Tulis("        3. Minimum        : "+FloatToStrF(Minimum, ffFixed, 8, 5));
Tulis("        4. Std. Deviation : "+FloatToStrF(SDResid, ffFixed, 8, 5));
if (Skewness == 0.) {
	Tulis("        5. Skewness       : "+FloatToStrF(Skewness, ffFixed, 8, 5)
		+ " (Symmetric)");
	}
else if (Skewness > 0.) {
	Tulis("        5. Skewness       : "
		+ FloatToStrF(Skewness, ffFixed, 8, 5)+" (Right Tail)");
}
else {
	Tulis("        5. Skewness       : "
		+FloatToStrF(Skewness, ffFixed, 8, 5)+" (Left Tail)");
}
if (Kurtosis == 3.) {
	Tulis("        6. Kurtosis       : "
		+FloatToStrF(Kurtosis, ffFixed, 8, 5)+" (Normal)");
}
else if (Kurtosis > 3.) {
	Tulis("        6. Kurtosis       : "
		+FloatToStrF(Kurtosis, ffFixed, 8, 5)
		+" (Leptokurtic)");
}
else {
	Tulis("        6. Kurtosis       : "
		+FloatToStrF(Kurtosis, ffFixed, 8, 5)
		+" (Platykurtic)");
}
Tulis("        7. Statistik Jarque-Berra ");
Tulis("           a. J-B            : "+
	FloatToStrF(JarqueBera, ffFixed, 15, 5));
Tulis("           b. Hypothesis     : Normal Distribution");
String TulisProbJB;
if ((ProbJB >= 0.00001 && ProbJB <= 99999999) || (ProbJB == 0.)) {
	TulisProbJB = FloatToStrF(ProbJB, ffFixed, 18, 5);
}
else {
	TulisProbJB = FloatToStrF(ProbJB, ffExponent, 5, 5);
}
Tulis("           c. Prob.          : " + TulisProbJB);

if (ProbJB < 0.01) {
Tulis("           d. Interpretation : Hypothesis rejected below 1%");
}
else {
	Tulis("           d. Interpretation : Hypothesis accpeted at "+
		FloatToStrF(ProbJB*100., ffFixed, 8, 3) + "%");
}
}
//---------------------------------------------------------------------------

void TulisHeaderTabelKolinieritas()
{
/****************************************************************************
  Rutin untuk Menulis Header Tabel Kolinieritas
****************************************************************************/

String SpasiKosong    = "                      ";
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;
Tulis("     C. Multicollinearity Test : ");
Tulis("        Assume Collinearity if VIF > 5 or tolerance value far from 1");
Tulis(Separator);
Tulis("        Variable      Tolerance           VIF");
Tulis(Separator);
}
//---------------------------------------------------------------------------

void TulisTabelKolinieritas
  (
  int Baris,
  int IndeksVariabelBebas,
  long double RSquareZi
  )
{ 
if (Baris != 0) {
	int    Len1;
	int    Add1;
	String TulisVAR   = TabelData->Cells[IndeksVariabelBebas][0];
	String TulisTOL   = FloatToStrF((1.-RSquareZi), ffFixed, 8, 5);
	String TulisVIF;
	if (RSquareZi != 1.) {
		TulisVIF   = FloatToStrF(1./(1.-RSquareZi), ffFixed, 8, 5);
	}
	else {
		TulisVIF = "Unlimited";
	}

	Len1 = TulisVAR.Length(); Add1 = 14 - Len1;
	for (int k = 0; k < Add1; k++) {TulisVAR = TulisVAR + " ";}
	Len1 = TulisTOL.Length(); Add1 = 20 - Len1;
	for (int k = 0; k < Add1; k++) {TulisTOL = TulisTOL + " ";}
	Tulis("        " + TulisVAR + TulisTOL + TulisVIF);
}
}
//---------------------------------------------------------------------------

void TulisHeaderUjiWhite()
{
/****************************************************************************
  Rutin untuk Menulis Header Uji White
****************************************************************************/

String SpasiKosong    = "                      ";
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;
Tulis(Separator);
Tulis("     D. Heteroscedasticity Test with White's General Heteroscedasticity Test (1980) : ");
}
//---------------------------------------------------------------------------

void TulisUjiWhite
  (
  long double RSQUAREWhite,
  long double JumlahObservasi,
  long double ProbWhite,
  long double SSReg,
  long double SSRes,
  long double SSTotal,
  long double MeanRegression,
  long double MeanResidual,
  long double FVALUE,
  long double PROBF
  )
{
Tulis("        1. Method                       : Pure White Heteroscedasticity Test");
Tulis("           a. Null Hypothesis           : Homoscedastics");
Tulis("           b. Alternative Hypothesis    : Heteroscedastics");
Tulis("        2. Analysis of Variance");
Tulis("           a. Sum of Square Regresssion : " +
	FloatToStr(SSReg));
Tulis("           b. Sum of Square Residual    : " +
	FloatToStr(SSRes));
Tulis("           c. Sum of Square Total       : " +
	FloatToStr(SSTotal));
Tulis("           d. Mean Regression           : " +
	FloatToStr(MeanRegression));
Tulis("           e. Mean Residual             : " +
	FloatToStr(MeanResidual));
Tulis("           f. F Value                   : " +
	FloatToStrF(FVALUE, ffFixed, 18, 5));
Tulis("           g. Probability F             : " +
	FloatToStrF(PROBF, ffFixed, 18, 5));
Tulis("        7. R²                           : " +
	FloatToStrF(RSQUAREWhite, ffFixed, 18,5));
Tulis("        8. R² x Observation             : " +
	FloatToStrF(RSQUAREWhite*JumlahObservasi, ffFixed, 18, 5));
Tulis("        9. Probability                  : " +
	FloatToStrF(1.-ProbWhite, ffFixed, 18, 5));
}
//---------------------------------------------------------------------------

void TulisHasilStatistik(
  long double StandardError,
  long double RSQUARE,
  long double ADJRSQUARE,
  long double DWStat,
  long double LogLike,
  long double AIC,
  long double SC)
{
/****************************************************************************
  Rutin untuk Menulis Hasil Regeresi
****************************************************************************/

Tulis("     F. Durbin-Watson Statistics     : " +
	FloatToStrF(DWStat, ffFixed, 8, 5));
if (RSQUARE >= 0.) {
	Tulis("     G. Regression Coefficient (R)   : " +
		FloatToStrF(sqrtl(RSQUARE), ffFixed, 8, 5));
}
else {
	Tulis("     G. Regression Coefficient (R)   : " +
		FloatToStrF(sqrtl(fabsl(RSQUARE)), ffFixed, 8, 5)+
		"i -> Check Model or Data" );
}
Tulis("     H. Det. Coefficient (R²)        : " +
FloatToStrF(RSQUARE, ffFixed, 8, 5));
Tulis("     I. Adjusted R²                  : " +
FloatToStrF(ADJRSQUARE, ffFixed, 8, 5));
Tulis("     J. Standard Error of Regression : " +
FloatToStrF(StandardError, ffFixed, 8, 5));
Tulis("     K. Log Likelihood               : " +
FloatToStrF(LogLike, ffFixed, 8, 5));
Tulis("     L. Akaike Information Criterion : " +
FloatToStrF(AIC, ffFixed, 8, 5));
Tulis("     M. Schwarz Criterion            : " +
FloatToStrF(SC, ffFixed, 8, 5));
}
//---------------------------------------------------------------------------

void TulisTabelAnova(
  int JumlahObservasi,
  int JumlahVariabel,
  long double SSReg,
  long double SSRes,
  long double SSTotal,
  long double MeanRegression,
  long double MeanResidual,
  long double FVALUE,
  long double PROBF)
{
/****************************************************************************
  Rutin untuk Menulis Data pada Tabel ANOVA
****************************************************************************/

int    Len1;
int    Add1;
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;
String Spasi20 = "                    ";
String TulisSSReg    = FloatToStrF(SSReg,ffFixed, 8, 5);
String TulisDOFReg   = IntToStr(JumlahVariabel - 1);
String TulisMReg     = FloatToStrF(MeanRegression,ffFixed, 8, 5);
String TulisFV       = FloatToStrF(FVALUE, ffFixed, 8, 5);
String TulisProbF    = FloatToStrF(PROBF, ffFixed, 8, 5);
String TulisSSRes    = FloatToStrF(SSRes,ffFixed, 8, 5);
String TulisDOFRes   = IntToStr(JumlahObservasi-JumlahVariabel);
String TulisMRes     = FloatToStrF(MeanResidual, ffFixed, 8, 5);
String TulisSSTotal  = FloatToStrF(SSTotal,ffFixed, 8, 5);
String TulisDOFTotal = IntToStr(JumlahObservasi-1);

Len1 = TulisSSReg.Length();
Add1 = 17 - Len1;
for (int k = 0; k < Add1; k++) {TulisSSReg = TulisSSReg + " ";}
Len1 = TulisDOFReg.Length();
Add1 = 8 - Len1;
for (int k = 0; k < Add1; k++) {TulisDOFReg = TulisDOFReg + " ";}
Len1 = TulisMReg.Length();
Add1 = 17 - Len1;
for (int k = 0; k < Add1; k++) {TulisMReg = TulisMReg + " ";}
Len1 = TulisFV.Length();
Add1 = 14 - Len1;
for (int k = 0; k < Add1; k++) {TulisFV = TulisFV + " ";}
Len1 = TulisSSRes.Length();
Add1 = 17 - Len1;
for (int k = 0; k < Add1; k++) {TulisSSRes = TulisSSRes + " ";}
Len1 = TulisDOFRes.Length();
Add1 = 8 - Len1;
for (int k = 0; k < Add1; k++) {TulisDOFRes = TulisDOFRes + " ";}
Len1 = TulisSSTotal.Length();
Add1 = 17 - Len1;
for (int k = 0; k < Add1; k++) {TulisSSTotal = TulisSSTotal + " ";}
Tulis("     N. Analysis of Variance (ANOVA) :");
Tulis(Separator);
Tulis(Spasi20 +
  "Sum of Square    DOF     Mean Square      F             Sig.");
Tulis(Separator);
Tulis("        Regression  " +
	TulisSSReg + TulisDOFReg + TulisMReg + TulisFV + TulisProbF);
Tulis("        Residual    " +
	TulisSSRes + TulisDOFRes + TulisMRes);
Tulis("        Total       " +
	TulisSSTotal + TulisDOFTotal);
Tulis(Separator);

	if (SSReg < 0.) {
		Tulis("        Negative Sum of Square Regression, Check Data");
	}
}
//---------------------------------------------------------------------------

void TulisPersamaan (
	int         JumlahVariabel,
	int         JumlahPopulasi,
	long double *KoefisienB,
	long double *KoefisienC)
{
/****************************************************************************
  Rutin untuk Menulis Persamaan
****************************************************************************/

String TulisDependent;
String *TulisIndependent = new String[JumlahVariabel];
String *TulisPersamaan   = new String[JumlahVariabel];

/* Simpan string dependent */
TulisDependent = FormDialog->ComboBoxVariabelTakBebas->Text;

for (int i = 0; i < JumlahVariabel; i++) {
	String B;
	if (fabsl(KoefisienB[i]) >= 0.00001 &&
		fabsl(KoefisienB[i]) <= 99999999) {
		B = FloatToStrF(fabsl(KoefisienB[i]), ffFixed, 18, 5);
	}
	else {
		B = FloatToStrF(fabsl(KoefisienB[i]), ffExponent, 6, 5);
	}
	/* Simpan string konstanta */
	if (i == 0) {
		if (KoefisienB[i] < 0) {
			TulisIndependent[i] = "-" + B;
		}
		else {
			TulisIndependent[i] = B;
		}
	}
	/* Simpan string variabel */
	else {
		String X = VariabelBebas->operator [](i-1);
		if (JumlahPopulasi == 1) {
			String TempString;
			if (KoefisienB[i] < 0) {
				TempString = " - " + B + "." + X;
			}
			else {
				TempString = " + " + B + "." + X;
			}
			TulisIndependent[i] = TempString;
		}
		else {
			String C = FloatToStrF(KoefisienC[i-1],ffFixed, 8, 5);
			String TempString;
			if (KoefisienB[i] < 0) {
				TempString = " - " + B + "." + X + "^" + C;
			}
			else {
				TempString = " + " + B + "." + X + "^" + C;
			}
			TulisIndependent[i] = TempString;
		}
	}
}

/* Tulis hasil persamaan */
Tulis("     O. Equation :");
int BarisPersamaan = 0;
TulisPersamaan[0] =  "        " + TulisDependent + " = ";
for (int i = 0; i < JumlahVariabel; i++) {
	String TempString;
	TempString = TulisPersamaan[BarisPersamaan] + TulisIndependent[i];
	if (TempString.Length() > 90) {
		BarisPersamaan ++;
		TulisPersamaan[BarisPersamaan] = "       " + TulisIndependent[i];
	}
	else {
		TulisPersamaan[BarisPersamaan] = TempString;
	}
}
for (int i = 0; i <= BarisPersamaan; i++) {
	Tulis(TulisPersamaan[i]);
}
delete [] TulisPersamaan;
delete [] TulisIndependent;
}
//---------------------------------------------------------------------------

void TulisTabelResidual (
	int JumlahObservasi,
	long double *VariabelY,
	long double *Residual,
  	long double *Ramalan)
{
/****************************************************************************
  Rutin untuk Menulis Tabel Residual
****************************************************************************/

FormMain->StringGridResidual->RowCount = JumlahObservasi + 1;
for (int obs = 0; obs < JumlahObservasi; obs++) {
	FormMain->StringGridResidual->Cells[0][obs+1] = IntToStr(obs+1);
	FormMain->StringGridResidual->Cells[1][obs+1] = FloatToStrF(
		VariabelY[obs], ffFixed, 8, 5);
	FormMain->StringGridResidual->Cells[2][obs+1] = FloatToStrF(
		Ramalan[obs], ffFixed, 8, 5);
	FormMain->StringGridResidual->Cells[3][obs+1] = FloatToStrF(
		Residual[obs], ffFixed, 8, 5);
	FormMain->StringGridResidual->Cells[4][obs+1] = FloatToStrF(
		Residual[obs]*Residual[obs], ffFixed, 8, 5);
}
}
//---------------------------------------------------------------------------

void TulisKoefisienCBest(int JumlahVariabel, long double* KoefisienCBest)
{
String NamaFile = FormMain->LabelFileTerbuka->Caption;
String Dummy = "";
int Panjang = NamaFile.Length();
for (int i = 0; i < Panjang-4; i++)
	Dummy = Dummy+NamaFile.c_str()[i] ;
NamaFile = Dummy;
NamaFile = NamaFile + ".hsl";
FormMain->MemoSave->Clear();
for (int i = 0; i < JumlahVariabel-1; i++)
	FormMain->MemoSave->Lines->Add(FloatToStr(KoefisienCBest[i]));
FormMain->MemoSave->Lines->SaveToFile(NamaFile);
FormMain->MemoSave->Clear();
}
//---------------------------------------------------------------------------

void TulisFooterReport()
{
/****************************************************************************
  Rutin untuk Menulis Footer pada Report
****************************************************************************/  
TDateTime Sekarang;
Sekarang = Now();
Tulis("");
Tulis("TIME FINISHED  : " + Sekarang.TimeString());
}
//---------------------------------------------------------------------------

void TulisQStat(
	int PeriodeTest,
	long double* AutoCorr,
	long double* QStat,
	long double* ProbQ)
{
String SeparatorKiri  = "        -------------------------------------";
String SeparatorKanan = "---------------------------------------------";
String Separator = SeparatorKiri + SeparatorKanan;
Tulis("     E. Autocorrelation Test with Q Statistics");
Tulis("        Null Hypothesis : No Autocorrelation");
Tulis(Separator);
Tulis("        Lag     Auto Correlation   Q Statistics       Prob.");
Tulis(Separator);
for (int k = 1; k <= PeriodeTest; k++) {
	String TulisLag = IntToStr(k);
	int Len1 = TulisLag.Length();
	int Add1 = 8 - Len1;
	for (int i = 0; i < Add1; i++) {
		TulisLag = TulisLag + " ";
	}
	String TulisAC = FloatToStrF(AutoCorr[k], ffFixed, 8, 3);
	Len1 = TulisAC.Length();
	Add1 = 19 - Len1;
	for (int i = 0; i < Add1; i++) {
		TulisAC = TulisAC + " ";
	}
	String TulisQ = FloatToStrF(QStat[k], ffFixed, 8, 4);
	Len1 = TulisQ.Length();
	Add1 = 19 - Len1;
	for (int i = 0; i < Add1; i++) {
		TulisQ = TulisQ + " ";
	}
	String TulisProbQ = FloatToStrF(ProbQ[k], ffFixed, 8, 4);
	Len1 = TulisProbQ.Length();
	Add1 = 19 - Len1;
	for (int i = 0; i < Add1; i++) {
		TulisProbQ = TulisProbQ + " ";
	}
	Tulis ("        " + TulisLag + TulisAC + TulisQ + TulisProbQ);
}
Tulis(Separator);
}
//---------------------------------------------------------------------------

