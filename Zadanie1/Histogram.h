#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Data.h"
#include "Hipotezy.h"
//
//
//#define GNUPLOT_PATH "C:\\gnuplot\\bin"
//#include "gnuplot_i.hpp"


using namespace std;

class Histogram
{
	int ilosc_przedzialow;
	double przedzial;
	double rozstep;
	int* czestosci;

public:
	Histogram();

	void rysuj_histogram(Data dane_etykieta1, Data dane_etykieta2, Data dane);
	void dane_histogram(Data dane_etykieta);

	~Histogram();
};

