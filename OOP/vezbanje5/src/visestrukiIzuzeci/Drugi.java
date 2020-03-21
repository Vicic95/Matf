package visestrukiIzuzeci;

import java.util.Scanner;

public class Drugi {
	public static void main(String[] args) {
		int x = 10;
		int[] a = {1, 2, 3, 4, 5};
		Scanner sc = null;

		try {
			sc.nextLine(); 	
			x = 10/0; 		
			x = a[20]; 		
		} catch (ArithmeticException | ArrayIndexOutOfBoundsException e) {
			System.out.println("Desila se ili greska 'ArithmeticException ili ArrayIndexOutOfBoundsException");
		} catch (Exception e) {
			System.out.println("Doslo je do neke greske koju ne znamo...");
			System.out.println("Greska: " + e.getMessage());
			
			e.printStackTrace();
		} finally {
			if (sc != null)
				sc.close();
		}
	}	
	private void imitiranjeCatchKonstrukcije(Exception e) {
		if (e instanceof ArithmeticException) {
			System.out.println("Greska pri racunanju.");
		} else if (e instanceof ArrayIndexOutOfBoundsException) {
			System.out.println("Lose indeksiranje niza!");
		} else /* if (e instanceof Exception */ {
			System.out.println("Ispaljen je nepoznat izuzetak");
		}
	}
}
