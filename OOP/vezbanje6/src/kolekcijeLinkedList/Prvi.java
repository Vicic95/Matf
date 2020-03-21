package kolekcijeLinkedList;

import java.util.Arrays;
import java.util.LinkedList;

public class Prvi {
	public static void main(String[] args) {
		LinkedList<String> imena = new LinkedList<>(Arrays.asList("Blue ranger", "Red ranger", "White ranger", "Zordon", "Yellow ranger"));
		
		System.out.println("Sadrzaj liste (foreach petlja):");
		for (String ime: imena)
			System.out.print(ime + " ");
		System.out.println("\n");
		
		System.out.println("Sadrzaj liste (for):");
		for (int i = 0; i < imena.size(); i++)
			System.out.print(imena.get(i) + " ");
		System.out.println("\n");
			
		System.out.println("Sadrzaj liste (toString): ");
		System.out.println(imena);
		
		imena.addLast("Rita");
		imena.addFirst("Alpha 5");
		System.out.println("\nNakon dodavanja na pocetak i kraj: " + imena);
		imena.removeFirst();
		imena.removeLast();
		System.out.println("\nNakon uklanjanja sa pocetka i kraja: " + imena);

		System.out.println("\nNakon uklanjanja elementa: " + imena.get(3));
		imena.remove(3);
		System.out.println(imena);
	}
}
