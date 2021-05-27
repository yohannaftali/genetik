//---------------------------------------------------------------------------

#pragma hdrstop                                                 

#include "UnitAlgoritma.h"
#include "UnitProbabilitas.h"
#include "UnitGenetik.h"      // Header unit genetik
#include "UnitDialog.h"       // Header unit kotak dialog
#include "UnitTulis.h"        // Header unit tulis
#include <math.h>             // Header fungsi matematika
#include <fstream.h>          // Header untuk streaming file
//---------------------------------------------------------------------------

#pragma package(smart_init)
#pragma argsused
//---------------------------------------------------------------------------

#define Tulis FormMain->RichEditHasil->Lines->Add      
//---------------------------------------------------------------------------

void AlgoritmaGenetik(
	int JumlahGenerasi,
	int JumlahPopulasi,
	int JumlahVariabel,
	int JumlahObservasi,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	int *IndeksX,
	long double BatasAtas,
	long double BatasBawah,
	long double XOAwal,
	long double XOAkhir,
	long double MutasiAwal,
	long double MutasiAkhir,
	bool PakaiOptimasiSebelum,
	long double *KoefisienCBest,
	int &Generasi,
	long double *AvgFitness,
	long double *BestFitness,
	long double *WorstFitness,
	bool IntegerOnly
	)
{
long double (*KoefisienC)[MaxVariabel-1];
KoefisienC = new long double [JumlahPopulasi][MaxVariabel-1];
long double Konvergensi = 1.;

PopulasiAwal(
	JumlahPopulasi,
	JumlahVariabel,
	BatasAtas,
	BatasBawah,
	KoefisienC,
	PakaiOptimasiSebelum,
	IntegerOnly);

for (Generasi = 0; Generasi < JumlahGenerasi; Generasi++) {
	FormDialog->Refresh();
	long double *Fitness;
	Fitness = new long double [JumlahPopulasi];
	HitungFitness(
		JumlahPopulasi,
		JumlahObservasi,
		JumlahVariabel,
		VariabelY,
		VariabelX,
		KoefisienC,
		Fitness);
	HitungKonvergensi(
		Generasi,
		JumlahPopulasi,
		Fitness,
		BestFitness,
		AvgFitness,
		WorstFitness,
		Konvergensi);
	bool isConvergence = (Konvergensi < 1.0e-5) ||
		(Generasi == JumlahGenerasi-1) ;
	if (isConvergence) {
		delete [] Fitness;
		Fitness = 0;
		break;
	}
	Seleksi(
		JumlahPopulasi,
		JumlahVariabel,
		Fitness,
		KoefisienC);
	delete [] Fitness;
	Fitness = 0;
	Rekombinasi(
		JumlahPopulasi,
		JumlahVariabel,
		Generasi,
		JumlahGenerasi,
		BatasAtas,
		BatasBawah,
		KoefisienC,
		XOAwal,
		XOAkhir,
		MutasiAwal,
		MutasiAkhir,
		IntegerOnly);
	FormDialog->ProgressBarTotal->Position ++;
}
Generasi++;
for (int i=0; i < JumlahVariabel-1; i++) {
	KoefisienCBest[i] = KoefisienC[0][i];
}
delete [] KoefisienC;
KoefisienC = 0;
}
//---------------------------------------------------------------------------

