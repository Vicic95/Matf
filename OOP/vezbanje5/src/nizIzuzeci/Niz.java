package nizIzuzeci;

import java.util.Arrays;

public class Niz {
	private int[] niz;

	public Niz(int niz) {
		this.niz = new int[niz];
	}

	public Niz(int[] tmp) {
		this.niz = new int[tmp.length]; 
		for(int i=0;i<tmp.length;i++) {
			niz[i]=tmp[i];
		}
	}
	public int length() {
		return niz.length;
	}
	public int get(int i) {
		if(i<0 || i>niz.length)
			throw new ArrayIndexOutOfBoundsException("Pogresno indeksiranje");
		return niz[i];
	}

	@Override
	public String toString() {
		return "Niz :" + Arrays.toString(niz);
	}
	
}
