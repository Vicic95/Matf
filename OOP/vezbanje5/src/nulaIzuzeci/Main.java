package nulaIzuzeci;

public class Main {
	public static void main(String[] args) {
		int x=10;
		try{
			System.out.println(x/0);
			System.out.println("Ova naredba se ne izvrsava.");
			System.out.println("A ni ova.");
			System.out.println("Razlog je sto izvrsavanje try bloka staje pri "
					+ "izbacivanju prvog izuzetka, i program nastavlja u jednom od "
					+ "navedenih catch blokova.");
		} catch(ArithmeticException e){
			System.err.println("Deljenje nulom!");	 		
	 		System.out.println("-----------------------------");
	 		System.err.println("e.getMessage(): " + e.getMessage());
	 		System.out.println("e.toString(): " + e.toString());
	 		System.out.println("e.getLocalizedMessage(): " + e.getLocalizedMessage());
	 		System.out.println("-----------------------------");
		}
	}
}
