#pragma once
#include "Data.h"

class Hipotezy
{	
public:
	Hipotezy();
	~Hipotezy();

	Data* dane_etykieta1;  // dane kt�re mia�y przypisan� jedynke
	Data* dane_etykieta2;  // dane kt�re mia�y przypisane dw�jk�

	double wspolczynnik_z;


	void rozdziel(vector <double> dane1, vector <double> dane2);
	void testowanie_hipotez();


};

