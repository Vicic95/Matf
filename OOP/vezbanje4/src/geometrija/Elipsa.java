package geometrija;

public class Elipsa extends Oblik {
	private double a,b;
	public Elipsa(Tacka c,double a,double b) {
		super(c);
		this.a=a;
		this.b=b;
	}

	public Elipsa(double a,double b) {
		this.a=a;
		this.b=b;
	}
	
	@Override
	public double getObim() {
		double h=((a-b)*(a-b))/((a+b)*(a+b));
		return Math.PI*(a+b)*(1+1/4*h+1/64*h*h+1/256*h*h*h);
	}

	@Override
	public double getPovrsina() {
		return a*b*Math.PI;
	}

	public double getA() {
		return a;
	}

	public double getB() {
		return b;
	}

	@Override
	public String toString() {
		return "Elipsa [centar: "+getCentar()+" a= " + a + " , b= " + b + "]";
	}
	
}
