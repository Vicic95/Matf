package kolekcijeArrayList;

import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public class Prvi {
	public static void main(String[] args) {
		
		List<Integer> xs = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

		Collections.reverse(xs);
		System.out.println("Nakon obrtanja: ");
		Iterator<Integer> iterator = xs.iterator();
		while (iterator.hasNext())
			System.out.print(iterator.next() + " ");
		System.out.println();

		Collections.shuffle(xs);
		System.out.println("\nNakon mesanja elemenata:");
		System.out.println(xs + "\n");

		int i = 0, j = 5;
		Collections.swap(xs, i, j);
		System.out.println("Razmena elemenata na indeksima " + i + " i " + j);
		System.out.println(xs + "\n");

		Integer maksimum = Collections.max(xs);
		Integer minimum = Collections.min(xs);
		System.out.println("Maksimum: " + maksimum);
		System.out.println("Minimum: " + minimum);
		
		System.out.println("\nNakon rotacije za 3 mesta udesno:");
		Collections.rotate(xs, 3);
		System.out.println(xs);

		Collections.rotate(xs, -3);
		System.out.println("\nNakon rotacije za 3 mesta ulevo:");
		System.out.println(xs);

		Collections.sort(xs);
		System.out.println("\nNakon sortiranja\n" + xs);
	}
}
