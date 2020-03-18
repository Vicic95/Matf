package nasledjivanje;


public class Trougao extends Oblik {
	private Tacka a,b,c;
	
	public Trougao(Tacka centar,Tacka a,Tacka b,Tacka c) {
		super(centar);
		this.a=new Tacka(a);
		this.b=new Tacka(b);
		this.c=new Tacka(c);
	}

	public Trougao(Tacka centar, double a1, double a2, double b1, double b2, double c1, double c2) {
		super(centar);
		this.a=new Tacka(a1,a2);
		this.b=new Tacka(b1,b2);
		this.c=new Tacka(c1,c2);
	}

	public Trougao(double a1, double a2, double b1, double b2, double c1, double c2) {
		this(0, 0, a1, a2, b1, b2, c1, c2);
	}
	
	public Trougao(double x1, double x2, double a1, double a2, double b1, double b2, double c1, double c2) {
		super(x1, x2);
		this.a=new Tacka(a1,a2);
		this.b=new Tacka(b1,b2);
		this.c=new Tacka(c1,c2);
	}

	public Trougao(Tacka a,Tacka b,Tacka s) {
		this.a=new Tacka(a);
		this.b=new Tacka(b);
		this.c=new Tacka(c);
	}

	public Tacka getA() {
		return a;
	}

	public Tacka getB() {
		return b;
	}

	public Tacka getC() {
		return c;
	}
	public double getAB() {
		return a.distanca(b);
	}
	public double getAC() {
		return a.distanca(c);
	}
	public double getBC() {
		return b.distanca(c);
	}

	@Override
	public String toString() {
		return "Trougao"+a+","+b+","+c;
	}
	
}
