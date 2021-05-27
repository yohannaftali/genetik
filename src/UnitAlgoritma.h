//---------------------------------------------------------------------------

#ifndef UnitAlgoritmaH
#define UnitAlgoritmaH
//---------------------------------------------------------------------------
#endif
const int   MaxVariabel  = 55;
const int   MaxObservasi = 1000;
long double HitungSSTotal(int JumlahObservasi, long double *VariabelY);
long double HitungSSRes(int JumlahObservasi, long double *Residual2);
long double ProbF(long double FHitung,int Observasi, int Variabel);
long double ProbT(long double tHitung,int Observasi, int Variabel);
void AlgoritmaGenetik(
	int JumlahGenerasi,
	int JumlahPopulasi,
	int JumlahVariabel,
	int JumlahObservasi,
	long double* VariabelY,
	long double (*VariabelX)[MaxObservasi],
	int* IndeksX,
	long double BatasAtas,
	long double BatasBawah,
	long double XOAwal,
	long double XOAkhir,
	long double MutasiAwal,
	long double MutasiAkhir,
	bool PakaiOptimasiSebelum,
	long double* KoefisienCBest,
	int& Generasi,
	long double* AvgFitness,
	long double* BestFitness,
	long double* WorstFitness,
	bool IntegerOnly
);
void Statistik(
	int JumlahPopulasi,
	int JumlahVariabel,
	int JumlahObservasi,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	int *IndeksX,
	long double* KoefisienB,
	long double* KoefisienCBest,
	long double* Residual,
	long double* RamalanBest,
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
	long double& PROBFWhite);
void QStatTest(
	int JumlahObservasi,
	long double* Residual,
	long double AIC,
	long double SC,
	int& PeriodeTest,
	long double* AutoCorr,
	long double* QStat,
	long double* ProbQ);
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
	long double& ADJRSQUARE);
void BubbleSort(
	int JumlahPopulasi,
	int JumlahVariabel,
	long double *Fitness,
	long double (*KoefisienC)[MaxVariabel-1]);
void HitungFitness(
	int JumlahPopulasi,
	int JumlahObservasi,
	int JumlahVariabel,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	long double (*KoefisienC)[MaxVariabel-1],
	long double *Fitness);
void HitungFitnessIndividu(
	int JumlahObservasi,
	int JumlahVariabel,
	long double *VariabelY,
	long double (*VariabelX)[MaxObservasi],
	long double *KoefisienC,
	long double &Fitness);
void HitungKoefisienB(
	long double *KoefisienB,
	long double (*MatriksZ)[MaxObservasi],
	long double *VariabelY,
	long double (*MatriksInvers)[MaxVariabel],
	int JumlahVariabel,
	int JumlahObservasi);
void HitungKonvergensi(
	int Generasi,
	int JumlahPopulasi,
	long double *Fitness,
	long double *BestFitness,
	long double *AvgFitness,
	long double *WorstFitness,
	long double &Konvergensi);
void Multikolinieritas(
	int JumlahVariabel,
	int JumlahObservasi,
	long double *KoefisienC,
	long double (*VariabelX)[MaxObservasi],
	int *IndeksX);
void Mutasi(
	int JumlahVariabel,
	long double *Kromosom,
	long double BatasAtas,
	long double BatasBawah,
	bool IntegerOnly);
void PeriksaBatas(
	long double &Kromosom,
	long double BatasAtas,
	long double BatasBawah);
void PopulasiAwal(
	int JumlahPopulasi,
	int JumlahVariabel,
	long double BatasAtas,
	long double BatasBawah,
	long double (*Kromosom)[MaxVariabel-1],
	bool PakaiOptimasiSebelum,
	bool IntegerOnly
);
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
	long double &DWStat
);
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
	bool IntegerOnly
);
void Seleksi(
	int JumlahPopulasi,
	int JumlahVariabel,
	long double *Fitness,
	long double (*KoefisienC)[MaxVariabel-1]
);
void SolusiInvers(
	long double (*MatriksZ)[MaxObservasi],
	int JumlahVariabel,
	int JumlahObservasi,
	long double (*MatriksInvers)[MaxVariabel],
	bool &isSolveablilty
);
void Transformasi(
	long double (*MatriksZ)[MaxObservasi],
	long double (*VariabelX)[MaxObservasi],
	long double *KoefisienC,
	int JumlahVariabel,
	int JumlahObservasi
);
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
	long double& PROBFWhite);
