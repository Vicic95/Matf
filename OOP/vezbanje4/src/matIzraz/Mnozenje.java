package matIzraz;

public class Mnozenje extends Operacija {

	public Mnozenje(Izraz levi, Izraz desni) {
		super(levi, desni);
	}
	public double izracunaj() {
		return getLevi().izracunaj()*getDesni().izracunaj();
	}
	@Override
	public String toString() {
		return getLevi() + " * " + getDesni();
	}
	
}
