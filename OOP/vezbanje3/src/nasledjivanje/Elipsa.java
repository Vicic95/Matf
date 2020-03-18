package nasledjivanje;

public class Elipsa extends Oblik {
	protected double a,b;
	
	public Elipsa(Tacka c,double a,double b) {
		super(c);
		this.a=a;
		this.b=b;
	}
	public Elipsa(double x, double y,double a,double b) {
		super(x, y);
		this.a=a;
		this.b=b;
	}

	public Elipsa(double a,double b) {
		this.a=a;
		this.b=b;
	}
	public Elipsa(Elipsa s) {
		super(s.centar);
		s.a=a;
		s.b=b;
	}
	public double getA() {
		return a;
	}
	public double getB() {
		return b;
	}
	@Override
	public String toString() {
		return "Elipsa:" + a + "," + b;
	}
	
}
