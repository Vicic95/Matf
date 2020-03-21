package gfStek;

public class Stek<T> implements GenerickiStek<T> {
	private class Cvor<G>{
        G vrednost;
        Cvor<G> sledeci;

        Cvor(G vrednost){
            this.vrednost = vrednost;
        }
        @Override
        public String toString(){
            return vrednost.toString();
        }
    }
    private Cvor<T> koren;

    public Stek(){   
    }
    @Override
    public T peek(){
        if (koren == null) {
            throw new Potkoracenje();
        }
        Cvor<T> c = koren;
        return c.vrednost;
    }
    @Override
    public T pop(){
        if (koren == null) {
            throw new Potkoracenje();
        }
        Cvor<T> c = koren;
        koren = koren.sledeci;
        return c.vrednost;
    }
    @Override
    public void push(T v){
        Cvor<T> c = new Cvor<>(v);
        c.sledeci = koren;
        koren = c;
    }
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append("[");
        Cvor<T> iterator = koren;
        while (iterator != null) {
            sb.append(iterator.vrednost).append(" ");
            iterator = iterator.sledeci;
        }
        sb.append("]");
        return sb.toString();
    }
}
