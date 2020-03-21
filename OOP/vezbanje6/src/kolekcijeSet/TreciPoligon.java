package kolekcijeSet;

public class TreciPoligon {
	public static void main(String[] args) {
		double[][] t = {
			{1, 2}, {3, 4.5}, {9, 1.1},
			{11.2, 13.1}, {1, 2}, {1, 2},
			{1, 2}, {1, 2}, {3, 4.5}
		};		
		Poligon p = new Poligon(t);
		System.out.println(p);	
	}
}
