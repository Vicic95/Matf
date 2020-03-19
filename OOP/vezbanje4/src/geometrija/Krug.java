package geometrija;

public class Krug extends Elipsa {

	public Krug(Tacka c, double r) {
		super(c, r, r);
	}

	public Krug(double r) {
		super(r, r);
	}
	public double getR() {
		return getA();
	}

	@Override
	public String toString() {
		return "Krug [centar: "+getCentar()+" getR()= " + getR() + "]";
	}
	
}
