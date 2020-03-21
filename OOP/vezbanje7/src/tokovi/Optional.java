package tokovi;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Optional {
    public static java.util.Optional<Integer> sumaListe(List<Integer> xs) {
        java.util.Optional<Integer> suma = xs.stream().reduce((x1, x2) -> x1 + x2);
        return suma;
    }
    public static int proizvodListe(List<Integer> xs) {
       int proizvod = xs.stream().reduce(1, (x1, x2) -> x1*x2);
        return proizvod;
    }

    public static void main(String[] args) {
        List<Integer> xs = new ArrayList<>(
                Arrays.asList(1, 2, 3, 4, 5, 6)
        );

        java.util.Optional<Integer> suma = sumaListe(xs);
        if (suma.isPresent())
            System.out.println("Suma niza: " + suma.get());
        else
            System.out.println("Niz je prazan.");

        System.out.println("Proizvod liste: " + proizvodListe(xs));

    }
}
