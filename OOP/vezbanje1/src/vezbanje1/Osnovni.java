package vezbanje1;

public class Osnovni {
	static int zbir(int x, int y) {
		return x+y;
	}
	static void ispisi(int x, int y) {
		System.out.println("x:"+x+" y:"+y+" Suma:"+zbir(x,y));
	}
	public static void main(String[] arg) {
		System.out.println("Hello world");
		int x = 1;
		int y = 2;
		int z = x+y;
		System.out.println(z);
		System.out.println(x+y);
		System.out.println("Suma:" + (x+y));
		String str = "Hello";
		str += " " + "world";
		System.out.println(str);
		int s = zbir(x,y);
		System.out.println("x:" + x + "y:"+ y +" Suma: "+s);
		System.out.println("x:" + x + "y:" + y +" Suma: "+zbir(x,y));
		System.out.printf("%d+%d=%d\n",x,y,zbir(x,y));
		System.out.format("%d+%d=%d\n",x,y,zbir(x,y));
		ispisi(x,y);
	}
}
