package matIzraz;

public class Broj extends Izraz{
	private double vrednost;
	public Broj(double vrednost) {
		this.vrednost=vrednost;
	}
	public double izracunaj() {
		return vrednost;
	}
	public double getVrednost() {
		return vrednost;
	}
	@Override
	public String toString() {
		return "" + vrednost;
	}
	
}
