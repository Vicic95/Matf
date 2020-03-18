package Student;

public class InfoStudent {
	private String ime,prezime,indeks;
	private double prosek;
	public InfoStudent(String ime, String prezime, String indeks, double prosek) {
		this.ime = ime;
		this.prezime = prezime;
		this.indeks = indeks;
		this.prosek = prosek;
	}
	public String getIme() {
		return ime;
	}
	public String getPrezime() {
		return prezime;
	}
	public String getIndeks() {
		return indeks;
	}
	public double getProsek() {
		return prosek;
	}
	public int getGodinaUpisa() {
		String tmp = "20"+indeks.charAt(7)+indeks.charAt(8);
		return Integer.parseInt(tmp);
	}
	public int getBrojIndeksa() {
		String tmp = "" + indeks.charAt(2)+indeks.charAt(3)+indeks.charAt(4);
		return Integer.parseInt(tmp);
	}
	public String getSmer() {
		char studije = indeks.charAt(0);
		char smer = indeks.charAt(1);
		if (studije == 'm')
			switch (smer) {
				case 'm': return "Teorijska matematika";
				case 'n': return "Primenjena matematika";
				case 'v': return "Statistika i aktuarska i finansijska matematika";
				case 'l': return "Profesor matematike i racunarstva";
				case 'r': return "Racunarstvo i informatika";
				case 'i': return "Informatika";
				default:  return "Nepoznat smer...";
			}
		else if (studije == 'a' && smer == 'f')
			return "Astrofizika";
		else if (studije == 'a' && smer == 'i')
			return "Astroinformatika";
		else
			return "Nepoznat smer";
	}
	public void setProsek(double prosek) {
		this.prosek = prosek;
	}
	@Override
	public String toString() {
		return "InfoStudent: "+ime+" "+prezime+", "+prosek+", "+getBrojIndeksa()+","+getGodinaUpisa()+","+getSmer();
	}
	

}
