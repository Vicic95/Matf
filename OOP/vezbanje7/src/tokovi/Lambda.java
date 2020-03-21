package tokovi;

import java.util.function.BinaryOperator;
import java.util.function.Function;

public class Lambda {
	static Integer square_f(Integer x){
        return x*x;
    }
    static Boolean even_f(Integer x){
        return x % 2 == 0;
    }
    static Integer add_f(Integer x, Integer y){
        return x + y;
    }

    public static void main(String[] args) {
        Function<Integer, Integer> square = x -> x*x;
        Function<Integer, Boolean> even = x -> x % 2 == 0;
        BinaryOperator<Integer> add = (x, y) -> x + y;

        System.out.println("2*2 = " + square.apply(2));
        System.out.println("2 is even: " + even.apply(2));
        System.out.println("2 + 3 = " + add.apply(2, 3));

        System.out.println();

        System.out.println("2*2 = " + square_f(2));
        System.out.println("2 is even: " + even_f(2));
        System.out.println("2 + 3 = " + add_f(2, 3));

    }
}