void Statistik (
	int JumlahPopulasi,
	int JumlahVariabel,
	int JumlahObservasi,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	int *IndeksX,
	long double *KoefisienB,
	long double *KoefisienCBest,
	long double *Residual,
	long double *RamalanBest,
	long double& SSReg,
	long double& SSRes,
	long double& SSTotal,
	long double& MeanRegression,
	long double& MeanResidual,
	long double& FVALUE,
	long double& PROBF,
	long double& StandardError,
	long double& RSQUARE,
	long double& ADJRSQUARE,
	long double& DWStat,
	long double& LogLike,
	long double& AIC,
	long double& SC,
	int& PeriodeTest,
	long double* AutoCorr,
	long double* QStat,
	long double* ProbQ,
	long double& RSQUAREWhite,
	long double& ProbWhite,
	long double& SSRegWhite,
	long double& SSResWhite,
	long double& SSTotalWhite,
	long double& MeanRegressionWhite,
	long double& MeanResidualWhite,
	long double& FVALUEWhite,
	long double& PROBFWhite)
{
long double *ElemenDJJ  = new long double [JumlahVariabel];
long double *Residual2  = new long double [JumlahObservasi];
long double *SB = new long double[JumlahVariabel];
long double *TO = new long double[JumlahVariabel];
long double *PROBT = new long double[JumlahVariabel];

RegresiBest (
	JumlahVariabel,
	JumlahObservasi,
	VariabelY,
	VariabelX,
	KoefisienB,
	KoefisienCBest,
	ElemenDJJ,
	Residual,
	Residual2,
	RamalanBest,
	DWStat);

SSRes = HitungSSRes(JumlahObservasi, Residual2);
StandardError = sqrtl(SSRes / (JumlahObservasi - JumlahVariabel));

for (int i = 0; i < JumlahVariabel; i++) {
	if (ElemenDJJ[i] >= 0.) {
		SB[i] = StandardError*sqrtl(ElemenDJJ[i]);
	}
	else {
		SB[i] = StandardError*sqrtl(fabsl(ElemenDJJ[i]));
		Tulis ("Error: Check Data");
		return;
	}
	TO[i] = KoefisienB[i]/SB[i];
	PROBT[i] = ProbT(TO[i], JumlahObservasi, JumlahVariabel);
}
delete [] ElemenDJJ;
ElemenDJJ = 0;

TulisHasil(JumlahPopulasi);
TulisTabelKoefisien(
	JumlahVariabel,
	IndeksX,
	KoefisienB,
	KoefisienCBest,
	SB,
	TO,
	PROBT
);
delete [] SB;
SB = 0;
delete [] TO;
TO = 0;
delete [] PROBT;
PROBT = 0;

// Test Normality Assumption
long double SumResid = 0.;
long double MakResid = Residual[0];
long double MinResid = Residual[0];
for (int i = 0; i < JumlahObservasi; i++) {
	SumResid = SumResid + Residual[i];
	if (Residual[i] > MakResid) {
		MakResid = Residual[i];
	}
	if (Residual[i] < MinResid) {
		MinResid = Residual[i];
	}
}
long double AvgResid = SumResid/JumlahObservasi;
long double SDResid = 0.;
for (int i = 0; i < JumlahObservasi; i++) {
	long double Selisih = Residual[i]-AvgResid;
	SDResid = SDResid + (Selisih*Selisih);
}
SDResid = SDResid/(JumlahObservasi-1.);
SDResid = sqrtl(SDResid);
long double SigmaTopi;
long double Skewness = 0.;
long double Kurtosis = 0.;
SigmaTopi = SDResid*sqrtl((JumlahObservasi-1.)/JumlahObservasi);
for (int i = 0; i < JumlahObservasi; i++) {
	long double Selisih = Residual[i]-AvgResid;
	long double HasilBagi = Selisih/SigmaTopi;
	Skewness = Skewness + (HasilBagi*HasilBagi*HasilBagi);
	Kurtosis = Kurtosis + (HasilBagi*HasilBagi*HasilBagi*HasilBagi);
}
Skewness = Skewness/JumlahObservasi;
Kurtosis = Kurtosis/JumlahObservasi;
long double JarqueBera;
JarqueBera = JumlahObservasi/6.;
JarqueBera = JarqueBera*(powl(Skewness,2.)+(powl(Kurtosis-3.,2.)/4.));
long double ProbJB = gammq(1., JarqueBera/2.); // 2 dof
TulisUjiNormalitas(
	AvgResid,
	MakResid,
	MinResid,
	SDResid,
	Skewness,
	Kurtosis,
	JarqueBera,
	ProbJB);

// Test Multicolinearity Assumption
Multikolinieritas(
	JumlahVariabel,
	JumlahObservasi,
	KoefisienCBest,
	VariabelX,
	IndeksX);

// Test Heteroschedasticity with White Test (no cross terms)
White(
	JumlahVariabel,
	JumlahObservasi,
	Residual2,
	KoefisienCBest,
	VariabelX,
	RSQUAREWhite,
	ProbWhite,
	SSRegWhite,
	SSResWhite,
	SSTotalWhite,
	MeanRegressionWhite,
	MeanResidualWhite,
	FVALUEWhite,
	PROBFWhite);

// Calculate Log Likelihood
LogLike = (-JumlahObservasi/2.)*(1.+ logl(2.*3.1415926535897932385)+
logl(SSRes/JumlahObservasi));

// Calculate Akaike Information Criterion
AIC = (-2. * LogLike / JumlahObservasi)+(2. * JumlahVariabel /
	JumlahObservasi);
SC = (-2 * LogLike / JumlahObservasi)+
	(JumlahVariabel * logl(JumlahObservasi) / JumlahObservasi);

// Autocorrelation Test
QStatTest(
	JumlahObservasi,
	Residual,
	AIC,
	SC,
	PeriodeTest,
	AutoCorr,
	QStat,
	ProbQ);

// F-Test
FTest(
	JumlahObservasi,
	JumlahVariabel,
	VariabelY,
	SSRes,
	SSReg,
	SSTotal,
	MeanRegression,
	MeanResidual,
	FVALUE,
	PROBF,
	RSQUARE,
	ADJRSQUARE);

delete [] Residual2;
Residual2 = 0;
}
//---------------------------------------------------------------------------

void QStatTest(
	int JumlahObservasi,
	long double* Residual,
	long double AIC,
	long double SC,
	int& PeriodeTest,
	long double* AutoCorr,
	long double* QStat,
	long double* ProbQ)
{
// Test Autocorrelation with Q Statistics
if (AIC*AIC < SC*SC) {
	PeriodeTest = (ceil(fabsl(AIC)));
}
else {
	PeriodeTest = (ceil(fabsl(SC)));
}
if ((PeriodeTest == 0) || (PeriodeTest > JumlahObservasi)) {
	PeriodeTest = JumlahObservasi/4;
}

for (int k = 1; k <= PeriodeTest; k++) {
	long double SumAtas = 0.;
	for (int t = k+1; t <= JumlahObservasi; t++) {
		SumAtas = SumAtas+(Residual[t-1]*Residual[t-1-k]);
	}
	long double SumBawah = 0.;
	for (int t = 1; t <= JumlahObservasi; t++) {
		SumBawah = SumBawah+(Residual[t-1]*Residual[t-1]);
	}
	AutoCorr[k] = SumAtas/SumBawah;
	long double SumQ = 0.;
	for (int j = 1; j <= k ; j++) {
		SumQ = SumQ+(AutoCorr[j]*AutoCorr[j]/(JumlahObservasi-j));
	}
	QStat[k] = ((JumlahObservasi)*(JumlahObservasi+2.))*SumQ;
	ProbQ[k] = 1.-gammp(k, QStat[k]);
}
}

void FTest(
	int JumlahObservasi,
	int JumlahVariabel,
	long double *VariabelY,
	long double SSRes,
	long double& SSReg,  
	long double& SSTotal,
	long double& MeanRegression,
	long double& MeanResidual,
	long double& FVALUE,
	long double& PROBF,
	long double& RSQUARE,
	long double& ADJRSQUARE)
{
SSTotal = HitungSSTotal(JumlahObservasi, VariabelY);;
SSReg = SSTotal - SSRes;

// F-Test
MeanRegression = SSReg / (JumlahVariabel - 1.);;
MeanResidual = SSRes / (JumlahObservasi - JumlahVariabel);;
FVALUE = MeanRegression/MeanResidual;
if (FVALUE >= 0.) {
	PROBF = ProbF(FVALUE, JumlahObservasi, JumlahVariabel);
}
else {
	PROBF = 1.;
}

// Calculate R square and Adjusted R square
RSQUARE = SSReg/SSTotal;
long double DOF = JumlahObservasi-JumlahVariabel;
ADJRSQUARE = 1.-((1.-RSQUARE)*((JumlahObservasi-1.)/DOF));
}

long double HitungSSTotal(int JumlahObservasi, long double *VariabelY)
{
long double SSTotal = 0.;
long double RataY = 0.;

for (int i = 0; i < JumlahObservasi; i++) {
	RataY = RataY + VariabelY[i];
}
RataY = RataY/JumlahObservasi;
for (int i = 0; i < JumlahObservasi; i++) {
	long double SelisihRata = VariabelY[i]-RataY;
	SSTotal = SSTotal + (SelisihRata * SelisihRata);
}
return SSTotal;
}
//---------------------------------------------------------------------------

