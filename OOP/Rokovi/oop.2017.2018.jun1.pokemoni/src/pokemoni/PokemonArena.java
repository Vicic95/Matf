package pokemoni;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.TextArea;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class PokemonArena extends Application {
    private static final String separator = "------------------------------------------------------------------------\n";
    public static void main(String[] args) {
        launch(args);
    }

    private static List<Pokemon> pokemoni = new ArrayList<>();
    private static Pokemon pokemon1 = null;
    private static Pokemon pokemon2 = null;

    

    @Override
    public void start(Stage primaryStage) throws Exception {
        VBox root = new VBox(10);
        root.setPadding(new Insets(10 , 10, 10, 10));
        Button btUcitaj = new Button("Ucitaj");
        TextArea taPokemoni = new TextArea();
        TextArea taBorba = new TextArea();

        RadioButton rbMagija1 = new RadioButton("Magija 1");
        rbMagija1.setSelected(true);
        RadioButton rbMagija2 = new RadioButton("Magija 2");
        Button btIzaberiMagiju = new Button("Izaberi magiju");
        ToggleGroup tg = new ToggleGroup();
        rbMagija1.setToggleGroup(tg);
        rbMagija2.setToggleGroup(tg);
        Button btSimuliraj = new Button("Simuliraj");

        HBox hbBottom = new HBox(10);
        hbBottom.getChildren().addAll(btIzaberiMagiju, btSimuliraj);

        root.getChildren().addAll(btUcitaj, taPokemoni, taBorba, rbMagija1, rbMagija2, hbBottom);

        Scene scene = new Scene(root, 600, 600);
        primaryStage.setTitle("Pokemon Arena");
        primaryStage.setScene(scene);
        primaryStage.show();
    }
}
