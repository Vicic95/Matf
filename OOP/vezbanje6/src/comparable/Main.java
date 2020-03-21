package comparable;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Main {
	public static void main(String[] args) {
		List<Tacka> tacke = new ArrayList<>();
		tacke.add(new Tacka(2, 3));
		tacke.add(new Tacka(10, 9));
		tacke.add(new Tacka(5, 1));
		tacke.add(new Tacka(-4, 11));
		tacke.add(new Tacka(100, 1));
		
		Collections.sort(tacke);
		System.out.println(tacke);
		
		Tacka t = new Tacka(5, 1);
		int k = Collections.binarySearch(tacke, t);
		if (k >= 0)
			System.out.println("Pronadjena je tacka " + tacke.get(k) + " na indeksu " + k);
		else
			System.out.println("Ne postoji tacka " + t);
	}
}
