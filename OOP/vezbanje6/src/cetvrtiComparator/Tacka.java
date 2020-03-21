package cetvrtiComparator;

import java.util.Comparator;

public class Tacka {
	private int x, y;

    public final static Comparator<Tacka> poredi =
            (o1, o2) -> o1.getX() != o2.getX() ?
                    Integer.compare(o1.getX(), o2.getX()):
                    Integer.compare(o1.getY(), o2.getY());

    public final static Comparator<Tacka> poredi2 =
            (o1, o2) -> o1.getY() != o2.getY() ?
                    Integer.compare(o1.getY(), o2.getY()):
                    Integer.compare(o1.getX(), o2.getX());
    
    public Tacka(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getX() {
        return x;
    }
    public int getY() {
        return y;
    }

    @Override
    public String toString() {
        return "(" + x + ", " + y + ")";
    }
}
