package nasledjivanje;

public class Tacka {
	private double x,y;
	private static int brojac =0;
	
	public Tacka() {
		this.x = 0;
		this.y = 0;
	}
	
	public Tacka(double x, double y) {
		this.x = x;
		this.y = y;
		brojac++;
	}
	public Tacka(Tacka t) {
		this.x=t.x;
		this.y=t.y;
	}
	public double getX() {
		return x;
	}

	public double getY() {
		return y;
	}
		
	public static int getBrojac() {
		return brojac;
	}
		
	public boolean equals(Tacka t) {
		return this.x==t.x && this.y==t.y;
	}
	public void transliranje(double tx,double ty) {
		this.x+=tx;
		this.y+=ty;
	}
	public double distanca(Tacka t) {
		return Math.sqrt((this.x-t.x)*(this.x-t.x)+(this.y-t.y)*(this.y-t.y));
	}

	@Override
	public String toString() {
		return x+","+y;
	}
}
