package hashMap;

import java.util.HashMap;
import java.util.Map;

public class Imenik {
	public static void main(String[] args){	
		HashMap<Osoba, String> imenik = new HashMap<>();
		imenik.put(new Osoba("Ana", "Anic"), "0611234567");
		imenik.put(new Osoba("Jovan", "Jovanovic"), "0659876543");
		imenik.put(new Osoba("Bojana", "Bojanic"), "062345678");
		imenik.put(new Osoba("Pavle", "Pavlovic"), "0645678901");

		imenik.put(new Osoba("Ana", "Anic"), "0612233445");

		for(Map.Entry<Osoba, String> unos : imenik.entrySet()) {
			System.out.println(unos.getKey() + ": " + unos.getValue());
		}
	}
}
