package TackaP;

public class Main {

	public static void main(String[] args) {
		Tacka t1 = new Tacka(0, 0);
		Tacka t2 = new Tacka(2, 2);
		
		System.out.println(t1.toString());
		System.out.println(t2.toString());
		
		t1.transliranje(2, 2);
		if (t1.equals(t2))
			System.out.println("t1 == t2");
		else
			System.out.println("t1 != t2");
		
		t1.transliranje(-2, -2);
		double d = t1.distanca(t2);
		System.out.println("d(t1, t2) = " + d);
		Tacka p = t2;
		Tacka r = new Tacka(t2);
		System.out.println(p.toString()+r.toString());
		System.out.println("Ukupno instancirano: "+Tacka.getBrojac());
	}

}
