package gfOpcionaVrednost;

public class Main {
	public static void main(String[] args){
        primer01();
        System.out.println("\n------------------------\n");
        primer02();
    }

    private static void primer01() {
        OpcionaVrednost<String> result = Poruka.procitajPoverljivuPoruku();
        if (result.postoji()) {
            System.out.println("Citanje je proslo uspesno! Sadrzaj:\n\n" + result.getVrednost());
        } else {
            System.out.println("Neuspelo citanje...");
        }
    }
    private static void primer02(){
        Integer[] xs = {1, 2, 3, 4, 100, 40, 20};
        OpcionaVrednost<Integer> maksX = nadjiMaksimum(xs);
        if (maksX.postoji()) {
            System.out.println("maksimum(xs) = " + maksX);
        } else {
            System.out.println("Prosledjen je prazan niz!");
        }
        Integer[] ys = {};
        OpcionaVrednost<Integer> maksY = nadjiMaksimum(ys);
        if (maksX.postoji()) {
            System.out.println("maksimum(ys) = " + maksY);
        } else {
            System.out.println("Prosledjen je prazan niz!");
        }
    }

    private static <T extends Comparable<T>> OpcionaVrednost<T> nadjiMaksimum(T[] xs)
    {
        if (xs.length == 0)
            return OpcionaVrednost.prazan();

        T maksimum = null;
        boolean first = true;
        for (T x: xs) {
            if (first) {
               maksimum = x;
               first = false;
            } else if (x.compareTo(maksimum) > 0) {
                maksimum = x;
            }
        }

        return OpcionaVrednost.od(maksimum);
    }
}
