#include "data.h"
#include <algorithm>



Data::Data(std::vector<double> dane_wejsciowe) {
	//Wczytanie danych do pliku
	for (int i = 0; i < dane_wejsciowe.size(); i++)
	{
		dane.push_back(dane_wejsciowe[i]);
	}
	sort(dane.begin(), dane.end());

	//Wyznaczenie parametrow tych danych
	wylicz_min();
	wylicz_max();
	wylicz_srednia_arytmetyczna();
	// wylicz_srednia_harmoniczna();
	// wylicz_srednia_geometryczna();
	// wylicz_mediana();
	// wylicz_dominatnta;
	// wylicz_wariancja();
	// wylicz_odchylenie_standardowe();
	// wylicz_trzeci_moment_centralny();
	// wylicz_wspolczynnik_asymetrii();
	// wylicz_wspolczynnik_as_dominanta();
	// wylicz_kurtoza();
}


Data::~Data() {

}


double Data::getMin() {
	return min;
}

double Data::getMax() {
	return max;
}

double Data::getSredniaArytmetyczna() {
	return srednia_arytmetyczna;
}

double Data::getSredniaHarmoniczna() {
	return srednia_harmoniczna;
}

double Data::getSredniaGeometryczna() {
	return srednia_geometryczna;
}

double Data::getMediana() {
	return mediana;
}

//pair<double, int> dominatnta;

double Data::getWariancja() {
	return wariancja;
}

double Data::getOdchylenieStandardowe() {
	return odchylenie_standardowe;
}

double Data::getTrzeciMomentCentralny() {
	return trzeci_moment_centralny;
}

double Data::getWspolczynnikAsymetrii() {
	return wspolczynnik_asymetrii;
}

double Data::getWspolczynnikAsDominanta() {
	return wspolczynnik_as_dominanta;
}

double Data::getKurtoza() {
	return kurtoza;
}

Histogram Data::getHistogram() {
	return hist;
}

void Data::wylicz_min() {
	min = dane[0];
}

void Data::wylicz_max() {
	max = dane[dane.size() - 1];
}

void Data::wylicz_srednia_arytmetyczna() {
	double suma = 0;
	for (int k = 0; k < dane.size(); k++) {
		suma += dane[k];
	}
	srednia_arytmetyczna = suma / dane.size();
}