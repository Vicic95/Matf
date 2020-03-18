package vezbanje2;

import java.util.Scanner;

public class matrice {
	static void razmeni(int a[][],int i,int j) {
		int tmp[] = a[i];
		a[i]=a[j];
		a[j]=tmp;
	}
	static void ispisi(int niz[][]) {
		for(int i=0;i<niz.length;i++) {
			for(int j=0;j<niz[i].length;j++) {
				System.out.print(niz[i][j]+" ");
			}
			System.out.println();
		}
	}
	public static void main(String[] args) {
		Scanner sc =new Scanner(System.in);
		System.out.println("Unesi dimenzije matrice");
		int n = sc.nextInt();
		int m = sc.nextInt();
		System.out.println("Unesi clanove matrice");
		int niz[][] = new int[n][m];
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				niz[i][j]=sc.nextInt();
			}
		}
		for(int i=0;i<n;i++) {
			for(int j=0;j<m;j++) {
				System.out.print(niz[i][j]+" ");
			}
			System.out.println();
		}
		System.out.println("Unesi vrste za razmenu");
		int i = sc.nextInt();
		int j = sc.nextInt();
		if (i < 0 || i >= niz.length || j < 0 || j >= niz.length) {
			System.out.println("Indeks vrste more biti izmedju 0 i " + (niz.length-1));
			System.exit(1);
		}
		razmeni(niz,i,j);
		ispisi(niz);
		sc.close();
	}
}
