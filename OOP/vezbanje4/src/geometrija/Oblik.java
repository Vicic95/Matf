package geometrija;

public abstract class Oblik {

	private Tacka centar;
	
	public Oblik(Tacka c) {
		this.centar = new Tacka(c);
	}
	public Oblik() {
		this.centar = new Tacka();
	}
	public Tacka getCentar() {
		return centar;
	}
	public abstract double getObim();
	public abstract double getPovrsina();
	@Override
	public String toString() {
		return "Oblik [centar=" + centar + "]";
	}
	

}
