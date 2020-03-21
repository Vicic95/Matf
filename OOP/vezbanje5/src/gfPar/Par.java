package gfPar;

public class Par<T1,T2> {
	private T1 a;
    private T2 b;

    public Par(T1 a, T2 b){
        this.a = a;
        this.b = b;
    }

    public T1 prvi(){
        return a;
    }

    public T2 drugi(){
        return b;
    }

    @Override
    public String toString(){
        return "(" + a + ", " + b + ")";
    }
}