long double HitungSSRes(int JumlahObservasi, long double *Residual2)
{
// Calculate Sum of Squared Residual
long double SSRes = 0.;
for (int obs = 0; obs < JumlahObservasi; obs++) {
	SSRes = SSRes+Residual2[obs];
}
return SSRes;
}
//---------------------------------------------------------------------------

long double ProbF(long double FHitung, int Observasi, int Variabel)
{
int V1;
int V2;
long double a;
long double b;
long double x;
long double Sig;

V1  = Variabel-1;
V2  = Observasi-Variabel;
a   = V2/2.;
b   = V1/2.;
x   = V2/(V2+(V1*FHitung));
Sig = betai(a, b, x);

return Sig;
}
//---------------------------------------------------------------------------

long double ProbT(long double tHitung, int Observasi, int Variabel)
{
int DOF;
long double a;
long double b;
long double x;
long double Sig;

DOF = Observasi-Variabel;
a = DOF/2.;
b = 0.5;
x = DOF/(DOF+(tHitung*tHitung));
Sig = betai(a, b, x);

return Sig;
}
//---------------------------------------------------------------------------

void BubbleSort(
	int JumlahPopulasi,
	int JumlahVariabel,
	long double *Fitness,
	long double (*KoefisienC)[MaxVariabel-1]
)
{
/****************************************************************************
  Rutin untuk Mengurutkan Koefisien C berdasarkan Nilai Fitnessnya dengan
  Metode Bubble Sort
****************************************************************************/

for (int i = 1; i < JumlahPopulasi; i++) {
	for (int j = JumlahPopulasi-1; j >= i; j--) {
		if(Fitness[j] > Fitness[j-1]) {
			long double Dummy;
			Dummy = Fitness[j];
			Fitness[j] = Fitness[j-1];
			Fitness[j-1] = Dummy;
			for (int k = 0; k < JumlahVariabel-1; k++) {
				Dummy = KoefisienC[j][k];
				KoefisienC[j][k] = KoefisienC[j-1][k];
				KoefisienC[j-1][k] = Dummy;
			}
		}
	}
}
}
//---------------------------------------------------------------------------

void HitungFitness(
	int JumlahPopulasi,
	int JumlahObservasi,
	int JumlahVariabel,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	long double (*KoefisienC)[MaxVariabel-1],
	long double *Fitness)
{
// Calculate Fitness
for (int pop = 0; pop < JumlahPopulasi; pop++) {
	HitungFitnessIndividu(
		JumlahObservasi,
		JumlahVariabel,
		VariabelY,
		VariabelX,
		KoefisienC[pop],
		Fitness[pop]);
}

// Sort Population based on Fitness
BubbleSort(
	JumlahPopulasi,
	JumlahVariabel,
	Fitness,
	KoefisienC);
}
//---------------------------------------------------------------------------

void HitungFitnessIndividu(
	int JumlahObservasi,
	int JumlahVariabel,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	long double *KoefisienC,
	long double &Fitness)
{
long double (*MatriksInvers)[MaxVariabel];
MatriksInvers = new long double [JumlahVariabel][MaxVariabel];
long double (*MatriksZ)[MaxObservasi];
MatriksZ = new long double [JumlahVariabel][MaxObservasi];
long double *KoefisienB;
KoefisienB = new long double [JumlahVariabel];
long double *Residual2 = new long double [JumlahObservasi];

// Transform Variable X to Variable Z
// [Z] = [X^C]
Transformasi(
	MatriksZ,
	VariabelX,
	KoefisienC,
	JumlahVariabel,
	JumlahObservasi);

// Calculate Invers of Matriks Z'Z
// [(Z'Z)^(-1)] = ([Z]'[Z])^(-1)
bool isSolveablilty = 1;
SolusiInvers(
	MatriksZ,
	JumlahVariabel,
	JumlahObservasi,
	MatriksInvers,
	isSolveablilty);

if (isSolveablilty) {
	HitungKoefisienB(
		KoefisienB,
		MatriksZ,
		VariabelY,
		MatriksInvers,
		JumlahVariabel,
		JumlahObservasi);

	// Calculate Residual
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		long double Yhat = 0.;
		long double ErrorT;
		for (int var = 0; var < JumlahVariabel; var++) {
			if (var == 0) {
				Yhat = Yhat + KoefisienB[var];
			}
			else {
				Yhat = Yhat+(MatriksZ[var][obs]
					* KoefisienB[var]);
			}
		}
		ErrorT = VariabelY[obs] - Yhat;
		Residual2[obs] = ErrorT * ErrorT;
	}
	long double SSRes = HitungSSRes(JumlahObservasi, Residual2);

	// Calculate Fitness
	if (SSRes != 0) {
		Fitness = 1./sqrtl(SSRes);
	}
	else {
		Fitness = 0.;
	}
}
else {
	// If no Solution Found, Set Fitness to 0
	Fitness = 0.;
}
delete [] MatriksZ;
MatriksZ = 0;
delete [] MatriksInvers;
MatriksInvers = 0;
delete [] KoefisienB;
KoefisienB = 0;
delete [] Residual2;
Residual2 = 0;
}
//---------------------------------------------------------------------------

void HitungKoefisienB (
	long double *KoefisienB,
	long double (*MatriksZ)[MaxObservasi],
	long double *VariabelY,
	long double (*MatriksInvers)[MaxVariabel],
	int JumlahVariabel,
	int JumlahObservasi)
{
// Build Matrix [Z'Y]
// [Z'Y] = [Z]'[Y]
long double *MatriksZTY = new long double [JumlahVariabel];
for (int var = 0; var < JumlahVariabel; var++) {
	MatriksZTY[var] = 0.;
}
for (int var = 0; var < JumlahVariabel; var++) {
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		MatriksZTY[var] = MatriksZTY[var] +
			(MatriksZ[var][obs]*VariabelY[obs]);
	}
}

