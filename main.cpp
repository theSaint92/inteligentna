#include "Histogram.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "Data.h"
//#include "Hipotezy.h"
#include <map>

using namespace std;

void displayhelp();

int main(int argc, char* argv[])
{
	// PROGRAM ODPALONY TYLKO DLA HELPA
	if (argc == 1) {
		displayhelp();
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
			displayhelp();
			return 0;
		}
	}

	//WCZYTYWANIE Z PLIKU
	fstream plik;
	vector <double> dane1, dane2;
	for (int i = 1; i < argc; i++) {
		cout << i << ". argv = " << argv[i] << endl;
		if (!strcmp(argv[i], "--file") || !strcmp(argv[i], "-f")) {
			cout << "elo";
			plik.open(argv[i + 1]);
			double temp;
			int k = 0;
			do {
				plik >> temp;
				dane1.push_back(temp);
				plik >> temp;
				dane2.push_back(temp);
				cout << "DANE1[" << k << "] = " << dane1[k] << ", DANE2[" << k << "] = " << dane2[k] << ".\n";
				k++;
			} while (!plik.eof());
		}
	}

	////Parametry dla ca³ego zbioru danych

	cout << "Parametry podstawoego zbioru danych: \n" << endl;
	Data wszystkie_dane(dane1);

	cout << "Miniumum wynosi: " << wszystkie_dane.getMin() << endl;
	cout << "Maximum wynosi: " << wszystkie_dane.getMax() << endl;
	cout << "Srednia arytmetyczna: " << wszystkie_dane.getSredniaArytmetyczna() << endl;
	cout << "Srednia harmoniczna: " << wszystkie_dane.getSredniaHarmoniczna() << endl;

	try {
		cout << "srednia geometryczna wynosi:" << " " << wszystkie_dane.getSredniaGeometryczna()<< endl;
	}
	catch (exception)
	{
		cout << "Nie mozna wyznaczyc sredniej geometrycznej dla podenego zbioru\n";
	}

	cout << "Mediana wynosi: " << wszystkie_dane.getMediana();

	if (wszystkie_dane.getDominanta()!= pair<double, int>())
	{
		cout << "\nDominanta wynosi: " << wszystkie_dane.getDominanta().first << ", a jej ilosc wystapien to: " << wszystkie_dane.getDominanta().second << "\n";
	}
	else
	{
		cout << "\nDominanta nie istnieje\n";
	}

	cout << "Wariancja wynosi: " << wszystkie_dane.getWariancja() << endl;

	cout << "Odchylenie standardowe wynosi : " << wszystkie_dane.getOdchylenieStandardowe() << endl;

	cout << "Wartosc trzeciego momentu centralnego: " << wszystkie_dane.getTrzeciMomentCentralny() << endl;
	cout << "Wartosc wspolczynnika asymetrii: " << wszystkie_dane.getWspolczynnikAsymetrii() << endl;
	cout << "Wartosc wspolczynnika asymetrii oparty na dominancie: " << wszystkie_dane.getWspolczynnikAsDominanta() << endl;
	cout << "Kurtoza: " << wszystkie_dane.getKurtoza() << endl;
	cout << endl;

	Hipotezy hipoteza;
	hipoteza.rozdziel(dane1, dane2);

	cout << "Parametry dla zbioru danych z etykieta 1\n " << endl;
	// Dane dla etykiety 1/////////////////////////////////////////////
	cout << "Srednia arytmetyczna: " << hipoteza.dane_etykieta1->getSredniaArytmetyczna() << endl;
	cout << "Srednia harmoniczna: " << hipoteza.dane_etykieta1->getSredniaHarmoniczna() << endl;

	try {
		cout << "srednia geometryczna wynosi:" << " " << hipoteza.dane_etykieta1->getSredniaGeometryczna();
	}
	catch (exception)
	{
		cout << "Nie mozna wyznaczyc sredniej geometrycznej dla podenego zbioru\n" << endl;
	}

	cout << "Mediana wynosi: " << hipoteza.dane_etykieta1->getMediana();

	if (hipoteza.dane_etykieta1->getDominanta() != pair<double, int>())
	{
		cout << "\nDominanta wynosi " << hipoteza.dane_etykieta1->getDominanta().first << ", a jej ilosc wystapien to " << hipoteza.dane_etykieta1->getDominanta().second << "\n";
	}
	else
	{
		cout << "\nDominanta nie istnieje\n";
	}
	cout << "Wariancja wynosi: " << hipoteza.dane_etykieta1->getWariancja() << endl;
	cout << "Odchylenie standardowe wynosi :"<<hipoteza.dane_etykieta1->getOdchylenieStandardowe() << endl;
	cout << "Wartosc trzeciego momentu centralnego: " << hipoteza.dane_etykieta1->getTrzeciMomentCentralny() << endl;
	cout << "Wartosc wspolczynnika asymetrii: " << hipoteza.dane_etykieta1->getWspolczynnikAsymetrii() << endl;
	cout << "Wartosc wspolczynnika asymetrii oparty na dominancie: " << hipoteza.dane_etykieta1->getWspolczynnikAsDominanta() << endl;
	cout << "Kurtoza: " <<  hipoteza.dane_etykieta1->getKurtoza() << endl;
	cout << endl;

	// Dane dla etykiety 2//////////////////////////////////////////
	cout << "Parametry dla zbioru danych z etykieta 2\n " << endl;
	cout << "Srednia arytmetyczna: " << hipoteza.dane_etykieta2->getSredniaArytmetyczna() << endl;
	cout << "Srednia harmoniczna: " << hipoteza.dane_etykieta2->getSredniaHarmoniczna() << endl;

	try {
		cout << "srednia geometryczna wynosi:" << " " << hipoteza.dane_etykieta2->getSredniaGeometryczna();
	}
	catch (exception)
	{
		cout << "Nie mozna wyznaczyc sredniej geometrycznej dla podenego zbioru\n" << endl;
	}

	cout << "Mediana wynosi: " << hipoteza.dane_etykieta2->getMediana();

	if (hipoteza.dane_etykieta2->getDominanta() != pair<double, int>())
	{
		cout << "\nDominanta wynosi " << hipoteza.dane_etykieta2->getDominanta().first << ", a jej ilosc wystapien to " << hipoteza.dane_etykieta2->getDominanta().second << "\n";
	}
	else
	{
		cout << "\nDominanta nie istnieje\n";
	}
	cout << "Wariancja wynosi: " << hipoteza.dane_etykieta2->getWariancja() << endl;
	cout << "Odchylenie standardowe wynosi :" << hipoteza.dane_etykieta2->getOdchylenieStandardowe() << endl;
	cout << "Wartosc trzeciego momentu centralnego: " << hipoteza.dane_etykieta2->getTrzeciMomentCentralny() << endl;
	cout << "Wartosc wspolczynnika asymetrii: " << hipoteza.dane_etykieta2->getWspolczynnikAsymetrii() << endl;
	cout << "Wartosc wspolczynnika asymetrii oparty na dominancie: " << hipoteza.dane_etykieta2->getWspolczynnikAsDominanta() << endl;
	cout << "Kurtoza:" << hipoteza.dane_etykieta2->getKurtoza() << endl;
	cout << endl;

	Histogram hist1;
	hist1.rysuj_histogram(*hipoteza.dane_etykieta1, *hipoteza.dane_etykieta2, dane1 );

	getchar();

}

void displayhelp() {
	cout << "Welcome to srututu!\n";
	cout << "List of parameters:\n";
	cout << "\t-h\t--help\tDisplay this menu\n";
	cout << "\t-f\t--file\tFile you want to take data from\n";
}
