package geometrija;


public class Main {
	public static void main(String[] args) {
		Kvadrat kvadrat = new Kvadrat(new Tacka(), 10);
		Pravougaonik pravougaonik = new Pravougaonik(new Tacka(10, 20), 100, 20);
		Trougao trougao = new Trougao(new Tacka(), new Tacka(20, 20), new Tacka(30, 30), new Tacka(10, 100));
		
		Elipsa elipsa = new Elipsa(new Tacka(10, 20), 10, 20);
		Krug krug = new Krug(new Tacka(1, 2), 16);
		
		Oblik[] oblici = {kvadrat, pravougaonik, trougao, elipsa, krug, new Pravougaonik(new Tacka(), 5, 7)};
		
		for (Oblik o: oblici) {
			System.out.println(o);
			System.out.println("O = " + o.getObim());
			System.out.println("P = " + o.getPovrsina() + "\n");
		}
		
		int brojacPravougaonika = 0;
		for (int i = 0; i < oblici.length; i++) {
			Oblik o = oblici[i];
			if (o instanceof Pravougaonik)
				brojacPravougaonika++;
		}
		
		System.out.println("Pronadjeno pravougaonika: " + brojacPravougaonika);
		
		brojacPravougaonika = 0;
		for (Oblik o: oblici)
			if (o.getClass() == Pravougaonik.class)
				brojacPravougaonika++;
		System.out.println("Pronadjeno pravougaonika: " + brojacPravougaonika);
	}
}
