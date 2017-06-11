package Klasyfikacja;

import java.util.*;

import weka.core.Instances;
import weka.core.converters.ConverterUtils;

public class Klasyfikacja {

	private Instances dane;
	//Atrybuty zbioru
	private int numInstances;
	private int numAttributes;
	private double[][] tab;
	private double[] zakresMin;
	private double[] zakresMax;
	//Wyniki z kSrednich
	private double[][] kSrednichSrodkiSkupien;
	private int kSrednichLiczbaSkupien;
	private int kSrednichIteracje;
	//Wyniki z gazuNeuronowego
	private double[][] gazNeuronowyWagi;
	
	//KONSTRUKTOR
	public Klasyfikacja(String plik) throws Exception {
		super();
		this.dane = ConverterUtils.DataSource.read(plik);
		numInstances = dane.numInstances();
		numAttributes = dane.numAttributes();
		
		double[][] tab = new double[numInstances][numAttributes];
		double[][] tempTab = new double[numAttributes][numInstances];
		
		for (int i=0; i<numAttributes; i++)
			if(dane.attributeStats(i).realCount > 0)
				tempTab[i] = dane.attributeToDoubleArray(i);
		
		for (int i=0; i<numInstances; i++) {
			for (int j=0; j<numAttributes; j++)
				tab[i][j] = tempTab[j][i];
		}
		
		this.tab = tab;
		
		//Wyznaczanie zakresMin i zakresMax
		double[] zakresMin = new double[numAttributes];
		double[] zakresMax = new double[numAttributes];
		
		for (int i=0; i<numAttributes; i++) {
			double maxValue = Double.MIN_VALUE;
			double minValue = Double.MAX_VALUE;
			for (int j=0; j<numInstances; j++) {
				if (tab[j][i] > maxValue)
					maxValue = tab[j][i];
				if (tab[j][i] < minValue)
					minValue = tab[j][i];
			}
			zakresMin[i] = minValue;
			zakresMax[i] = maxValue;
		}
		
		this.zakresMin = zakresMin;
		this.zakresMax = zakresMax;	

	}
	
	//GETERY
	public int getNumInstances() {
		return numInstances;
	}

	public int getNumAttributes() {
		return numAttributes;
	}

	public double[][] getTab() {
		return tab;
	}

	public double[] getZakresMin() {
		return zakresMin;
	}

	public double[] getZakresMax() {
		return zakresMax;
	}

	public double[][] getkSrednichSrodkiSkupien() {
		return kSrednichSrodkiSkupien;
	}

	public int getkSrednichLiczbaSkupien() {
		return kSrednichLiczbaSkupien;
	}

	public int getkSrednichIteracje() {
		return kSrednichIteracje;
	}
	
	public double[][] getGazNeuronowyWagi() {
		return gazNeuronowyWagi;
	}
	
