package instanceOf;

import java.util.Comparator;

public class Oblik implements Comparable<Oblik> {
	private Tacka centar;

    public Oblik(Tacka centar) {
        this.centar = centar;
    }

    public Tacka getCentar() {
        return centar;
    }

    public static final Comparator<Oblik> poredjenje = new Comparator<Oblik>() {
        @Override
        public int compare(Oblik o1, Oblik o2) {
            return poredjenjePomocnaFunkcija(o1, o2);
        }
    };
    @Override
    public int compareTo(Oblik o) {
        return poredjenjePomocnaFunkcija(this, o);
    }

    private static int poredjenjePomocnaFunkcija(Oblik o1, Oblik o2) {
        if(o1 instanceof Pravougaonik && o2 instanceof Pravougaonik) {
            Pravougaonik p1 = (Pravougaonik) o1;
            Pravougaonik p2 = (Pravougaonik) o2;
            
            if(p1.getA() != p2.getA()) {
                return Double.compare(p1.getA(), p2.getA());
            }
            else {
                return Double.compare(p1.getB(), p2.getB());
            }
        }
        else if (o1 instanceof Pravougaonik && o2 instanceof Krug) {
            return 1;
        }
        else if (o1 instanceof Krug && o2 instanceof Pravougaonik) {
            return -1;
        }
        else {
            Krug k1 = (Krug) o1;
            Krug k2 = (Krug) o2;
            return Double.compare(k1.getR(), k2.getR());
        }
    }
}
