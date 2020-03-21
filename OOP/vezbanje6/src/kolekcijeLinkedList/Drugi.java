package kolekcijeLinkedList;

import java.util.Iterator;
import java.util.LinkedList;

public class Drugi {
	public static void main(String[] args) {
		LinkedList<String> imena = new LinkedList<>();
		imena.add("Zdravo");
		imena.add("svete");
		imena.add("kako");
		imena.add("si");
		imena.add("?");
		
		Iterator<String> iter = imena.iterator();
		while (iter.hasNext()) {
			String e = iter.next();
			System.out.println(e);
		}
	}
}
