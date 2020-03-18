package vezbanje1;

import java.util.Scanner;

public class RadSaBrojevima {
	static double toDegrees(double radians) {
		return (radians * 180)/Math.PI;
	}
	static double toRadians(double degs) {
		return (degs * Math.PI)/180;
	}
	static void Parni(int n) {
		for(int i=2;i<=n;i+=2) {
			System.out.println(i+" ");
		}
		System.out.println();
	}
	static int fibonaci(int x) {
		if(x==1 || x==2)
			return 1;
		else 
			return fibonaci(x-1) + fibonaci(x-2);
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int suma = 0,x=sc.nextInt();
		while(x!=0) {
			suma+=x;
			x=sc.nextInt();
		}
		System.out.println(suma);
		int n = sc.nextInt();
		Parni(n);
		int y = sc.nextInt();
		System.out.println(fibonaci(y));
		char z = ' ';
		if(sc.hasNext()) {
			String tmp = sc.next();
			z = tmp.charAt(0);
		}
		else {
			System.out.println("Pogrsan unos");
			System.exit(1);
		}
		System.out.println("Unet:"+z);
		if(Character.isUpperCase(z)) {
			System.out.println("Veliko slovo:"+z);
			System.out.println("Pretvaramo u malo slovo:"+Character.toLowerCase(z));
		}
		else if(Character.isLowerCase(z)) {
			System.out.println("Malo:"+z);
			System.out.println(" Pretvaramo u veliko:"+Character.toUpperCase(z));
		}
		else if(Character.isDigit(z)) {
			System.out.println("cifra:"+z);
			int k = Character.getNumericValue(z);
			System.out.println("Num vrednost"+k);
		}
		System.out.println("Ugao u stepenima:");
		double ugao = sc.nextDouble();
		ugao = toRadians(ugao);
		//Postoji i ugradjena funkcija Math.toRadians(ugao)
		System.out.println("Ugaou radijanima: "+ugao);
		System.out.println("sinus:" +Math.sin(ugao));
		System.out.println("cosinus:" +Math.cos(ugao));
		System.out.println("tangens: "+Math.tan(ugao));
		System.out.println("cotangens: "+1/Math.tan(ugao));
		System.out.println("Unesite realan broj:");
		double r = sc.nextDouble();
		System.out.println(Math.sqrt(Math.pow(r, 7)));
		sc.close();
		
	}

}