// Calculate Matrix B
// [B] = [(Z'Z)^(-1)][Z'Y]
for (int var = 0; var < JumlahVariabel; var++) {
	KoefisienB[var] = 0.;
}
for (int var = 0; var < JumlahVariabel; var++) {
	for (int kolom = 0; kolom < JumlahVariabel; kolom++) {
		KoefisienB[var] = KoefisienB[var] +
			(MatriksInvers[kolom][var] * MatriksZTY[kolom]);
	}
}
delete [] MatriksZTY;
MatriksZTY = 0;
}
//---------------------------------------------------------------------------

void HitungKonvergensi(
	int Generasi,
	int JumlahPopulasi,
	long double *Fitness,
	long double *BestFitness,
	long double *AvgFitness,
	long double *WorstFitness,
	long double &Konvergensi)
{
long double JumlahFitness = 0.;

for (int pop = 0; pop < JumlahPopulasi; pop++) {
	JumlahFitness = JumlahFitness+Fitness[pop];
}
BestFitness[Generasi]  = Fitness[0];
AvgFitness[Generasi]   = JumlahFitness/JumlahPopulasi;
WorstFitness[Generasi] = Fitness[JumlahPopulasi-1];

Konvergensi = Fitness[0]-Fitness[JumlahPopulasi-1];
}
//---------------------------------------------------------------------------

void Multikolinieritas(
	int JumlahVariabel,
	int JumlahObservasi,
	long double *KoefisienC,
	long double (*VariabelX)[MaxObservasi],
	int *IndeksX)
{ 
TulisHeaderTabelKolinieritas();
for (int i = 1; i < JumlahVariabel; i++) {
	/*...........................................................
	Hitung derajat toleransi variabel bebas (TOL) dan VIF dengan
	cara menghitung koefisien determinasi regresi persamaan :
	Zi = B0 + B1.Z1 + ... + BN.Zn
	Zi adalah Variabel Bebas yang ditetapkan menjadi variabel
	tak bebas pada iterasi ke-i
	i adalah nomor iterasi sejumlah variabel bebas
	n adalah nomor variabel bebas terakhir sejumlah jumlah
	variabel bebas pada persamaan dikurangi 1 (n = i - 1)
	...........................................................*/
	long double (*MatriksZ)[MaxObservasi];
	MatriksZ = new long double [JumlahVariabel-1][MaxObservasi];
	long double (*VariabelZi);
	VariabelZi = new long double[JumlahObservasi];

	// Build Variable Zi
	for (int j = 0; j < JumlahObservasi; j++) {
		if (VariabelX[i][j] == 0.) {
			VariabelZi[j] = 0.;
		}
		else if (VariabelX[i][j] == 1.) {
			VariabelZi[j] = 1.;
		}
		else {
			VariabelZi[j] = powl(VariabelX[i][j],
				KoefisienC[i-1]);
		}
		MatriksZ[0][j] = 1.;
	}

	// Build Matrix Z
	int n = 0;
	for (int j = 0; j < JumlahVariabel-1; j++) {
		if (j != i - 1) {
			for (int k = 0; k < JumlahObservasi;
				k++) {
				if (VariabelX[j+1][k] == 0.) {
					MatriksZ[n+1][k] = 0.;
				}
				else if (VariabelX[j+1][k] == 1.) {
					MatriksZ[n+1][k] = 1.;
				}
				else {
					MatriksZ[n+1][k] =
						powl(VariabelX[j+1]
						[k], KoefisienC[j]);
				}
			}
			n ++;
		}
	}
	long double (*MatriksInvers)[MaxVariabel];
	MatriksInvers = new long double [JumlahVariabel-1][MaxVariabel];
	bool isSolveablilty = true;
	SolusiInvers(
		MatriksZ,
		JumlahVariabel-1, // Jumlah variabel dikurangi 1
		JumlahObservasi,
		MatriksInvers,
		isSolveablilty);
	if (isSolveablilty) {
		long double (*KoefisienB);
		KoefisienB = new long double [JumlahVariabel-1];
		HitungKoefisienB (
			KoefisienB,
			MatriksZ,
			VariabelZi,
			MatriksInvers,
			JumlahVariabel-1, // Jumlah variabel dikurangi 1
			JumlahObservasi
		);

		long double *Residual2;
		Residual2 = new long double [JumlahObservasi];
		for (int obs = 0; obs < JumlahObservasi; obs++) {
			long double Ramalan = 0.;
			long double ErrorT;
			for (int var = 0; var < JumlahVariabel-1; var++) {
				if (var == 0) {
					Ramalan = Ramalan +
						KoefisienB[var];
				}
				else {
					Ramalan = Ramalan +
						(MatriksZ[var][obs] *
						KoefisienB[var]);
				}
			}
			ErrorT = VariabelZi[obs]-Ramalan;
			Residual2[obs] = ErrorT*ErrorT;
		}

		long double SSRes;
		long double SSReg;
		long double SSTotal;
		long double RSQUARE;
		SSRes = HitungSSRes(JumlahObservasi, Residual2);
		SSTotal = HitungSSTotal(JumlahObservasi, VariabelZi);
		SSReg = SSTotal - SSRes;
		RSQUARE = SSReg / SSTotal;

		delete [] KoefisienB;
		KoefisienB = 0;
		delete [] Residual2;
		Residual2 = 0;

		TulisTabelKolinieritas(
			i,
			IndeksX[i-1],
			RSQUARE);
	}
	else {
		Tulis("        Error: Collinearity Test");
	}

	delete [] MatriksInvers;
	MatriksInvers = 0;
	delete [] MatriksZ;
	MatriksZ = 0;
	delete [] VariabelZi;
	VariabelZi = 0;
}
}
//---------------------------------------------------------------------------

void Mutasi(
	int JumlahVariabel,
	long double *Kromosom,
	long double BatasAtas,
	long double BatasBawah,
	bool IntegerOnly)
{
long double Range = BatasAtas-BatasBawah;
long double OperatorMutasi = Range/2.;
for (int var = 0; var < JumlahVariabel-1; var++) {
	if(OperatorMutasi+Kromosom[var]>BatasAtas){
		Kromosom[var] =  Kromosom[var]-OperatorMutasi;
	}
	else {
	Kromosom[var] =  Kromosom[var]+OperatorMutasi;
    }   
	if (IntegerOnly) {
		if (Kromosom[var]>0) {
			Kromosom[var]=(long)(Kromosom[var]+0.5);
		}
		else {
			Kromosom[var]=(long)(Kromosom[var]-0.5);
		}
	}
	PeriksaBatas(Kromosom[var], BatasAtas, BatasBawah);
}
}
//---------------------------------------------------------------------------

