#include "Hipotezy.h"



Hipotezy::Hipotezy()
{
}


Hipotezy::~Hipotezy()
{
}

void Hipotezy::rozdziel(vector <double> dane1, vector <double> dane2)
{
	vector<double> tmp1, tmp2;

	for (int i = 0; i < dane1.size(); i++)
	{
		if (dane2[i] == 1) tmp1.push_back(dane1[i]);
		if (dane2[i] == 2) tmp2.push_back(dane1[i]);
	}
	sort(tmp1.begin(), tmp1.end());
	sort(tmp2.begin(), tmp2.end());

	dane_etykieta1 = new Data(tmp1);
	dane_etykieta2 = new Data(tmp2);
}

void Hipotezy::testowanie_hipotez()
{
	double temp_1 = (dane_etykieta1->getOdchylenieStandardowe()) / dane_etykieta1->getRozmiar();
	double temp_2 = (dane_etykieta2->getOdchylenieStandardowe()) / dane_etykieta2->getRozmiar();

	wspolczynnik_z = (dane_etykieta1->getSredniaArytmetyczna()-dane_etykieta2->getSredniaArytmetyczna())/ sqrt(temp_1 + temp_2);
}
