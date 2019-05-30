#include <iostream>
#include <fstream>
#include <cmath>
// #include "time.h"


double f1(double x) {
	const double alfa = rand () / (RAND_MAX + 1.0) - 0.5;
	return 2 * sin(x) + sin (2*x) + 2 * sin (3*x) + alfa;  
}

double f2(double x) {
	return 2 * sin(x) + sin (2*x) + 2 * cos (x) + cos (2*x);  
}

double f3(double x) {
	return 2 * sin(1.1 * x) + sin (2.1 *x) + 2 * sin (3.1 * x);  
}


double funApprox(double *a, double *b, int Ms, int Mc, double x) {
	double sum1 = 0.0;
	double sum2 = 0.0;

	for (int k=1; k<=Ms; k++) {
		sum1+= a[k] * sin (k * x);
	}

	for (int j=0; j<=Mc; j++) {
		sum2+= b[j] * cos (j * x);
	}

	return sum1 + sum2;
}


int main() {

//otwarcie plikow tekstowych
	std::ofstream plik, plik2;

	//plik2.open("drugie_pochodne.dat");
	plik.open("podpunkt4.2.dat");

	// srand(time(NULL));

	int liczbaWezlow = 100;
	int Ms = 10;
	int Mc = 10;
	double a[Ms+1];
	double b[Mc+1];
	double x_min = 0;
	double x_max = 2 * M_PI;

	double wezly[liczbaWezlow];
	double y[liczbaWezlow];
	double deltaX = (x_max - x_min) / (liczbaWezlow);


	for (int i=0; i<liczbaWezlow; i++) {
		wezly[i] = x_min + (i * deltaX);
		y[i] = f3(wezly[i]);
	}


	for (int k=1; k<=Ms; k++) {
		a[k] = 0.0;
		for (int i=0; i<liczbaWezlow; i++) {
			a[k]+=y[i] * sin (k * wezly[i]) / (liczbaWezlow / 2);
		}
	}

	for (int k=0; k<=Mc; k++) {
		b[k] = 0.0;
		double wsp;
		
		if (k>0) wsp = liczbaWezlow / 2;
		else if (k==0) wsp = liczbaWezlow; 
		
		for (int i=0; i<liczbaWezlow; i++) {
			
			b[k]+=y[i] * cos (k * wezly[i]) / wsp;
		}
	}

	for (double x=0.0; x<2 * M_PI; x = x + 0.1) {
		plik << x << "," << f1(x) << "," << funApprox(a,b,Ms,Mc, x) << std::endl;
	}


	

//zamkniecie plikow tekstowych
	plik.close();
	//plik2.close();

    return 0;
}