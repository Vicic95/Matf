package Student;

public class Main {
	public static void main(String[] args) {
		InfoStudent s1 = new InfoStudent("M", "Matematic", "mm0012016", 10.0);
		InfoStudent s2 = new InfoStudent("N", "Numerovic", "mn3142014", 9.5);
		InfoStudent s3 = new InfoStudent("V", "Verovatnic", "mv3142015", 8.5);
		InfoStudent s4 = new InfoStudent("N", "Nastavnic", "ml3142014", 9.5);
		InfoStudent s5 = new InfoStudent("R", "Racunalo", "mr3142017", 9.7);
		InfoStudent s6 = new InfoStudent("I", "Informatikovic", "mi3142015", 9.7);
		InfoStudent s7 = new InfoStudent("A", "Afikic", "af3142014", 8.5);
		InfoStudent s8 = new InfoStudent("A", "Ainformatikovic", "ai3142014", 8.5);
		
		InfoStudent[] studenti = {s1, s2, s3, s4, s5, s6, s7, s8};
		for (InfoStudent student : studenti)
			System.out.println(student.toString());
	}
}