void PeriksaBatas(
	long double &Kromosom,
	long double BatasAtas,
	long double BatasBawah)
{
if (Kromosom > BatasAtas) {
	Kromosom = BatasAtas;
}
else if (Kromosom < BatasBawah) {
	Kromosom = BatasBawah;
}
}
//---------------------------------------------------------------------------

void PopulasiAwal (
	int JumlahPopulasi,
	int JumlahVariabel,
	long double BatasAtas,
	long double BatasBawah,
	long double (*Kromosom)[MaxVariabel-1],
	bool PakaiOptimasiSebelum,
	bool IntegerOnly)
{
randomize();
for (int pop = 0; pop < JumlahPopulasi; pop++) {
	if (pop == 1 && PakaiOptimasiSebelum) {
		// Membaca hasil optimasi terbaik sebelumnya
		// Hasil optimasi terbaik dijadikan individu ke-2
		char   CharBaca[128];
		String NamaFile = FormMain->LabelFileTerbuka->Caption;
		String Dummy    = "";
		String StringKromosom;
		int Panjang = NamaFile.Length();
		for (int i = 0; i < Panjang-4; i++)
			Dummy = Dummy+NamaFile.c_str()[i] ;

		NamaFile = Dummy;
		NamaFile = NamaFile + ".hsl";
		ifstream baca(NamaFile.c_str());
		for (int i = 0; i < JumlahVariabel-1; i++) {
			baca >> CharBaca;
			StringKromosom = CharBaca;
			

			Kromosom[pop][i] = StrToFloat(StringKromosom);

			if (IntegerOnly) {
				if (Kromosom[pop][i]>0) {
					Kromosom[pop][i]=(long)(Kromosom[pop][i]+0.5);
				}
				else {
					Kromosom[pop][i]=(long)(Kromosom[pop][i]-0.5);
				}
			}
		}
	}
	else {
    	// Random populasi awal
		for (int var = 0; var < JumlahVariabel-1; var++) {
			if (pop == 0) {
            	// Individu pertama digunakan linear regression
				Kromosom[pop][var] = 1.;
				PeriksaBatas(Kromosom[pop][var],
				BatasAtas, BatasBawah);
			}
			else {
				if (IntegerOnly) {
					Kromosom[pop][var] = random(BatasAtas-BatasBawah)
						+BatasBawah;
				}
				else {
					Kromosom[pop][var] =
					(random((int)((BatasAtas -
					BatasBawah) * 100.)) / 100.)
					+ BatasBawah;
				}
				PeriksaBatas(Kromosom[pop][var],
					BatasAtas, BatasBawah);
			}
		}
	}
}
}
//---------------------------------------------------------------------------

void RegresiBest(
	int JumlahVariabel,
	int JumlahObservasi,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	long double *KoefisienB,
	long double *KoefisienC,
	long double *ElemenDJJ,
	long double *Residual,
	long double *Residual2,
	long double *RamalanBest,
	long double &DWStat)
{
// Transform Variabel X into Variabel Z
// [Z] = [X^C]
long double (*MatriksZ)[MaxObservasi];
MatriksZ = new long double [JumlahVariabel][MaxObservasi];
Transformasi(
	MatriksZ,
	VariabelX,
	KoefisienC,
	JumlahVariabel,
	JumlahObservasi);

// Calculate Invers of Matriks Z'Z
// [(Z'Z)^(-1)] = ([Z]'[Z])^(-1)
long double (*MatriksInvers)[MaxVariabel];
MatriksInvers = new long double [JumlahVariabel][MaxVariabel];
bool isSolveablilty = true;
SolusiInvers(
	MatriksZ,
	JumlahVariabel,
	JumlahObservasi,
	MatriksInvers,
	isSolveablilty);
if (isSolveablilty) {
	HitungKoefisienB(
		KoefisienB,
		MatriksZ,
		VariabelY,
		MatriksInvers,
		JumlahVariabel,
		JumlahObservasi);

	// Calculate Residual
	long double ErrorT1 = 0.; // e(t-1)
	long double SelisihError = 0.; // Sum((e(t)-e(t-1))^2)
	long double MinResidual;
	long double MaxResidual;
	FormMain->SeriesResidual->Clear();
	FormMain->SeriesHistogram->Clear();
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		RamalanBest[obs] = 0.;
		long double ErrorT;
		for (int var = 0; var < JumlahVariabel; var++) {
			if (var == 0) {
			RamalanBest[obs] = RamalanBest[obs] +
				KoefisienB[var];
			}
			else {
				RamalanBest[obs] = RamalanBest[obs] +
				(MatriksZ[var][obs] *
				KoefisienB[var]);
			}
		}
		ErrorT = VariabelY[obs]-RamalanBest[obs];
		Residual[obs]  = ErrorT;
		Residual2[obs] = ErrorT*ErrorT;
		FormMain->SeriesResidual->Add((float)ErrorT);
		if (obs == 0) {
			MinResidual = ErrorT;
			MaxResidual = ErrorT;
		}
		else {
			if (ErrorT < MinResidual) {
				MinResidual = ErrorT;
			}
			if (ErrorT > MaxResidual) {
				MaxResidual = ErrorT;
			}
		}
		if (obs !=0) {
			SelisihError = SelisihError +
				powl((ErrorT-ErrorT1),2);
		}
		ErrorT1 = ErrorT;
	}
	long double Range = MaxResidual-MinResidual;
	long double Interval = Range/31.;
	long double Hist[31];
	int Frek[31];
	for (int i = 0; i < 31; i++) {
		Hist[i] = MinResidual+(Interval*i)+(Interval/2.);
		Frek[i] = 0;
		long double Lower, Upper;
		Lower = MinResidual+(Interval*i);
		Upper = Lower+Interval;
		for (int obs = 0; obs < JumlahObservasi; obs++) {
			if (Residual[obs] >= Lower &&
				Residual[obs] < Upper) {
				Frek[i] = Frek[i]+1;
			}
			if (i == 30) {
				if (Residual[obs] >= Upper) {
					Frek[i] = Frek[i]+1;
				}
			}
		}
		FormMain->SeriesHistogram->AddXY((float)Hist[i],
			Frek[i]);
	}
	long double SSRes = HitungSSRes(JumlahObservasi, Residual2);
	DWStat = SelisihError/SSRes; // Statistik Durbin-Watson
		for (int var = 0; var < JumlahVariabel; var++) {
		ElemenDJJ[var] = MatriksInvers[var][var];
	}
}
delete [] MatriksZ;
MatriksZ = 0;
delete [] MatriksInvers;
MatriksInvers = 0;
}
//---------------------------------------------------------------------------

