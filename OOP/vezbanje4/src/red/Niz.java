package red;

public class Niz implements Red {
	private int kapacitet=1025;
	private int[] elementi = new int[kapacitet];
	private int pocetak,kraj,Brojac;
	@Override
	public void add(int x) {
		if (Brojac== kapacitet-1) {
			System.err.println("Queue overflow!");
			return;
		}
		elementi[kraj] = x;
		Brojac++;
		kraj = (kraj + 1) % kapacitet;
	}
	@Override
	public int remove() {
		if (Brojac == 0) {
			System.err.println("Queue underflow!");
			return 0;
		}
		int tmp = elementi[pocetak];
		pocetak = (pocetak + 1) % kapacitet;
		Brojac--;
		return tmp;
	}
	@Override
	public int head() {
		if (Brojac == 0) {
			System.err.println("Queue underflow!");
			return 0;
		}
		return elementi[pocetak];
	}
	@Override
	public int back() {
		if (Brojac == 0) {
			System.err.println("Queue underflow!");
			return 0;
		}
		if (kraj == 0)
			return elementi[kapacitet-1];
		else
			return elementi[kraj-1];
	}
	@Override
	public int size() {
		return Brojac;
	}
	@Override
	public void show() {
		System.out.print("[ ");
		
		int i = pocetak;
		while (i != kraj) {
			System.out.print(elementi[i] + " ");
			i = (i + 1) % kapacitet;
		}
		System.out.println("]");
	}
}
