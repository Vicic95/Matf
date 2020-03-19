package pCovek;


public class Main {
	public static void main(String[] args) {
		Covek c = new Covek("Petar", "Sojic", 25);
		c.zdravo();
		c.hello();
		
		Srpski s = c;
		s.dovidjenja();
		s.hvala();
		
		Engleski e= c;
		e.goodBye();
		e.hello();
		
		if (c instanceof Srpski)
			System.out.println("Klasa Covek implementira interfejs SrpskiJezik");
		if (c instanceof Engleski)
			System.out.println("Klasa Covek implementira interfejs EngleskiJezik");
	}

}
