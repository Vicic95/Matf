package matIzraz;

public class Promenljiva extends Izraz {
	private String ime;
	private double vrednost;
	public Promenljiva(String ime,double vrednost) {
		this.ime=ime;
		this.vrednost=vrednost;
	}

	@Override
	public double izracunaj() {
		return vrednost;
	}

	public double getVrednost() {
		return vrednost;
	}

	public void setVrednost(double vrednost) {
		this.vrednost = vrednost;
	}

	public String getIme() {
		return ime;
	}

	@Override
	public String toString() {
		return ime;
	}
	
}
