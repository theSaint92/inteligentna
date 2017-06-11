package Klasyfikacja;

import java.util.Arrays;

public class Neuron implements Comparable<Neuron> {
	private int wymiar;
	private double[] wektorWag;
	private Double dist; //Pomocnicza przy algorytmach

	private final double maxWspolczynnikUczenia = 0.8;
	private final double minWspolczynnikUczenia = 0.03;
	
	private final double lambdaMin = 0.01;
	private double lambdaMax;
	

	public Neuron(int wymiar, double[] zakresMin, double[] zakresMax) {
		this.wymiar = wymiar;
		double[] losowyWektor = new double[wymiar];
		for (int i = 0; i<wymiar; i++) {
			losowyWektor[i] = (Math.random()+0.5)/2.0; //Znormalizowany zakres 0.25 - 0.75
			losowyWektor[i] = (zakresMax[i]-zakresMin[i])*losowyWektor[i] + zakresMin[i];
		}
		this.wektorWag = losowyWektor;
	}
	
	public int getWymiar() {
		return wymiar;
	}
	
	public double[] getWektorWag() {
		return wektorWag;
	}
	
	public double getDist() {
		return dist;
	}

	public void setDist(double dist) {
		this.dist = dist;
	}
	
	public double getLambdaMax() {
		return lambdaMax;
	}

	public void setLambdaMax(double lambdaMax) {
		this.lambdaMax = lambdaMax;
	}

	private double wspolczynnikUczenia(int k, int kMax) {
		return this.maxWspolczynnikUczenia*Math.pow(this.minWspolczynnikUczenia/this.maxWspolczynnikUczenia, (double)k/kMax);
	}
	
	private double lambda(int k, int kMax) {
		return this.lambdaMax*Math.pow(this.lambdaMin/this.lambdaMax, k/kMax);
	}
	
	public void updateWagi(double[] x, int pozycja, int k, int kMax) {
		double etak = wspolczynnikUczenia(k, kMax);
		double gix = Math.exp(-pozycja/lambda(k,kMax));
		for (int i = 0; i<wymiar; i++) {
			wektorWag[i] = wektorWag[i] + etak*gix*(x[i] - wektorWag[i]);
		}
		//System.out.println("etak " + etak + " gix " + gix);
	}

	@Override
	public String toString() {
		return "Neuron [wymiar=" + wymiar + ", wektorWag="
				+ Arrays.toString(wektorWag) + ", dist=" + dist
				+ ", maxWspolczynnikUczenia=" + maxWspolczynnikUczenia
				+ ", minWspolczynnikUczenia=" + minWspolczynnikUczenia
				+ ", lambdaMin=" + lambdaMin + ", lambdaMax=" + lambdaMax + "]";
	}

	public int compareTo(Neuron n) {
		return this.dist.compareTo(n.dist);
	}


	
	
	
	
	
	
	
	
	
	
}
