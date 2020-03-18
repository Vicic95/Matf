package vezbanje1;

import java.util.Scanner;

public class ScannerPr {

	public static void main(String[] args) {
		Scanner s;
		s = new Scanner(System.in);
		System.out.println("Unesi ceo broj");
		if(s.hasNextInt()) {
			int x = s.nextInt();
			System.out.println("Broj:"+x);
		}
		else {
			System.out.println("Pogresan unos");
			System.exit(1);
		}
		System.out.println("Unesi realan broj:");
		if(s.hasNextDouble()) {
			double y = s.nextDouble();
			System.out.println("Broj:"+y);
		}
		else{
			System.out.println("Pogresan unos");
			System.exit(1);
		}
		System.out.println("Unesi string");
		String z = s.next();
		System.out.println("String:"+z);
		System.out.println("Unesi karakter");
		String tmp = s.next();
		char t = tmp.charAt(0);
		System.out.println("karakter:"+t);
		s.close();
		
	}

}
