package hashMap;

public class Osoba {
	private String ime;
	private String prezime;

	public Osoba(String ime, String prezime){
		this.ime = ime;
		this.prezime = prezime;
	}
	public String toString(){
		return ime + " " + prezime;
	}
	public boolean equals(Object osoba){
		return prezime.compareTo(((Osoba) osoba).prezime) == 0 &&
				ime.compareTo(((Osoba) osoba).ime) == 0;
	}
	public int hashCode(){
		return 7*ime.hashCode() + 13*prezime.hashCode();
	}
}
