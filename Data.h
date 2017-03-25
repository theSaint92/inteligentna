#pragma once

#include "Histogram.h"
#include <vector>

class Data
{
	//Same dane
	std::vector<double> dane;

	//Max i min
	double min;
	double max;

	//Miary srednie i pozycyjne
	double srednia_arytmetyczna;
	double srednia_harmoniczna;
	double srednia_geometryczna;
	double mediana;
	//pair<double, int> dominatnta;

	//Miary rozproszenia
	double wariancja;
	double odchylenie_standardowe;

	//Miary asymetrii
	double trzeci_moment_centralny;
	double wspolczynnik_asymetrii;
	double wspolczynnik_as_dominanta;

	//Miary koncentracji
	double kurtoza;

	//Dane do histogramu
	Histogram hist;

public:

	//Konstruktory i Destruktory
	Data(std::vector<double> dane_wejsciowe);
	~Data();

	//Getery
	double getMin();
	double getMax();
	double getSredniaArytmetyczna();
	double getSredniaHarmoniczna();
	double getSredniaGeometryczna();
	double getMediana();
	//pair<double, int> dominatnta;
	double getWariancja();
	double getOdchylenieStandardowe();
	double getTrzeciMomentCentralny();
	double getWspolczynnikAsymetrii();
	double getWspolczynnikAsDominanta();
	double getKurtoza();
	Histogram getHistogram();


	//Funkcje
	void wylicz_min();
	void wylicz_max();
	void wylicz_srednia_arytmetyczna();
	void wylicz_srednia_harmoniczna();
	void wylicz_srednia_geometryczna();
	void wylicz_mediana();
	//pair<double, int> dominatnta;
	void wylicz_wariancja();
	void wylicz_odchylenie_standardowe();
	void wylicz_trzeci_moment_centralny();
	void wylicz_wspolczynnik_asymetrii();
	void wylicz_wspolczynnik_as_dominanta();
	void wylicz_kurtoza();

	Data usuwanie_el_odstajacych(double przedzial_ufnosci);
	Data standaryzacja_zmiennej();

};

