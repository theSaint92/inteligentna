package Klasyfikacja;

//import java.util.Arrays;
//import java.io.*;
//import java.util.*;


public class Zabawa {

	public static void main(String[] args) throws Exception {
		
		/* ================================================
		 * DEFINIUJEMY ZBIOR NA KTORYM DZIALAMY
		 * ================================================
		 */
		Klasyfikacja zab = new Klasyfikacja("./sampledata/attract_small.arff");
		
		
		/* ================================================
		 * EKSPERYMENT 1 - GRUPOWANIE OBIEKTOW - K-SREDNICH
		 * ================================================
		 * 
		 * W celu przeprowadzenia eksperymentu przeprowadzimy
		 * algorytmem k-srednich grupowanie zbioru na k=2..10
		 * podzbiorow. Dla kazdego k przeprowadzimy badanie 5
		 * razy i jako wynik badania dla danego k wezmiemy 
		 * srednia bledu kwantyzacji z tych 5 testow. 'Naj-
		 * lepsze k' zobrazujemy za pomocą Mozaiki Voronoia
		 * 
		 */
		
		System.out.println("=====================================================================================================");
		System.out.println("EKSPERYMENT 1");
		System.out.println("=====================================================================================================");
		int maxIteracji = 1000;
		int ileProb = 5;
		
		int najlepszeK = 0;
		double najlepszaKwantyzacja = Double.MAX_VALUE;
		for (int k=2; k<=10; k++) {
			System.out.print("Srodki skupien: " + k + "\tBledy kwantyzacji: ");
			double srednia = 0;
			for (int i=0; i<ileProb; i++) {
				zab.kSrednich(k, maxIteracji);
				double err = zab.getBladKwantyzacji();
				System.out.printf("%.3f ",err);
				srednia += err;
			}
			srednia /= ileProb;
			System.out.printf("\tSrednia z prob: %.3f\n", srednia);
			if (srednia < najlepszaKwantyzacja) {
				najlepszaKwantyzacja = srednia;
				najlepszeK = k;
			}
		}
		System.out.println("=====================================================================================================");
		System.out.printf("Najmniejszy blad kwantyzacji uzyskalismy dla k = " + najlepszeK + ". Wynosi on srednio  %.3f\n", najlepszaKwantyzacja);
		System.out.println("Rysunek został uzyskany po " + zab.getIteracje() + " iteracjach");
		System.out.println("=====================================================================================================");

		
		//Rysujemy Voronoia dla kSrednich
		zab.kSrednich(najlepszeK, maxIteracji);
		new Voronoi(zab.getZakresMin(),zab.getZakresMax(),zab.getSrodkiSkupien(),zab.getTab(), 1000 ).setVisible(true);
		
		/* ================================================
		 * EKSPERYMENT 2 - ALGORYTM GAZU NEURONOWEGO
		 * ================================================
		 * 
		 * W tym eksperymencie wykorzystamy algorytm gazu
		 * neuronowego do podzielenia przestrzeni na ilosc
		 * obszarow ktora okazala sie "zwycieska w poprzednim
		 * algorytmie. Wyniki te porownamy z wynikami z pop-
		 * rzedniego eksperymentu
		 * 
		 */
			
		System.out.println("=====================================================================================================");
		System.out.println("EKSPERYMENT 2");
		System.out.println("=====================================================================================================");
		zab.gazNeuronowy(najlepszeK, maxIteracji);
		new Voronoi(zab.getZakresMin(),zab.getZakresMax(),zab.getSrodkiSkupien(),zab.getTab(), 1000 ).setVisible(true);
		double kwantyzacjaNeuron = zab.getBladKwantyzacji();
		System.out.printf("Blad kwantyzacji dla algorytmu gazu neuronowego wynosi: %.3f\n", kwantyzacjaNeuron);
		System.out.println("=====================================================================================================");
		
		
		/* ================================================
		 * EKSPERYMENT 3 - ALGORYTM GAZU NEURONOWEGO
		 * ================================================
		 * 
		 * Powtarzamy algorytm k, przyjmujac jednakze zna-
		 * cznie wieksze k. Nastepnie zbior, bedacy wynikiem
		 * tego algorytmu  grupujemy znowu w k-zbiorow przy
		 * pomocy algorytmu k-srednich i wyniki te porownu-
		 * jemy z wynikami eksperymentu 1
		 * 
		 */
		
		System.out.println("=====================================================================================================");
		System.out.println("EKSPERYMENT 3");
		System.out.println("=====================================================================================================");
		zab.gazNeuronowy(najlepszeK*najlepszeK, maxIteracji);
		double kwantyzacja31 = zab.getBladKwantyzacji();
		System.out.printf("W pierwszym kroku podzielilismy na " + najlepszeK*najlepszeK + " obszarow. Blad kwantyzacji wynosi %.3f\n",  kwantyzacja31 );
		new Voronoi(zab.getZakresMin(),zab.getZakresMax(),zab.getSrodkiSkupien(),zab.getTab(), 1000 ).setVisible(true);
		double[][] zapisujemy = zab.getTab();
		double[][] srodkiSkupien = zab.getSrodkiSkupien();
		//Zastepujemy teraz nasze dane uzyskanymi srodkami skupien
		zab.setTab(srodkiSkupien);
		//Przeprowadzamy algorytm k-srednich
		zab.kSrednich(najlepszeK, maxIteracji);
		double kwantyzacja32 = zab.getBladKwantyzacji();
		System.out.printf("W drugim kroku podzielilismy otrzymany zbior na " + najlepszeK + " obszarow. Blad kwantyzacji dla tego kroku wynosi %.3f\n",  kwantyzacja32 );
		new Voronoi(zab.getZakresMin(),zab.getZakresMax(),zab.getSrodkiSkupien(),zab.getTab(), 1000 ).setVisible(true);
		//Przywracamy w tablicy stare dane
		zab.setTab(zapisujemy);
		new Voronoi(zab.getZakresMin(),zab.getZakresMax(),zab.getSrodkiSkupien(),zab.getTab(), 1000 ).setVisible(true);
		//I liczymy blad kwantyzacji dla ostatnich wynikow
		double kwantyzacja33 = zab.getBladKwantyzacji();
		System.out.printf("Blad kwantyzacji dla calego algorytmu 'mieszanego ;)' wynosi: %.3f\n",  kwantyzacja33 );
		System.out.println("=====================================================================================================");
		

	}

}
