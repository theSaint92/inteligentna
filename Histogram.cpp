#include "Histogram.h"

#define GNUPLOT_PATH "C:\\gnuplot\\bin"
#include "gnuplot_i.hpp"

Histogram::Histogram()
{

}

void Histogram::rysuj_histogram(Data dane_etykieta)
{
	dane_histogram(dane_etykieta);

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


	main_plot.set_xrange(dane_etykieta.getMin(), dane_etykieta.getMax());
	main_plot.set_yrange(0, 100);


	////		rysowanie funkcji przed obliczeniem pierwiastkow (poglad polozenia pierwsiatkow)
	//main_plot.plot_equation(funkcja, "Pogladowa funkcja");
	//for (int i = 0; i < dane.ilosc_przedzialow; i++)
	//{
	//	vector<int> x = { 0 };
	//	vector<int> y = { *dane.czestosci };
	//	main_plot.plot_xy(x, y, "Pogladowa funkcja");
	//}

	vector<double> x;
	vector<double> y;

	/*vector<double> x1;
	vector<double> y1;
	vector<double> x2;
	vector<double> y2;*/

	for (int i = 0; i < ilosc_przedzialow; i++) {
		x.push_back(dane_etykieta.getMin() + i*rozstep + rozstep / 2);
		y.push_back(czestosci[i]);
		//cout << "[" << x[i] << ", " << y[i] << "]" << endl;
	}

	//for (int i = 0; i < dan1.ilosc_przedzialow; i++) {
	//	x1.push_back(dan1.min + i*dan1.rozstep + dan1.rozstep / 2);
	//	y1.push_back(dan1.czestosci[i]);
	//	//cout << "[" << x[i] << ", " << y[i] << "]" << endl;
	//}

	//for (int i = 0; i < dan2.ilosc_przedzialow; i++) {
	//	x2.push_back(dan2.min + i*dan2.rozstep + dan2.rozstep / 2);
	//	y2.push_back(dan2.czestosci[i]);
	//	//cout << "[" << x[i] << ", " << y[i] << "]" << endl;
	//}


	//cout << dane11.size() << " " << dane12.size();


	//main_plot.plot_xy(x, y, "Pogladowa funkcja");
	main_plot.plot_xy(x, y, "Klasa C1");
	//main_plot.plot_xy(x2, y2, "Klasa C2");
	
}


void Histogram::dane_histogram (Data dane_etykieta) //na kopii
{	
	dane_etykieta.usuwanie_el_odstajacych(0.99);

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
				continue;
			}
		}
	}

}

Histogram::~Histogram()
{
}