	public void kSrednich(int liczbaSkupien, int maxIteracji) {
		
		//Wybieramy pierwsze srodki skupien (pierwsze kilka obserwacji)
		double[][] srodkiSkupien = new double[liczbaSkupien][numAttributes];
		for (int i=0; i<liczbaSkupien; i++)
			for (int j=0; j<numAttributes; j++)
				srodkiSkupien[i][j] = tab[i][j];
		
		//Tworzymy tablice - bêdzie nam ona mówi³a, który punkt nale¿y do którego skupienia
		int[] przynaleznosc = new int [numInstances];
		int[] przynaleznoscBefore = new int [numInstances]; //Do sprawdzenia czy pkt sie zamienily
		przynaleznoscBefore[0] = 1; //Zeby nam sie warunek w while przypadkowo nie sprawdzil odrazu
		
		//No i jedziemy iteracje
		double minDistance;
		double temp;
		int najmniejszaWartosc;
		int iteracja = 0;
		
		while (iteracja<maxIteracji && !Arrays.equals(przynaleznosc, przynaleznoscBefore)) {
			przynaleznoscBefore = Arrays.copyOf(przynaleznosc, przynaleznosc.length);
			
			//Sprawdzamy do ktorego punktu skupienia nam najblizej
			for (int i=0; i<numInstances; i++) {
				minDistance = Double.MAX_VALUE;
				najmniejszaWartosc = 0;
				for (int j=0 ; j<liczbaSkupien; j++) {
					temp = distance(numAttributes,tab[i],srodkiSkupien[j]);
					if (temp < minDistance) {
						minDistance = temp;
						najmniejszaWartosc = j;
					}
				}
				przynaleznosc[i] = najmniejszaWartosc;
			}
			
			//Teraz punkty skupienia ustalamy jako srednia z punktow do nich przynalezacych
			double[] buf = new double[numAttributes];
			int ilosc;
			
			for (int i=0; i<liczbaSkupien; i++) {
				Arrays.fill(buf, 0);
				ilosc = 0;
				for (int j=0; j<numInstances; j++) {
					if (przynaleznosc[j] == i) {
						for(int k = 0; k<numAttributes; k++) {
							buf[k] += tab[j][k];
						}
						ilosc++;
					}
				}
				if (ilosc!= 0) {
					for(int j = 0; j<numAttributes; j++)
						srodkiSkupien[i][j] = buf[j]/ilosc;
				}
			}
			
			//Odbyla sie iteracja
			iteracja++;
		}
		
		this.kSrednichIteracje = iteracja;
		this.kSrednichLiczbaSkupien = liczbaSkupien;
		this.kSrednichSrodkiSkupien = srodkiSkupien;
		
		//TESTY
		//for (int i=0; i<numInstances; i++) {
		//	for (int j=0; j<numAttributes; j++)
		//		System.out.print(tab[i][j] + " ");
		//	System.out.println("");
		//}
		//System.out.println("numInstances: " + numInstances);
		//System.out.println("numAttributes: " + numAttributes);
		//
		//for (int i=0; i<liczbaSkupien; i++) {
		//	for (int j=0; j<numAttributes; j++)
		//		System.out.print(srodkiSkupien[i][j] + " ");
		//	System.out.println("");
		//}
		//for (int i=0; i<numInstances; i++) {
		//	System.out.print(przynaleznosc[i] + " ");
		//}
		//System.out.println("");
		//System.out.println("iteracja: " + iteracja);
	}
	
	public void gazNeuronowy(int liczbaNeuronow, int maxIteracji) {
		//Inicjalizujemy neurony
		Neuron[] neurony = new Neuron[liczbaNeuronow];
		for (int i=0; i<liczbaNeuronow; i++) {
			neurony[i] = new Neuron(numAttributes,zakresMin,zakresMax);
			neurony[i].setLambdaMax((double)liczbaNeuronow/2);
		}
		
		int iteracje = 0;
		while (iteracje < maxIteracji) {
			//Kazdy punkt
			for (int i=0; i<numInstances; i++) {
				//Dla konkretnego punktu
				for (int j=0; j<liczbaNeuronow; j++) {
					//Liczymy dystans
					neurony[j].setDist(distance(numAttributes, tab[i], neurony[j].getWektorWag()));
				}
				Arrays.sort(neurony);
				
				for (int j=0; j<liczbaNeuronow; j++) {
					//Dokonujemy adaptacji
					neurony[j].updateWagi(tab[i], j, iteracje, maxIteracji);
					
				}
			}
			iteracje++;
		}
		
		double[][] temp = new double[liczbaNeuronow][numAttributes];
		
		for (int i=0; i<liczbaNeuronow; i++)
			temp[i] = neurony[i].getWektorWag();
		
		this.gazNeuronowyWagi = temp;
		
		
		//Testy
		for (int i=0; i<liczbaNeuronow; i++)
			System.out.println(neurony[i]);
		
		System.out.println(Arrays.toString(zakresMin));
		System.out.println(Arrays.toString(zakresMax));
		
	}
	
	
	private double distance(int dimension, double[] point1, double[] point2) {
		double d = 0;
		//Taka prawie ze euklidesowa, ale bez pierwiastka, bo szkoda procesora
		for (int i=0; i<dimension; i++) {
			d += (point1[i] - point2[i])*(point1[i] - point2[i]);
		}
		d = Math.sqrt(d); //Jakby jednak byla potrzebna pelna euklidesowa
		//d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2); // Euklidesowa do kwadratu
		//d = Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); // Euclidian
		//d = Math.abs(x1 - x2) + Math.abs(y1 - y2); // Manhattan
		//d = Math.pow(Math.pow(Math.abs(x1 - x2), p) + Math.pow(Math.abs(y1 - y2), p), (1 / p)); // Minkovski
	  	return d;
	}
}
