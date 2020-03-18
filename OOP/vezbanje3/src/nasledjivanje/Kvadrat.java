package nasledjivanje;

public class Kvadrat extends Pravougaonik {

	public Kvadrat(Tacka c, double a) {
		super(c, a, a);
	}


	public Kvadrat(double x, double y, double a) {
		super(x, y,a, a);
	}

	public Kvadrat(double a) {
		super(a, a);
	}

	public Kvadrat(Kvadrat p) {
		super(p.centar,p.sirina,p.sirina);
	}

	public double getDimenzija() {
		return this.sirina;
	}


	@Override
	public String toString() {
		return "Kvadrat:" + sirina + ", centar=" + centar;
	}
	
}
