package CitanjePisanje;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.List;

public class CitanjeIPisanje {
	public static void main(String[] args) {
		Path ulaznaPutanja = Paths.get("input.txt");
		System.out.println("path.toString() = " + ulaznaPutanja/*.toString()*/);
		
		System.out.println("Ime datoteke: " + ulaznaPutanja.getFileName());
		System.out.println("Parent putanje: " + ulaznaPutanja.getParent());
		System.out.println("Root: " + ulaznaPutanja.getRoot());
		System.out.println("Apsolutna putanja: " + ulaznaPutanja.toAbsolutePath().toString());
		System.out.println();
		try {
			List<String> linije = Files.readAllLines(ulaznaPutanja, StandardCharsets.UTF_8);
			System.out.println("Sadrzaj datoteke:" + ulaznaPutanja.toAbsolutePath());
			for (String linija: linije)
				System.out.println(linija);
		} catch (IOException e) {
			System.err.println("Neuspelo otvaranje ulazne datoteke!");
			e.printStackTrace();
		} 
		Path izlaznaPutanja = Paths.get("output.txt");
		System.out.println("\nPisemo u datoteku: " + izlaznaPutanja.toAbsolutePath());
		List<String> linije;
		linije = Arrays.asList("Zdravo", " ", "svete", "!");

		try {
			Files.write(izlaznaPutanja, linije, StandardOpenOption.APPEND);
			System.out.println("Sadrzaj je uspesno upisan!");

		} catch (IOException e) {
			System.err.println("Neuspelo pisanje u datotekU!");
			e.printStackTrace();
		}
	}
}
