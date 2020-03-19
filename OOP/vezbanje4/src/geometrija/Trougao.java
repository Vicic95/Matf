package geometrija;

public class Trougao extends Oblik {
	private Tacka a,b,c;
	public Trougao(Tacka centar,Tacka a,Tacka b,Tacka c) {
		super(centar);
		this.a=new Tacka(a);
		this.b=new Tacka(b);
		this.c= new Tacka(c);
	}

	public Trougao(Tacka a,Tacka b,Tacka c) {
		this.a=new Tacka(a);
		this.b=new Tacka(b);
		this.c= new Tacka(c);
	}
	public double getAB() {
		return a.distanca(b);
	}
	public double getAC() {
		return a.distanca(c);
	}
	public double getBC() {
		return b.distanca(c);
	}
	@Override
	public double getObim() {
		return getAB()+getAC()+getBC();
	}

	@Override
	public double getPovrsina() {
		double obim = getObim()/2;
		return Math.sqrt(obim*(obim-getAB())*(obim-getAC())*(obim-getBC()));
	}

	public Tacka getA() {
		return a;
	}

	public Tacka getB() {
		return b;
	}

	public Tacka getC() {
		return c;
	}

	@Override
	public String toString() {
		return "Trougao [centar: "+getCentar() + "A= " + a + " , B= " + b + " , C= " + c + "]";
	}
	
}
