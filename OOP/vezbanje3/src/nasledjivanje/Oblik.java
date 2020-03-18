package nasledjivanje;

public class Oblik {
	protected Tacka centar;

	public Oblik(Tacka c) {
		this.centar = new Tacka(c);
	}
	public Oblik(Oblik o) {
		this(o.centar);
	}
	public Oblik(double x, double y) {
		this.centar = new Tacka(x, y);
	}
	public Oblik() {
		this.centar = new Tacka();
	}
	public Tacka getCentar() {
		return centar;
	}
	@Override
	public String toString() {
		return "Oblik" + centar;
	}
	
}
