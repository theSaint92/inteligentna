#pragma once
#include "Data.h"

class Hipotezy
{	
public:
	Hipotezy();
	~Hipotezy();

	Data* dane_etykieta1;  // dane które mia³y przypisan¹ jedynke
	Data* dane_etykieta2;  // dane które mia³y przypisane dwójkê

	double wspolczynnik_z;


	void rozdziel(vector <double> dane1, vector <double> dane2);
	void testowanie_hipotez();


};

