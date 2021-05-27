//---------------------------------------------------------------------------

#pragma hdrstop

#include "UnitProbabilitas.h"
#include <math.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)
  
long double betai(long double a, long double b, long double x)
{
/****************************************************************************
  Rutin untuk Menghitung Nilai Incomplete Beta Function
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/

long double beta;

if (x == 0. || x == 1.0) {
	beta = 0.0;
}
else {
	beta = expl(gammln(a+b)-gammln(a)-gammln(b)+a*logl(x)+b*logl(1.0-x));
}
if (x < (a+1.0)/(a+b+2.0)) {
	return beta * betacf(a, b, x)/a;
}
else {
	return 1.0 - beta * betacf(b, a, 1.0-x)/b;
}
}
//---------------------------------------------------------------------------

long double betacf(long double a, long double b, long double x)
{
/****************************************************************************
  Rutin untuk Melakukan Evaluasi Continued Fraction
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/
const long double FPMIN = 1.0e-30;   
long double c;
long double d;
long double h;
long double aa;

/* Langkah awal dari Lentz's method */
c = 1.;
d = 1.-((a+b)*x)/(a+1.); if (fabsl(d) < FPMIN) {d = FPMIN;}
d = 1./d;
h = d;
for (int m = 1; m <= 200; m++) {
	int m2 = m*2;
	aa = (m*(b-m)*x)/((a+m2)*((a-1.)+m2));
	// Genap
	d = 1.+(aa*d); if (fabsl(d) < FPMIN) {d = FPMIN;}
	c = 1.+(aa/c); if (fabsl(c) < FPMIN) {c = FPMIN;}
	d = 1./d;
	h *= (d*c);
	aa = -((a+m)*((a+b)+m)*x)/((a+m2)*((a+1.)+m2));
	// Ganjil
	d = 1.+(aa*d); if (fabsl(d) < FPMIN) {d = FPMIN;}
	c = 1.+(aa/c); if (fabsl(c) < FPMIN) {c = FPMIN;}
	d = 1./d;
	h *= (d*c);
	// Periksa apakah sudah mendekati nol
	if (fabsl((d * c) - 1.) < 3.0e-7) {
		break;
	}
}
return h;
}
//---------------------------------------------------------------------------

long double gammln(long double Z)
{
/****************************************************************************
  Rutin untuk Menghitung Nilai Logaritma Natural Gamma (ln Γ (Z)), Z > 0
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/

const long double Akar2Pi = 2.5066282746310005;
long double Koefisien[6];
long double Series;
long double RuasKiri;

Koefisien[0] =  76.18009172947146;
Koefisien[1] = -86.50532032941677;
Koefisien[2] =  24.01409824083091;
Koefisien[3] = -1.231739572450155;
Koefisien[4] =  0.001208650973866179;
Koefisien[5] = -0.000005395239384953;    
Series = 1.000000000190015; // Koefisien c0 mendekati 1
RuasKiri = ((Z+0.5)*logl(Z+5.5))-(Z+5.5);
for (int i = 0; i <= 5; i++) {
	Series = Series+(Koefisien[i]/(Z+i+1.));
}
return RuasKiri + logl((Akar2Pi*Series)/Z);
}
//---------------------------------------------------------------------------

long double gammp(long double a, long double x)
{
/****************************************************************************
  Rutin untuk Menghitung Incomplete Gamma Function (Γ (Z)) P(a,x)
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/
long double gamser, gammcf, gln;
if (x < a+1.) {
	gser(&gamser, a, x, &gln);
	return gamser;
}
else {
	gcf(&gammcf, a, x, &gln);
	return 1.-gammcf;
}
}
//---------------------------------------------------------------------------


long double gammq(long double a, long double x)
{
/****************************************************************************
  Rutin untuk Menghitung Incomplete Gamma Function (Γ (Z)) Q(a,x)
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/
long double gamser, gammcf, gln;
if (x < a+1.) {
	gser(&gamser, a, x, &gln);
	return 1.-gamser;
}
else {
	gcf(&gammcf, a, x, &gln);
	return gammcf;
}
}
//---------------------------------------------------------------------------

void gser(
  long double *gamser,
  long double a,
  long double x,
  long double *gln)
{
/****************************************************************************
  Rutin untuk Menghitung Series
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/

int n;
long double sum, del, ap;

*gln = gammln(a);
if (x <= 0.) {
	*gamser = 0.;
	return;
}
else {
	ap = a;
	del = sum = 1./a;
	for (n = 0; n <= 100; n++) {
		++ap;
		del *= x/ap;
		sum += del;
		if (fabsl(del) < fabsl(sum)*3.0e-7) {
			*gamser = sum*expl(-x+a*logl(x)-(*gln));
			return;
		}
	}
	return;
}
}
//---------------------------------------------------------------------------

void gcf(
	long double *gammcf,
	long double a,
	long double x,
	long double *gln)
{
/****************************************************************************
  Rutin untuk Menghitung Continued Fraction
  Sumber : Press, William H., Teukolsky, Saul A., Vetterling, William T.,
		   dan Flannery, Brian P., 2002. Numerical Recipes in C, The Art of
		   Scientific Computing, Second Edition. Cambridge: Cambridge
		   University Press
****************************************************************************/

long double an, b, c, d, del, h;
*gln = gammln(a);
b = x+1.-a;
c = 1./1.e-30;
d = 1./b;
h = d;
for (int i = 1; i <= 100; i++) {
	an = -i*(i-a);
	b += 2.;
	d = an*d+b;
	if (fabsl(d) < 1.e-30) {d = 1.e-30;}
	c = b+an/c;
	if (fabsl(c) < 1.e-30) {c = 1.e-30;}
	d = 1./d;
	del = d*c;
	h *= del;
	if (fabsl(del-1.) < 3.e-7) {break;}
}
*gammcf = expl(-x+a*logl(x)-(*gln))*h;
}
//---------------------------------------------------------------------------
