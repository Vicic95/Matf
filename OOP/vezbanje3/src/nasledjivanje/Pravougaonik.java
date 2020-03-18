package nasledjivanje;

public class Pravougaonik extends Oblik {
	protected double sirina,visina;
	
	public Pravougaonik(Tacka c,double sirina,double visina) {
		super(c);
		this.sirina=sirina;
		this.visina=visina;
	}
	public Pravougaonik(Oblik o) {
		super(o);
	}
	public Pravougaonik(double x, double y, double sirina, double visina) {
		super(x, y);
		this.sirina=sirina;
		this.visina=visina;
	}
	public Pravougaonik( double sirina, double visina) {
		this.sirina=sirina;
		this.visina=visina;
	}
	public Pravougaonik(Pravougaonik p) {
		super(p.centar);
		p.sirina=sirina;
		p.visina=visina;
	}
	public double getSirina() {
		return sirina;
	}
	public double getVisina() {
		return visina;
	}
	@Override
	public String toString() {
		return "Pravougaonik: " + sirina + "," + visina;
	}
	
}
