package vezbanje2;

import java.util.Arrays;
import java.util.Scanner;

public class SotriranjePretraga {

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		System.out.println("duzina niza:");
		int n = sc.nextInt();
		int niz[] = new int[n];
		System.out.println("clanovi niza:");
		for(int i=0;i<n;i++) {
			niz[i]=sc.nextInt();
		}
		Arrays.sort(niz);
		System.out.println(Arrays.toString(niz));
		System.out.println("broj za pretragu niza:");
		int x = sc.nextInt();
		int i = Arrays.binarySearch(niz, x);
		if(i<0)
			System.out.println("nije clan niza:");
		else
			System.out.println("Na poziciji:"+i);
		System.out.println("Unesi broj za kreiranje niza:");
		int k = sc.nextInt();
		int niz2[]=new int[n];
		Arrays.fill(niz2, k);
		System.out.println(Arrays.toString(niz2));
		int a[] = Arrays.copyOfRange(niz2, 1, niz2.length-1);
		System.out.println(Arrays.toString(a));
		int b[] = Arrays.copyOf(niz2, niz2.length);
		System.out.println(Arrays.toString(b));
		sc.close();
	}

}
