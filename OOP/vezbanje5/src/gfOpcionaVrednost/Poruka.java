package gfOpcionaVrednost;

import java.util.Random;

public class Poruka {
	private static Random random = new Random();

    public static OpcionaVrednost<String> procitajPoverljivuPoruku(){
        double d = random.nextDouble();
        String sadrzaj;
        if (d < 0.5) {
            sadrzaj = "U dobru je lako dobar biti,\n" +
                    "na muci se poznaju junaci!";
        } else {
            sadrzaj = null;
        }
        return OpcionaVrednost.odMozdaNepostojece(sadrzaj);
    }
}
