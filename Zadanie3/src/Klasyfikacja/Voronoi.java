package Klasyfikacja;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Ellipse2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;
 
import javax.imageio.ImageIO;
import javax.swing.JFrame;
 
public class Voronoi extends JFrame {
	
	private static final long serialVersionUID = 1L;

	BufferedImage I;
	private final int BORDER_GAP = 20;

	
	public Voronoi(double minX, double maxX, double minY, double maxY, double[][] tablica,double[][] tablica2, int size ) {
		super("Voronoi Diagram");
		//setBounds(x, y, width, height) to specify the position and size of a GUI component 
		setBounds(5, 5, size, size+30);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		I = new BufferedImage(size, size, BufferedImage.TYPE_INT_RGB);
		Graphics2D g = I.createGraphics();
		
		
		/* ==========================
	     * DRAW VORONOI DIAGRAM
	     * ==========================
	     */
		Random rand = new Random();
		int[] color = new int[tablica.length];
		int[] px = new int[tablica.length];
		int[] py = new int[tablica.length];
		
		for (int i = 0; i < tablica.length; i++) {
			px[i] = convertToPixelCoords(tablica[i][0],minX,maxX,0,size);
			py[i] = convertToPixelCoords(tablica[i][1],minY,maxY,0,size);
			color[i] = rand.nextInt(16777215);
		}
		
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				int n = 0;
				for (byte i = 0; i < tablica.length; i++) {
					if (distance(px[i], py[i], x, y) < distance(px[n], py[n], x, y)) {
						n = i;
					}
				}
				I.setRGB(x, size - y-1, color[n]);
			}
		}
        
		/* ==========================
	     * PUT BASE POINTS ON DIAGRAM
	     * ==========================
	     */
		g.setColor(Color.BLACK);
		for (int i = 0; i < tablica.length; i++) {
			g.fill(new Ellipse2D .Double(px[i] - 2.5, size - py[i] - 2.5, 5, 5));
		}
		
		/* ====================
	     * PUT PROBE ON DIAGRAM
	     * ====================
	     */
		g.setColor(Color.white);
		
		int[] px2 = new int[tablica2.length];
		int[] py2 = new int[tablica2.length];
		
		for (int i = 0; i < tablica2.length; i++) {
			px2[i] = convertToPixelCoords(tablica2[i][0],minX,maxX,0,size);
			py2[i] = convertToPixelCoords(tablica2[i][1],minY,maxY,0,size);
		}
		
		g.setColor(Color.WHITE);
		for (int i = 0; i < tablica2.length; i++) {
			g.fill(new Ellipse2D .Double(px2[i] - 1.5, size - py2[i] - 1.5, 3, 3));
		}
		
	
		
		/* ===================
	     * CREATE X AND Y AXES
	     * ===================
	     */
		
		g.setColor(Color.WHITE);
		if(minY*maxY >= 0) { //Jezeli nie ma srodka w ukladzie to rysujemy oske na boku
			g.drawLine(BORDER_GAP,size-BORDER_GAP,size-BORDER_GAP,size - BORDER_GAP);
			
			double width = maxX - minX;
			double denomination = findDenomination(width);
			double start = Math.ceil(minX * 1/denomination)*denomination;
			
		    for (double i = start; i < maxX; i+=denomination) {
		    	int point = convertToPixelCoords(i, minX, maxX, 0, size);
		    	if (point >= BORDER_GAP && point <= size-BORDER_GAP) {
		    		g.drawLine(point, size - BORDER_GAP, point, size - BORDER_GAP - 10);
		    		if (i!=0.0)
		    			g.drawString(Double.toString(i), point, size - BORDER_GAP - 15);
		    	}
		    }
		}
		else { //Oske X rysujemy tam gdzie sie y zeruje czyli
			int p = size - convertToPixelCoords(0.0, minY, maxY, 0, size);
			g.drawLine(BORDER_GAP,p,size-BORDER_GAP,p);
			
			double width = maxX - minX;
			double denomination = findDenomination(width);
			double start = Math.ceil(minX * 1/denomination)*denomination;
			
		    for (double i = start; i < maxX; i+=denomination) {
		    	int point = convertToPixelCoords(i, minX, maxX, 0, size);
		    	if (point >= BORDER_GAP && point <= size-BORDER_GAP) {
		    		g.drawLine(point, p-10, point, p+10);
		    		if (i!=0.0)
		    			g.drawString(Double.toString(i), point,  p - 15);
		    	}
		    }
			
			
		}
		if(minX*maxX >= 0) {
			g.drawLine(BORDER_GAP,BORDER_GAP,BORDER_GAP,size - BORDER_GAP);
			
			double height = maxY - minY;
			double denomination = findDenomination(height);
			double start = Math.ceil(minY * 1/denomination)*denomination;
			
		    for (double i = start; i < maxY; i+=denomination) {
		    	int point = size - convertToPixelCoords(i, minY, maxY, 0, size);
		    	if (point >= BORDER_GAP && point <= size-BORDER_GAP) {
		    		g.drawLine(BORDER_GAP, point, BORDER_GAP + 10, point);
		    		if (i!=0.0)
		    			g.drawString(Double.toString(i), BORDER_GAP + 15, point);
		    	}
		    }
		}
		else {
			int p = convertToPixelCoords(0.0, minX, maxX, 0, size);
			g.drawLine(p,BORDER_GAP,p,size-BORDER_GAP);
			
			double height = maxY - minY;
			double denomination = findDenomination(height);
			double start = Math.ceil(minY * 1/denomination)*denomination;
			
			for (double i = start; i < maxY; i+=denomination) {
		    	int point = size - convertToPixelCoords(i, minY, maxY, 0, size);
		    	if (point >= BORDER_GAP && point <= size-BORDER_GAP) {
		    		g.drawLine(p-10, point, p + 10, point);
		    		if (i!=0.0)
		    			g.drawString(Double.toString(i), p + 15, point);
		    	}
		    }
		}
		
		//Wyrzucamy do png
		try {
			ImageIO.write(I, "png", new File("voronoi.png"));
		} catch (IOException e) {
 
		}
 
	}
 
	public void paint(Graphics g) {
		g.drawImage(I, 0, 30, this); //Ta powoduje ze pasek nam nie najezdza
	}
 
	double distance(double x1, double y1, double x2, double y2) {
		double d;
	    d = Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); // Euclidian
	//  d = Math.abs(x1 - x2) + Math.abs(y1 - y2); // Manhattan
	//  d = Math.pow(Math.pow(Math.abs(x1 - x2), p) + Math.pow(Math.abs(y1 - y2), p), (1 / p)); // Minkovski
	  	return d;
	}
	
	double findDenomination(double width) {
		double result = 1.0;
		
		int iteracje = 0;
		
		while (!(result*5 < width)) {
			if (iteracje%2 == 0) result /= 2.0;
			else if(iteracje%2 ==1) result /= 5.0;
			iteracje++;
			//result /= 10.0;
			
		}
		while (!(result*50 > width)) {
			if (iteracje%2 == 0) result *= 2.0;
			else if(iteracje%2 ==1) result *= 5.0;
			iteracje++;
			//result *= 10.0;
		}

		return result;
	}
	
	int convertToPixelCoords(double value, double minDouble, double maxDouble, int minInt, int maxInt) {
		int result;
		
		double maxWidthDouble = maxDouble - minDouble;
		double maxWidthInt = maxInt - minInt;
		
		double widthDouble = value - minDouble;
		
		result = (int)Math.round(widthDouble * maxWidthInt/maxWidthDouble);
		
		return result;
	}
}