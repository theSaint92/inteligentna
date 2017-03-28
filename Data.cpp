#include "data.h"




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
	wylicz_srednia_harmoniczna();
	wylicz_srednia_geometryczna();
	wylicz_mediana();
	wylicz_dominanta();
	wylicz_wariancja();
	wylicz_odchylenie_standardowe();
	wylicz_trzeci_moment_centralny();
	wylicz_wspolczynnik_asymetrii();
	wylicz_wspolczynnik_as_dominanta();
	wylicz_kurtoza();
}


Data::~Data() {

}

double Data::operator[](int i)
{
	return dane[i];
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

pair<double, int> Data:: getDominanta()
{
	return dominanta;
}

double Data::getKurtoza() {
	return kurtoza;
}

//Histogram Data::getHistogram() {
//	return hist;
//}

void Data::wylicz_min() {
	min = dane[0];
}

void Data::wylicz_max() {
	max = dane[dane.size() - 1];
}

int Data::getRozmiar()
{
	return dane.size();
}

void Data::wylicz_srednia_arytmetyczna() {
	double suma = 0;
	for (int k = 0; k < dane.size(); k++) {
		suma += dane[k];
	}
	srednia_arytmetyczna = suma / dane.size();
}

void Data::wylicz_srednia_harmoniczna()
{
	double suma = 0;
	for (int k = 0; k < dane.size(); k++) {
		suma += 1 / dane[k];
	}
	srednia_harmoniczna = dane.size() / suma;
}


//Poniewa¿ wyci¹ganie pierwiastka wysokiego stopnia jest trudne, a liczebnoœæ szeregu n mo¿e byæ du¿a, 
//dlatego wygodniej jest korzystaæ z postaci zlogarytmowanej œredniej geometrycznej, tj.œredniej arytmetycznej logarytmów wartoœci zmiennej

void Data::wylicz_srednia_geometryczna()   //iloczyn *= pow(dane1[k], 1.0 / dane1.size()); 
{

	int licznik = 0;
	for (int k = 0; k < dane.size(); k++) {
		if (dane[k] < 0)
		{
			licznik++;
		}
	}

	if (licznik % 2 == 0 && dane.size() % 2 == 0)
	{
		double suma = 0;
		for (int k = 0; k < dane.size(); k++) {
			suma += log(dane[k]);
		}
		srednia_geometryczna = suma / dane.size();
	}
	if (licznik % 2 == 0 && dane.size() % 2 != 0) {
		double suma = 0;
		for (int k = 0; k < dane.size(); k++) {
			suma += log(dane[k]);
		}
		srednia_geometryczna = suma / dane.size();
	}
	else
	{
		srednia_geometryczna = INFINITY*0.0;
		/*throw exception();*/
	}
}

void Data::wylicz_mediana()
{

	if (dane.size() / 2 == 0)
	{
		mediana = dane[(dane.size() + 1) / 2];
	}
	else
	{
		mediana = (dane[(dane.size() / 2)] + dane[(dane.size() / 2 + 1)]) / 2;
	}
}


void Data::wylicz_dominanta()
{
	map <double, int> dominujaca;
	for (int k = 0; k < dane.size(); k++) {
		//if (dominujaca.find(dane[k]) == dominujaca.end())
		//{
		//	dominujaca.insert(pair <double, int>(dane[k], 1));
		//}
		//else
		//{
		dominujaca[dane[k]]++;   //wszystko co zakomentowane jest w tej jednej magicznej linijce
								 //}
	}
	//dominujaca.begin = max;

	pair<double, int> max = *dominujaca.begin();
	for (map<double, int>::iterator it = dominujaca.begin(); it != dominujaca.end(); it++)
	{
		if (it->second > max.second)
		{
			max = *it;
		}
	}

	for (map<double, int>::iterator it = dominujaca.begin(); it != dominujaca.end(); it++)
	{
		if (it->first != max.first && it->second == max.second)
		{
			dominanta= pair<double, int>();
			return;
		}
	}

	dominanta= max;
}

void Data::wylicz_wariancja()
{
	double suma = 0;
	for (int k = 0; k < dane.size(); k++) {
		suma += pow((dane[k] - srednia_arytmetyczna), 2);
	}
	wariancja = suma / (dane.size() - 1);
}

void Data::wylicz_odchylenie_standardowe()
{
	odchylenie_standardowe = sqrt(wariancja);
}

void Data::wylicz_trzeci_moment_centralny()
{
	double suma = 0;
	for (int k = 0; k < dane.size(); k++) {
		suma += pow((dane[k] - srednia_arytmetyczna), 3);
	}
	trzeci_moment_centralny = suma / dane.size();
}

void Data::wylicz_wspolczynnik_asymetrii()    //moment standaryzowany trzeciego rzêdu, trzeci moment przez dchylenie^3
{
	wspolczynnik_asymetrii = trzeci_moment_centralny / pow(odchylenie_standardowe, 3);
}

void Data::wylicz_wspolczynnik_as_dominanta()  //wspó³czynnik $ As $ (oparty na dominancie)
{
	wspolczynnik_as_dominanta = (srednia_arytmetyczna - dominanta.first) / odchylenie_standardowe;
}

void Data::wylicz_kurtoza()
{
	double suma = 0;

	for (int k = 0; k < dane.size(); k++) {
		suma += pow((dane[k] - srednia_arytmetyczna), 4);
	}

	double m4 = suma / dane.size();

	kurtoza = (m4 / pow(odchylenie_standardowe, 4)) - 3;
}

Data Data::usuwanie_el_odstajacych(double przedzial_ufnosci)
{

	for (vector <double>:: iterator it=dane.begin() ; it < dane.end(); it++) {
		if ((*it - srednia_arytmetyczna) > (przedzial_ufnosci* odchylenie_standardowe))
		{
			it = dane.erase(it);
		}
	}
	return dane;
}

Data Data::standaryzacja_zmiennej()
{
	double standard;

	for (int k = 0; k < dane.size(); k++) {
		standard = (dane[k] - srednia_arytmetyczna) / odchylenie_standardowe;
		dane_standaryzowane.push_back(standard);
	}
	return dane_standaryzowane;
}