package kolekcijeSet;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class Poligon {
	private Set<Tacka> temena;
	
	private Set<Tacka> napraviSkup() {
		return new TreeSet<>();
	}
	
	public Poligon() {
		temena = napraviSkup();
	}
	
	public Poligon(Tacka teme) {
		temena = napraviSkup();
		temena.add(new Tacka(teme));
	}
	
	public Poligon(double[][] koordinate) {
		temena = napraviSkup();
		for (double[] teme: koordinate)
			temena.add(new Tacka(teme[0], teme[1]));
	}
	public int getBrojTemena() {
		return temena.size();
	}
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		Iterator<Tacka> i = temena.iterator();
		while (i.hasNext())
			sb.append(i.next() + " ");
		return sb.toString();
	}
}
