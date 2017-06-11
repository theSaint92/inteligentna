package Klasyfikacja;

//import java.util.Arrays;
//import java.io.*;
//import java.util.*;


public class Zabawa {

	public static void main(String[] args) throws Exception {
	
		args[0] = "./sampledata/attract_small.arff";
		Klasyfikacja zab = new Klasyfikacja(args[0]);
		zab.kSrednich(80, 1000);
		zab.gazNeuronowy(5, 1000);
		
		//double minX = -5;
		//double maxX = 5;
		//double minY = -5;
		//double maxY = 5;
	    //
		//int rozmiar = 50;
		//int rozmiarWiekszy = 1000;
		//double[][] tablica = new double[rozmiar][2];
		//for(int i=0; i<rozmiar; i++)
		//	for(int j=0; j<2; j++)
		//		tablica[i][j] = Math.random()*10-5;
		//for(int i=0; i<rozmiar;i++)
		//	System.out.println(Arrays.toString(tablica[i]));
		//
		//double[][] tab2 = new double[rozmiarWiekszy][2];
		//for(int i=0; i<rozmiarWiekszy; i++)
		//	for(int j=0; j<2; j++)
		//		tab2[i][j] = Math.random()*10-5;

		
		//Rysujemy Voronoia dla kSrednich
		new Voronoi(zab.getZakresMin()[0],zab.getZakresMax()[0],zab.getZakresMin()[1],zab.getZakresMax()[1],zab.getkSrednichSrodkiSkupien(),zab.getTab(), 1000).setVisible(true);
	
		new Voronoi(zab.getZakresMin()[0],zab.getZakresMax()[0],zab.getZakresMin()[1],zab.getZakresMax()[1],zab.getGazNeuronowyWagi(),zab.getTab(), 1000).setVisible(true);	
	}

}
