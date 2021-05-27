//---------------------------------------------------------------------------

#ifndef UnitTulisH
#define UnitTulisH
//---------------------------------------------------------------------------
#endif
          
void TulisHeaderReport(int Populasi);
void TulisVariabel
     (
     int JumlahVariabel,
     int JumlahObservasi
     );
void TulisOptimasi
	 (
	 int Populasi,
	 int TotalGenerasi,
	 int Generasi,
	 long double *BestFitness,
	 long double *AvgFitness,
	 long double *WorstFitness,
	 bool IntegerOnly
     );
void TulisHasil(int Populasi);
void TulisTabelKoefisien
	 (
     int	      JumlahVariabel,
     int 	      *IndeksX,
     long double *KoefisienB,
     long double *KoefisienC,
     long double *SB,
     long double *TO,
     long double *PROBT
	 );
void TulisUjiNormalitas
     (
     long double Mean,
     long double Maksimum,
     long double Minimum,
     long double SDResid,
     long double Skewness,
     long double Kurtosis,
     long double JarqueBera,
     long double ProbJB
     );
void TulisHeaderTabelKolinieritas();
void TulisTabelKolinieritas
	 (
	 int Baris,
	 int IndeksVariabelBebas,
	 long double RSquareZi
	 );
void TulisHeaderUjiWhite();
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
	 );
void TulisHasilStatistik
	 (
	 long double StandardError,
	 long double RSQUARE,
	 long double ADJRSQUARE,
	 long double DWStat,
     long double LogLike,
     long double AIC,
     long double SC
	 );
void TulisTabelAnova
	 (
	 int 		 JumlahObservasi,
	 int 		 JumlahVariabel,
	 long double SSReg,
	 long double SSRes,
	 long double SSTotal,
	 long double MeanRegression,
	 long double MeanResidual,
	 long double FVALUE,
	 long double PROBF
	 );
void TulisPersamaan
	 (
	 int JumlahVariabel,
	 int JumlahPopulasi,
	 long double *KoefisienB,
	 long double *KoefisienC
	 );
void TulisTabelResidual(
	int JumlahObservasi,
	long double *VariabelY,
	long double *Residual,
	long double *Ramalan);
void TulisKoefisienCBest(int JumlahVariabel, long double* KoefisienCBest);
void TulisFooterReport();
void TulisQStat(
	int PeriodeTest,
	long double* AutoCorr,
	long double* QStat,
	long double* ProbQ);

