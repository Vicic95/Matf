package nasledjivanje;

public class Krug extends Elipsa {

	public Krug(Tacka c, double a) {
		super(c, a, a);
	}

	public Krug(double x, double y, double a) {
		super(x, y, a, a);
	}

	public Krug(double a) {
		super(a, a);
	}

	public Krug(Krug s) {
		super(s.centar,s.a,s.a);
	}
	public double getPoluprecnik() {
		return this.a;
	}

	@Override
	public String toString() {
		return "Krug:" + a + ", centar=" + centar;
	}
	
}
