//---------------------------------------------------------------------------

#ifndef UnitProbabilitasH
#define UnitProbabilitasH
//---------------------------------------------------------------------------
#endif

long double betai
	 (
	 long double a,
	 long double b,
	 long double x
	 );
long double betacf
	 (
	 long double a,
	 long double b,
	 long double x
	 );
long double gammln(long double Z);
long double gammp(long double a, long double x);
long double gammq(long double a, long double x);
void gser
	 (
	 long double *gamser,
	 long double a,
	 long double x,
	 long double *gln
	 );
void gcf
	(
	long double *gammcf,
	long double a,
	long double x,
	long double *gln
	);
