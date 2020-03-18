package vezbanje2;

import java.util.Arrays;
import java.util.Scanner;

public class Stringovi {

	public static boolean palindrom(String str){
        String bezBelinaMalaSlova = str.replace(" ", "").toLowerCase();
        
        return new StringBuilder(bezBelinaMalaSlova).reverse().toString().equals(bezBelinaMalaSlova);
    }
	public static void main(String[] args) {
		String str = "Hello world";
		System.out.println(str);
		String t = str + "?";
		System.out.println(t);
		if(str.equals(t))
			System.out.println("str==t");
		else
			System.out.println("str!=t");
		String t2 = "hEllO WorlD";
		if(str.equalsIgnoreCase(t2))
			System.out.println("str==t2 ignore case");
		else
			System.out.println("str!=t2");
			
		int i = str.compareTo(t2);
		if(i==0)
			System.out.println("str==t2");
		else if(i>0)
			System.out.println("str>t2");
		else
			System.out.println("str<t2");
		
		if(str == t)
            System.out.println("str i t su jedan isti string");
        else if(t.equals(str))
            System.out.println("t == str");
        else
            System.out.println("str != t");
		
		Scanner sc = new Scanner(System.in);
		System.out.println("Unesite liniju teksta");
		str = sc.nextLine();
		int brC=0,brS=0,brB=0;
		for(i=0;i<str.length();i++) {
			if(Character.isDigit(str.charAt(i)))
				brC++;
			else if(Character.isLetter(str.charAt(i)))
				brS++;
			else if(Character.isWhitespace(str.charAt(i)))
				brB++;
		}
		System.out.println("broj cifara: " + brC);
        System.out.println("broj slova: " + brS);
        System.out.println("broj belina: " + brB);
        char[] tmp = str.toCharArray();
        for (i = 0; i < tmp.length; i++)
            if (Character.isUpperCase(tmp[i]))
                tmp[i] = Character.toLowerCase(tmp[i]);
		//ili samo str.toLowerCase
        System.out.println("Mala slova :"+String.valueOf(tmp));
        str = str.toUpperCase();
        String strB = str.replace(" ", "");
        System.out.println("Velika slova bez belina: "+strB);
        
        System.out.println("Unesite prvo liniju stringa,a potom liniju podstringa za pretragu");
        str = sc.nextLine();
        String str2 = sc.nextLine();
        brB=0;
        i = str.indexOf(str2);
        while(i!=-1) {
        	brB++;
        	str=str.substring(i+str2.length());
        	i=str.indexOf(str2);
        }
        System.out.println("Ima "+brB+" podstringa");
        System.out.println(t);
        if(t.contains("Hello world"))
        	System.out.println("t sadrzi Hello world");
        else
        	System.out.println("t ne sadrzi Hello world");
        System.out.println("podskup nakon prvih 5 mesta:"+t.substring(5));
        System.out.println("podskup od 2 do 7 mesta: "+t.substring(2, 7));
        String p = "Hello";
        if(t.startsWith(p))
        	System.out.println("prefix za t je:"+p);
        else
        	System.out.println(p+" nije prefix za t");
        p = "World";
        if(t.endsWith(p))
        	System.out.println("sufix za t je:"+p);
        else
        	System.out.println("sufix za t nije:"+p);
        String[] p1 = t.split(" ");
        System.out.println("t smo razdvojili " + Arrays.toString(p1));
        char[] p2 = t.toCharArray();
        Arrays.sort(p2);
        String sorted = new String(p2);
        System.out.println("sortirano: "+sorted);
        
        StringBuilder sb = new StringBuilder();
        System.out.println("unosite reci sve dok ne unesete exit, tad se prekida");
        str = sc.next();
        while(!str.equals("exit")) {
        	
        	sb.append(str+" ");
        	str=sc.next();
        }
        str = sb.toString();
        System.out.println(str);
        str=sb.reverse().toString();
        System.out.println("obrnuto: "+str);
        System.out.println("duzina sb-a: "+sb.length());
        sb.setCharAt(0,'1');
        System.out.println("sa promenjenim karakterom na poziciji 0: "+sb);
        sb.setLength(0);
        sb.append("Hello").append(" ").append("world");
        System.out.println(sb);
        sb.insert(5, "ttt");
        System.out.println(sb);
        sb.delete(5, 8);
        System.out.println(sb);
        
        System.out.println("Unesite rec za proveru da li je palindrom");
        str = sc.next();
        if(palindrom(str))
        	System.out.println("Jeste palindrom");
        else
        	System.out.println("Nije palindrom");
        
        sc.close();
	}

}
