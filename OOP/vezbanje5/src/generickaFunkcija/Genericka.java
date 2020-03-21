package generickaFunkcija;

public class Genericka {
	public static <T> void print(T a)
    {
        System.out.println(a.toString());
    }
    public static void main(String[] args)
    {
        print(5);
        print("Hello world");
        print(new Tacka(2, 3));
    }
}
