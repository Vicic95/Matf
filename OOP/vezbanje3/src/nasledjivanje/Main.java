package nasledjivanje;

public class Main {
	public static void main(String[] args) {
		
		Pravougaonik pravougaonik = new Pravougaonik(10, 20, 100, 200);
		Kvadrat kvadrat = new Kvadrat(new Tacka(2, 3), 40);
		Krug krug = new Krug(40);
		Elipsa elipsa = new Elipsa(new Tacka(), 11, 42);
		Trougao trougao = new Trougao(10, 10, 20, 20, 40, 40);
		
		System.out.println(pravougaonik);
		System.out.println(kvadrat);
		System.out.println(krug);
		System.out.println(elipsa);
		
		Tacka centar = krug.getCentar();
		System.out.println("\nKrug se nalazi u tacki " + centar);
		
		System.out.println("\nDuzine stranice trougla: AB = " + trougao.getAB() + " BC = " + trougao.getBC()+ " AC = " + trougao.getAC());
		Tacka c1 = new Tacka(krug.getCentar());

		krug.getCentar().transliranje(10, 20);
		Tacka c2 = krug.getCentar();
		System.out.println("\nKrug je tranisliran iz " + c1 + " u " + c2 + " koristeci vektor (10, 20)");
		
	    double dist = krug.getCentar().distanca(kvadrat.getCentar());
		System.out.println("\nRastojanje izmedju " + krug + " i " + kvadrat + " je " + dist);
	}
}
