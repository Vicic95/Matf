package gfPar;

public class Main {
	public static void main(String[] args){
        Par<String, Integer> p = new Par<>("Python", 100);
        Par<String, Integer> q = dveVrednosti();
        System.out.println(p);
        System.out.println(q);
    }

    private static Par<String, Integer> dveVrednosti() {
        return new Par<>("Java", 80);
    }
}
