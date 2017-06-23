package Klasyfikacja;

public class Distance {
	
	public static double getDistance(int dimension, double[] point1, double[] point2) {
		double d = 0;
		
		//Euklidesowa do kwadratu
		//for (int i=0; i<dimension; i++) {
		//	d += (point1[i] - point2[i])*(point1[i] - point2[i]);
		//}
		
		//Euklidesowa
		for (int i=0; i<dimension; i++) {
			d += (point1[i] - point2[i])*(point1[i] - point2[i]);
		}
		d = Math.sqrt(d); 
		
		//Manhattan
		//for (int i=0; i<dimension; i++) {
		//	d += Math.abs(point1[i] - point2[i]);
		//}
		
		//Czebyszew
		//for (int i=0; i<dimension; i++) {
		//  double temp = Math.abs(point1[i] - point2[i]);
		//  if (d < temp) {
		//	  d = temp;
		//  }	
		//}
		
		
		//Minkovski of order p
		//double p = 4;
		//for (int i=0; i<dimension; i++) {
		//	d += Math.pow(Math.abs(point1[i] - point2[i]), p);
		//}
		//d = Math.pow(d, 1/p);
	
		return d;
	}

}
