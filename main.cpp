#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "Data.h"
#include "Hipotezy.h"
#include "Histogram.h"
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

	//try {
	//	Data wszystkie_dane(dane1);
	//}
	//catch (exception)
	//{
	//	cout << "nie mozna wyznaczyc sredniej geometrycznej\n" << endl;
	//}

	Data wszystkie_dane(dane1);
	
	cout << "getMin(): " << wszystkie_dane.getMin() << endl;
	cout << "getMax(): " << wszystkie_dane.getMax() << endl;
	cout << "getSredniaArytmetyczna(): " << wszystkie_dane.getSredniaArytmetyczna() << endl;
	cout << "getSredniaHarmoniczna(): " << wszystkie_dane.getSredniaHarmoniczna() << endl;

	//cout << "getSredniaGeometryczna(): " << wszystkie_dane.getSredniaGeometryczna() << endl;

	try {
		cout << "srednia geometryczna wynosi:" << " " << wszystkie_dane.getSredniaGeometryczna();
		cout << "\n" << endl;
	}
	catch (exception)
	{
		cout << "nie mozna wyznaczyc sredniej geometrycznej\n" << endl;
	}

	cout << "getMediana(): " << wszystkie_dane.getMediana() << endl;

	if (wszystkie_dane.getDominanta()!= pair<double, int>())
	{
		cout << "\nDominanta wynosi " << wszystkie_dane.getDominanta().first << ", a jej ilosc wystapien to " << wszystkie_dane.getDominanta().second << "\n";
	}
	else
	{
		cout << "\nDominanta nie istnieje\n";
	}

	cout << "getWariancja(): " << wszystkie_dane.getWariancja() << endl;

	cout << "getOdchylenieStandardowe(): " << wszystkie_dane.getOdchylenieStandardowe() << endl;

	cout << "getTrzeciMomentCentralny(): " << wszystkie_dane.getTrzeciMomentCentralny() << endl;
	cout << "getWspolczynnikAsymetrii(): " << wszystkie_dane.getWspolczynnikAsymetrii() << endl;
	cout << "getKurtoza(): " << wszystkie_dane.getKurtoza() << endl;

	

	getchar();

}

void displayhelp() {
	cout << "Welcome to srututu!\n";
	cout << "List of parameters:\n";
	cout << "\t-h\t--help\tDisplay this menu\n";
	cout << "\t-f\t--file\tFile you want to take data from\n";
}