void Rekombinasi(
	int JumlahPopulasi,
	int JumlahVariabel,
	int Generasi,
	int JumlahGenerasi,
	long double BatasAtas,
	long double BatasBawah,
	long double (*KoefisienC)[MaxVariabel-1],
	long double XOAwal,
	long double XOAkhir,
	long double MutasiAwal,
	long double MutasiAkhir,
	bool IntegerOnly)
{
/****************************************************************************
  Rutin untuk Melakukan Rekombinasi Individu
****************************************************************************/

/*---------------------------------------------------------------------------
  Rekombinasi Individu dengan Kawin Silang
---------------------------------------------------------------------------*/
int XO;
long double ProbXO;
ProbXO = (XOAwal - ((XOAwal-XOAkhir) *
	((Generasi + 1.) / JumlahGenerasi)))*100.;

int *StatusKawin = new int [JumlahPopulasi];
int Ayah = 0;
int Ibu;
int NoPerkawinan  = 0;

for (int i = 0; i < JumlahPopulasi; i++) {
	StatusKawin[i] = 0;
}

while (NoPerkawinan < JumlahPopulasi/2) {
	if (StatusKawin[Ayah] == 0) {
		NoPerkawinan++;
		StatusKawin[Ayah] = 1;
		Ibu = random(JumlahPopulasi);
		while (StatusKawin[Ibu] == 1) {
			if (Ibu < JumlahPopulasi-1) {
				Ibu = Ibu+1;
			}
			else {
				Ibu = Ayah+1;
			}
		}
		StatusKawin[Ibu] = 1;
		XO = random (100);
		if (XO <= ProbXO) {
			// Cross Over dengan Operator Aritmatika
			// Range Lambda 0 - 1.25, disebut juga rekombinasi
			// menengah
			long double Lambda = random(125)/100.;

			for (int k = 0; k < JumlahVariabel-1; k++) {
				long double CAyah = KoefisienC[Ayah][k];
				long double CIbu  = KoefisienC[Ibu][k];
				if (Ayah != 0) {
					// Ayah bukan individu terbaik

					// Formula untuk Anak Pertama
					KoefisienC[Ayah][k] = (CAyah*Lambda)
						+ (CIbu * (1.-Lambda));
					if (IntegerOnly) {
						if (KoefisienC[Ayah][k]>0) {
							KoefisienC[Ayah][k]=(long)(KoefisienC[Ayah][k]+0.5);
						}
						else {
							KoefisienC[Ayah][k]=(long)(KoefisienC[Ayah][k]-0.5);
						}
					}
					PeriksaBatas(KoefisienC[Ayah][k], BatasAtas,
						BatasBawah);

					// Formula untuk Anak Kedua
					KoefisienC[Ibu][k] = (CIbu*Lambda)+
						(CAyah * (1.-Lambda));
					if (IntegerOnly) {
						if (KoefisienC[Ibu][k]>0) {
							KoefisienC[Ibu][k]=(long)(KoefisienC[Ibu][k]+0.5);
						}
						else {
							KoefisienC[Ibu][k]=(long)(KoefisienC[Ibu][k]-0.5);
						}
					}
					PeriksaBatas(KoefisienC[Ibu][k],
						BatasAtas, BatasBawah);
				}
				else {
					// Ayah merupakan individu terbaik, gen ayah tidak
					// berubah
					KoefisienC[Ibu][k]  = (CIbu*Lambda)
						+ (CAyah * (1.-Lambda));
					if (IntegerOnly) {
						if (KoefisienC[Ibu][k]>0) {
							KoefisienC[Ibu][k]=(long)(KoefisienC[Ibu][k]+0.5);
						}
						else {
							KoefisienC[Ibu][k]=(long)(KoefisienC[Ibu][k]-0.5);
						}
					}
					PeriksaBatas(KoefisienC[Ibu][k], BatasAtas, BatasBawah);
				}
			}
		}
	}
	Ayah++;
}
delete [] StatusKawin;
StatusKawin = 0;

/*---------------------------------------------------------------------------
  Rekombinasi individu dengan mutasi
---------------------------------------------------------------------------*/
int mutasi;
long double ProbMutasi;
ProbMutasi = (MutasiAwal-((MutasiAwal-MutasiAkhir) *
	((Generasi+1.)/JumlahGenerasi)))*100.;

for (int i = 1; i < JumlahPopulasi; i++) {
	mutasi = random (100);
	if (mutasi <= ProbMutasi) {
		Mutasi(
			JumlahVariabel,
			KoefisienC[i],
			BatasAtas,
			BatasBawah,
			IntegerOnly);
	}
}
}
//---------------------------------------------------------------------------

