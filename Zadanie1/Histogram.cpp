#include "Histogram.h"

#define GNUPLOT_PATH "C:\\gnuplot\\bin"
#include "gnuplot_i.hpp"

Histogram::Histogram()
{
}

void Histogram::rysuj_histogram(Data dane_etykieta1, Data dane_etykieta2, Data dane )
{
	

	////		zainicjowanie programu GnuPlot
	Gnuplot::set_GNUPlotPath(GNUPLOT_PATH);
	Gnuplot main_plot;

	//// 		Podpisy na wykresie
	main_plot.set_title("Histogram");
	main_plot.set_xlabel("Ox");
	main_plot.set_ylabel("Oy");

	//// 		styl rysowania ustawiony na linie
	main_plot.set_style("boxes");

	//// 		wlaczenie siatki
	main_plot.set_grid();

	//// 		zakres osi x


	main_plot.set_xrange(dane.getMin(), dane.getMax());
	main_plot.set_yrange(0, 100);


	////		rysowanie funkcji przed obliczeniem pierwiastkow (poglad polozenia pierwsiatkow)
	//main_plot.plot_equation(funkcja, "Pogladowa funkcja");
	//for (int i = 0; i < dane.ilosc_przedzialow; i++)
	//{
	//	vector<int> x = { 0 };
	//	vector<int> y = { *dane.czestosci };
	//	main_plot.plot_xy(x, y, "Pogladowa funkcja");
	//}

	dane_histogram(dane_etykieta1);
	vector<double> x;
	vector<double> y;

	for (int i = 0; i < ilosc_przedzialow; i++) {
		x.push_back(dane_etykieta1.getMin() + i*rozstep + rozstep / 2);
		y.push_back(czestosci[i]);
		//cout << "[" << x[i] << ", " << y[i] << "]" << endl;
	}

	for (int i = 0; i < ilosc_przedzialow; i++)
	{
		czestosci[i] = 0;
	}

	ilosc_przedzialow = 0;
	przedzial = 0;
	rozstep = 0;

	vector<double> x2;
	vector<double> y2;
	dane_histogram(dane_etykieta2);

	for (int i = 0; i < ilosc_przedzialow; i++) {
		x2.push_back(dane_etykieta2.getMin() + i*rozstep + rozstep / 2);
		y2.push_back(czestosci[i]);
		//cout << "[" << x[i] << ", " << y[i] << "]" << endl;
	}

	//main_plot.plot_xy(x, y, "Pogladowa funkcja");
	main_plot.plot_xy(x, y, "Klasa C1");
	main_plot.plot_xy(x2, y2, "Klasa C2");
	getchar();
}


void Histogram::dane_histogram (Data dane_etykieta) //na kopii
{	
	//dane_etykieta.usuwanie_el_odstajacych(0.99);

	ilosc_przedzialow = round( sqrt(dane_etykieta.getRozmiar()));

	przedzial = dane_etykieta[dane_etykieta.getRozmiar()-1] - dane_etykieta.getMin();

	rozstep = przedzial / ilosc_przedzialow;

	czestosci = new int[ilosc_przedzialow];

	for (int i = 0; i < ilosc_przedzialow; i++)
	{
		czestosci[i] = 0;
	}

	for (int i = 0; i < dane_etykieta.getRozmiar(); i++)
	{
		for (int k = 0; k < ilosc_przedzialow; k++)
		{
			if (dane_etykieta[i] <= dane_etykieta.getMin() + rozstep *k)
			{
				czestosci[k] ++;
				break;
			}
		}
	}

}

Histogram::~Histogram()
{
}
