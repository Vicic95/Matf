package matIzraz;

public class Sabiranje extends Operacija {

	public Sabiranje(Izraz levi, Izraz desni) {
		super(levi, desni);
		
	}
	public double izracunaj() {
		return getLevi().izracunaj() + getDesni().izracunaj();
	}
	@Override
	public String toString() {
		return getLevi() + " + " + getDesni();
	}
	
}
