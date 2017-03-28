#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Data.h"
#include "Hipotezy.h"


using namespace std;

class Histogram
{
	int ilosc_przedzialow;
	double przedzial;
	double rozstep;
	int* czestosci;

public:
	Histogram();

	void rysuj_histogram(Data dane_etykieta);
	void dane_histogram(Data dane_etykieta);

	~Histogram();
};