void Seleksi(
	int JumlahPopulasi,
	int JumlahVariabel,
	long double *Fitness,
	long double (*KoefisienC)[MaxVariabel-1])
{
/****************************************************************************
  Rutin untuk Seleksi Individu dengan Metode Roulette Wheel
****************************************************************************/
long double (*TempKoefisienC)[MaxVariabel-1];
TempKoefisienC = new long double [JumlahPopulasi][MaxVariabel-1];
for (int i = 0; i < JumlahPopulasi; i++) {
	for (int j = 0; j < JumlahVariabel-1; j++) {
		TempKoefisienC[i][j] = KoefisienC[i][j];
	}
}

long double JumlahFitness = 0.;
for (int i = 0; i < JumlahPopulasi; i++) {
	JumlahFitness = JumlahFitness + Fitness[i];
}
long double *Share = new long double [JumlahPopulasi];
for (int i = 0; i < JumlahPopulasi; i++) {
	Share[i] = Fitness[i]/JumlahFitness;
	if (i != 0) {
		Share[i] = Share[i]+Share[i-1];
	}
}
for (int i = 0; i < JumlahPopulasi; i++) {
	long double Roulette = random(100) / 100.;
	for (int j = 0; j < JumlahPopulasi; j++) {
		// Pilih individu ke-j
		if (Roulette <= Share[j]) {
			for (int k = 0; k < JumlahVariabel-1; k++) {
				KoefisienC[i][k] =
					TempKoefisienC[j][k];
			}
			j = JumlahPopulasi-1;
		}
	}
}

// Preserve Individu Terbaik
for (int i = 0; i < JumlahVariabel-1; i++) {
	KoefisienC[0][i] = TempKoefisienC[0][i];
}
delete Share;
Share = 0;
delete [] TempKoefisienC;
TempKoefisienC = 0;
}
//---------------------------------------------------------------------------

void SolusiInvers(
	long double (*MatriksZ)[MaxObservasi],
	int JumlahVariabel,
	int JumlahObservasi,
	long double (*MatriksInvers)[MaxVariabel],
	bool& isSolveablilty)
{
/****************************************************************************
  Rutin untuk menghitung invers dari matriks Z
****************************************************************************/

/*---------------------------------------------------------------------------
  Bentuk Matriks Z'Z
	[Z'Z] = [Z]'.[Z]
---------------------------------------------------------------------------*/
long double (*MatriksZTZ) [MaxVariabel];
MatriksZTZ = new long double [JumlahVariabel][MaxVariabel];
for (int kolom = 0; kolom < JumlahVariabel; kolom++) {
	for (int baris = 0; baris < JumlahVariabel; baris++) {
		MatriksZTZ[kolom][baris] = 0.;
	}
}
for (int kolom = 0; kolom < JumlahVariabel; kolom++) {
	for (int baris = 0; baris < JumlahVariabel; baris++) {
		for (int obs = 0; obs < JumlahObservasi; obs++) {
			MatriksZTZ[kolom][baris] =
				MatriksZTZ[kolom][baris]
				+ MatriksZ[kolom][obs]
				* MatriksZ[baris][obs];
		}
	}
}

/*---------------------------------------------------------------------------
  Bentuk Matriks Augmented
	[Aug] = [Z'Z]|[I]
---------------------------------------------------------------------------*/
long double (*MatriksAUGZTZ)[MaxVariabel];
MatriksAUGZTZ = new long double	[JumlahVariabel*2][MaxVariabel];
for (int kolom = 0; kolom < 2*JumlahVariabel; kolom++) {
	for (int baris = 0; baris < JumlahVariabel; baris++) {
		if (kolom >= JumlahVariabel) {
			if (kolom == baris + JumlahVariabel) {
				MatriksAUGZTZ[kolom][baris] = 1.;
			}
			else {
				MatriksAUGZTZ[kolom][baris] = 0.;
			}
		}
		else {
			MatriksAUGZTZ[kolom][baris] =
				MatriksZTZ[kolom][baris];
		}
	}
}
delete [] MatriksZTZ;
MatriksZTZ = 0;

/*---------------------------------------------------------------------------
  Hitung matriks invers dengan eliminasi Gauss Jordan
---------------------------------------------------------------------------*/
isSolveablilty = true;
for (int baris = 0; baris < JumlahVariabel; baris++) {
	/*.......................................................................
	Tetapkan variabel pembagi dari matriks diagonal yang nomor baris sama
	dengan nomor kolomnya
	.......................................................................*/
	long double Pembagi;
	Pembagi = MatriksAUGZTZ[baris][baris];

	/*.......................................................................
	Periksa apakah elemen diagonal dari matriks kiri adalah nol
	.......................................................................*/
	if (MatriksAUGZTZ[baris][baris] == 0) {
	/*.......................................................................
	  Apabila sama dengan nol, tukarkan baris elemen diagonal mengandung
	  nol dengan baris berikutnya, periksa ulang elemen diagonal
	.......................................................................*/
	for (int ibaris = baris+1; ibaris < JumlahVariabel;
			ibaris++) {
			if(MatriksAUGZTZ[baris][ibaris] != 0) {
				for (int kolom = 0;
					kolom < (2*JumlahVariabel);
					kolom++) {
					long double TempSwap;
					TempSwap = MatriksAUGZTZ
						[kolom][baris];
					MatriksAUGZTZ[kolom][baris] =
						MatriksAUGZTZ[kolom]
						[ibaris];
					MatriksAUGZTZ[kolom][ibaris]
						= TempSwap;
				}
			}
		}
		Pembagi = MatriksAUGZTZ[baris][baris];
		if (Pembagi == 0.) {
			isSolveablilty = false;
			baris = JumlahVariabel; // Tidak ditemukan solusi, hentikan perhitungan
		}
	}
  /*.........................................................................
	Bila faktor pembagi bukan nol, lanjutkan operasi eliminasi supaya
	didapatkan invers dari matriks
  .........................................................................*/
	if (isSolveablilty) {
	/*.......................................................................
	  Bagi semua bilangan pada baris ke-i kolom ke-j dengan faktor
	  pembagi
	.......................................................................*/
		for (int kolom = baris; kolom < (2*JumlahVariabel);
			kolom++) {
			MatriksAUGZTZ[kolom][baris] =
				MatriksAUGZTZ[kolom][baris] / Pembagi;
		}
	/*.......................................................................
	  Kurangkan bilangan pada baris ke-i supaya menjadi nol, kecuali pada
	  elemen diagonal, yang pasti akan menghasilkan nilai 1, sehingga
	  terbentuk matriks augmented yang sebelah kiri adalah matriks
	  identitas dan sebelah kanan merupakan matriks inverse
		[Aug] = [I] | [Z'Z]^(-1)
	.......................................................................*/
		for (int ibaris = 0; ibaris < JumlahVariabel;
			ibaris++) {
			if (ibaris != baris) {
				long double PembuatNol =
				MatriksAUGZTZ[baris][ibaris];
				for (int kolom = 0;
					kolom < (2*JumlahVariabel);
					kolom++) {
					MatriksAUGZTZ[kolom][ibaris]
						= MatriksAUGZTZ
						[kolom][ibaris] -
						(MatriksAUGZTZ
						[kolom][baris] *
						PembuatNol);
				}
			}
		}
	}
}

/*---------------------------------------------------------------------------
  Pindahkan elemen matriks augmented ke matriks invers
---------------------------------------------------------------------------*/
for (int kolom = 0; kolom < JumlahVariabel; kolom++) {
	for (int baris = 0; baris < JumlahVariabel; baris++) {
		MatriksInvers[kolom][baris] =
			MatriksAUGZTZ[kolom+JumlahVariabel][baris];
	}
}
delete [] MatriksAUGZTZ;
MatriksAUGZTZ = 0;
}
//---------------------------------------------------------------------------

