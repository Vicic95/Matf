package kolekcijeSet;

import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

public class Prvi {
	public static void main(String[] args) {
		Set<Integer> brojevi = new TreeSet<>();
			
		for (int i = 0; i < 100; i++)
			brojevi.add(i % 20);
			
		System.out.println("foreach iteracija kroz skup:");
		for (Integer i: brojevi)
			System.out.print(i + " ");
		System.out.println("\n");
			
		System.out.println("iterator iteracija kroz skup:");
		Iterator<Integer> i = brojevi.iterator();
		while (i.hasNext())
			System.out.print(i.next() + " ");
		System.out.println("\n");
			
	}	
}