package pCovek;

public class Covek implements Srpski,Engleski{
	private String ime,prezime;
	private int godina;
	
	
	public Covek(String ime, String prezime, int godina) {
		super();
		this.ime = ime;
		this.prezime = prezime;
		this.godina = godina;
	}
	
	@Override
	public void hello() {
		System.out.println("hello");
	}
	@Override
	public void goodBye() {	
		System.out.println("goodbye");
	}
	@Override
	public void thanks() {
		System.out.println("thanks");
		
	}
	@Override
	public void zdravo() {
		System.out.println("zdravo");
		
	}
	@Override
	public void dovidjenja() {
		System.out.println("dovidjenja");
		
	}
	@Override
	public void hvala() {
		System.out.println("hvala");
		
	}

	public String getIme() {
		return ime;
	}

	public String getPrezime() {
		return prezime;
	}

	public int getGodina() {
		return godina;
	}

	@Override
	public String toString() {
		return ime + prezime + godina;
	}

}