void Transformasi(
	long double (*MatriksZ)[MaxObservasi],
	long double (*VariabelX)[MaxObservasi],
	long double *KoefisienC,
	int JumlahVariabel,
	int JumlahObservasi)
{
// [Z] = [X^C]
for (int obs = 0; obs < JumlahObservasi; obs++) {
	MatriksZ[0][obs] = 1.;
}
for (int var = 0; var < JumlahVariabel-1; var++) {
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		if (VariabelX[var+1][obs] == 0.) {
			MatriksZ[var+1][obs] = 0.;
		}
		else if (VariabelX[var+1][obs] == 1.) {
			MatriksZ[var+1][obs] = 1.;
		}
		else {
			MatriksZ[var+1][obs] =
				powl(VariabelX[var+1][obs],
				KoefisienC[var]);
		}
	}
}
}
//---------------------------------------------------------------------------

void White(
	int JumlahVariabel,
	int JumlahObservasi,
	long double *Residual2,
	long double *KoefisienC,
	long double (*VariabelX)[MaxObservasi],
	long double& RSQUAREWhite,
	long double& ProbWhite,
	long double& SSRegWhite,
	long double& SSResWhite,
	long double& SSTotalWhite,
	long double& MeanRegressionWhite,
	long double& MeanResidualWhite,
	long double& FVALUEWhite,
	long double& PROBFWhite)
{
/****************************************************************************
  Rutin untuk Pengujian Heteroskedastisitas dengan Uji White (No Cross Term)
****************************************************************************/
TulisHeaderUjiWhite();
long double (*MatriksZ)[MaxObservasi];
MatriksZ = new long double [2*JumlahVariabel][MaxObservasi];
long double (*VariabelU2);
VariabelU2 = new long double[MaxObservasi];
long double (*MatriksInvers)[MaxVariabel];
MatriksInvers = new long double	[2*(JumlahVariabel-1)+1][MaxVariabel];
bool isSolveablilty = true;
int JumlahVariabelWhite = 2*(JumlahVariabel-1)+1;

/*---------------------------------------------------------------------------
  Ambil Data Variabel Bebas dan Variabel Tak Bebas
	U^2 = B0 + B1.Z1 B1.Z1^2 + ... + Bn.Zn + BN.Zn^2
	U^2 adalah kuadrat selisih ramalan dengan kenyataan
---------------------------------------------------------------------------*/
for (int obs = 0; obs < JumlahObservasi; obs++) {
	VariabelU2[obs] = Residual2[obs];
	MatriksZ[0][obs] = 1.;
}

int VarW = 0;
for (int var = 0; var < JumlahVariabel-1; var++) {
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		long double Z;
		if (VariabelX[var+1][obs] == 0.) {
			Z = 0.;
		}
		else if (VariabelX[var+1][obs] == 1.) {
			Z = 1.;
		}
		else {
			Z = powl(VariabelX[var+1][obs],
				KoefisienC[var]);
		}
		MatriksZ[VarW+1][obs] = Z;
		MatriksZ[VarW+2][obs] = Z*Z;
	}
	VarW ++;
	VarW ++;
}

SolusiInvers(
	MatriksZ,
	JumlahVariabelWhite,
	JumlahObservasi,
	MatriksInvers,
	isSolveablilty
);

if (isSolveablilty) {
	long double (*KoefisienB) = new long double[2*JumlahVariabel];
	HitungKoefisienB(
		KoefisienB,
		MatriksZ,
		VariabelU2,
		MatriksInvers,
		JumlahVariabelWhite,
		JumlahObservasi
	);

	long double *Residual2White = new long double [JumlahObservasi];
	for (int obs = 0; obs < JumlahObservasi; obs++) {
		long double Ramalan = 0.;
		long double ErrorT;
		for (int var = 0; var < JumlahVariabelWhite; var++) {
			if (var == 0) {
				Ramalan = Ramalan + KoefisienB[var];
			}
			else {
				long double HasilKali =
					MatriksZ[var][obs] *
					KoefisienB[var];
					Ramalan = Ramalan + HasilKali;
			}
		}
		ErrorT = VariabelU2[obs]-Ramalan;
		Residual2White[obs] = ErrorT*ErrorT;
	}
	delete [] KoefisienB;
	KoefisienB = 0;
	SSResWhite = HitungSSRes(JumlahObservasi,
		Residual2White);
	delete [] Residual2White;
	Residual2White = 0;
	SSTotalWhite   = HitungSSTotal(JumlahObservasi, VariabelU2);
	SSRegWhite     = SSTotalWhite - SSResWhite;
	RSQUAREWhite   = SSRegWhite / SSTotalWhite;
	long double StatWhite = RSQUAREWhite * JumlahObservasi / 2.;
	ProbWhite = gammp(JumlahVariabel - 1,
		fabsl(StatWhite));
	MeanRegressionWhite = SSRegWhite /
		(JumlahVariabelWhite - 1.);
	MeanResidualWhite   = SSResWhite / (JumlahObservasi -
		JumlahVariabelWhite);
	FVALUEWhite = fabsl(MeanRegressionWhite) / MeanResidualWhite;

	PROBFWhite = ProbF(fabsl(FVALUEWhite), JumlahObservasi,
		JumlahVariabelWhite);
}
else {
	Tulis("        Error : Heteroscedasticity Test");
}
delete [] MatriksInvers;
MatriksInvers = 0;
delete [] MatriksZ;
MatriksZ = 0;
delete [] VariabelU2;
VariabelU2 = 0;
}
//---------------------------------------------------------------------------

