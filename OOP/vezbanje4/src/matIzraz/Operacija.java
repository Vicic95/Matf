package matIzraz;

public abstract class Operacija extends Izraz {

	private Izraz levi,desni;
	public Operacija(Izraz levi,Izraz desni) {
		this.levi=levi;
		this.desni=desni;
	}

	@Override
	public double izracunaj() {
		return 0;
	}

	public Izraz getLevi() {
		return levi;
	}

	public Izraz getDesni() {
		return desni;
	}

}
