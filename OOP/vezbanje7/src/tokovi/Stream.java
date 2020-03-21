package tokovi;

import java.util.Arrays;

public class Stream {
	public static void main(String[] args) {
        Arrays.asList("a1", "a2", "a3")
                .stream()
                .findFirst()
                .ifPresent(System.out::println);
        
        java.util.stream.Stream.of("a1", "a2", "a3")
                .findFirst()
                .ifPresent(System.out::println);
    }
}
