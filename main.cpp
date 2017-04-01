#include "Histogram.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h> //exp
#include <cstring>
#include "Data.h"
//#include "Hipotezy.h"
#include <map>

using namespace std;

void displayhelp();
void testowanie_hipotez(Data dane1, Data dane2, double alpha, char* plik);

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
	vector <double> dane1, dane2, dane1_etykieta1, dane1_etykieta2;
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
				if (dane2[k] == 1) dane1_etykieta1.push_back(dane1[k]);
				if (dane2[k] == 2) dane1_etykieta2.push_back(dane1[k]);
				cout << "DANE1[" << k << "] = " << dane1[k] << ", DANE2[" << k << "] = " << dane2[k] << ".\n";
				k++;
			} while (!plik.eof());
		}
	}

	////Parametry dla ca³ego zbioru danych

	cout << "Parametry podstawoego zbioru danych: \n" << endl;
	Data wszystkie_dane(dane1);
	Data dane_etykieta1(dane1_etykieta1);
	Data dane_etykieta2(dane1_etykieta2);

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

	cout << dane_etykieta1.getRozmiar() << " " << dane_etykieta1.getSredniaArytmetyczna();

	//Histogram hist1;
	//hist1.rysuj_histogram(*hipoteza.dane_etykieta1, *hipoteza.dane_etykieta2, dane1 );

	//DLA 200242
	testowanie_hipotez(dane_etykieta1, dane_etykieta2, 0.010, "./200242/wyniki.txt");
	//DLA 203940
	//testowanie_hipotez(dane_etykieta1, dane_etykieta2, 0.010, "./203940/wyniki.txt");

	getchar();
}

void displayhelp() {
	cout << "Welcome to srututu!\n";
	cout << "List of parameters:\n";
	cout << "\t-h\t--help\tDisplay this menu\n";
	cout << "\t-f\t--file\tFile you want to take data from\n";
}


void testowanie_hipotez(Data dane1, Data dane2, double alpha, char* plik) {
	fstream wyniki;
	wyniki.open(plik);
	
	int n1 = dane1.getRozmiar();
	int n2 = dane2.getRozmiar();
	double m1 = dane1.getSredniaArytmetyczna();
	double m2 = dane2.getSredniaArytmetyczna();
	double s1 = dane1.getOdchylenieStandardowe();
	double s2 = dane2.getOdchylenieStandardowe();

	double dof = 0;
	double z = 0;
	double pValueNormal = 0;
	//double pValueStudent = 0;
	char* decisionNormal = ""; //"H0 rejected(alternative proved)" or "H0 proved"
	//char* decisionStudent = "";

	//Liczymy dof dla t-Studenta
	double dol1 = s1*s1 / n1;
	double dol2 = s2*s2 / n2;
	double gora = dol1 + dol2;
	dof = gora*gora / (dol1*dol1 / (n1 - 1) + dol2*dol2 / (n2 - 1));

	//Liczymy znormalizowana roznice srednich
	z = (m1 - m2) / sqrt(s1*s1 / n1 + s2*s2 / n2);

	//Dobra to liczymy teraz fajne rzeczy
	//GESTOSC ROZKLADU NORMALNEGO
	// 1/sqrt(2*M_PI) * exp(-x*x/2)

	

	wyniki << "1st sample size = " << n1 << endl;
	wyniki << "2nd sample size = " << n2 << endl << endl;

	wyniki << "1st sample mean = " << m1 << endl;
	wyniki << "2nd sample mean = " << m2 << endl;
	wyniki << "1st sample stdev =  " << s1 << endl;
	wyniki << "2nd sample stdev = " << s2 << endl;
	wyniki << "Degrees of freedom for Student - t distribution = " << dof << endl << endl;

	wyniki << "Results:" << endl;
	wyniki << "Statistics value z = " << z << endl;
	wyniki << "Normal distribution : p - value = " << pValueNormal << endl;
	//wyniki << "Student - t distribution : p - value = " << pValueStudent << endl;
	wyniki << "Normal distribution : " << decisionNormal << endl;
	//wyniki << "Student - t distribution : " << decisionStudent << endl;

}
