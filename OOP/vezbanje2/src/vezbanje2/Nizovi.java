package vezbanje2;

import java.util.Scanner;

public class Nizovi {
	//moze i globalna:static Scanner sc = new Scanner(System.in);
	static int[] unos() {
		@SuppressWarnings("resource")
		Scanner sc2 = new Scanner(System.in);
		System.out.println("Unesite velicinu 2. niza:");
		int n = sc2.nextInt();

		System.out.println("Unesite elemente 2. niza:");
		int[] tmp = new int[n];
		for (int i = 0; i < n; i++)
			tmp[i] = sc2.nextInt();
		return tmp;
	}
	static void ispisi1(int[] niz) {
		for (int i = 0; i < niz.length; i++)
			System.out.print(niz[i] + " ");
		System.out.println();
	}
	static void ispisi2(int[] niz) {
		for (int e: niz)
			System.out.print(e + " ");
		System.out.println();
	}
	static void pomnoziKonstantom(int niz[],int c) {
		for(int i=0;i<niz.length;i++) {
			niz[i]=niz[i]*c;
		}
	}
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("uneti duzinu niza:");
		int n = sc.nextInt();
		int niz[] = new int[n];
		System.out.println("Uneti " +n+ " clanova niza");
		for(int i =0;i<n;i++) {
			niz[i]=sc.nextInt();
		}
		System.out.println("Niz:");
		for(int i=0;i<n-1;i++) {
			System.out.print(niz[i]+",");
		}
		System.out.println(niz[n-1]);
		System.out.println("Niz:");
		for(int e: niz) {
			System.out.print(e+" ");
		}
		System.out.println();
		int niz2[] = unos();
		ispisi1(niz2);
		ispisi2(niz2);
		System.out.println("uneti konstantu za mnozenje sa nizom");
		
		int c = sc.nextInt();
		
		pomnoziKonstantom(niz2,c);
		ispisi1(niz2);
		sc.close();
	}
}
