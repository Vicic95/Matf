package geometrija;

public class Kvadrat extends Pravougaonik {

	public Kvadrat(Tacka c, double sirina) {
		super(c, sirina, sirina);
	}
	public double getDimenzijeStranice() {
		return getSirina();
	}
	@Override
	public String toString() {
		return "Kvadrat [centar: "+getCentar()+" a= "+getSirina()+"]";
	}
	
}
