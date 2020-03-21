package javaFX;

import java.util.Random;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class javaFXAnagram extends Application{

	public static void main(String[] args) {
		launch(args);
	}	
	private static String izracunajAnagram(String s) {
		char[] tmp = s.toCharArray();
		Random rand = new Random();
		for (int i = 0; i < tmp.length; i++) {
			int k = rand.nextInt(tmp.length);
			
			char helper = tmp[i];
			tmp[i] = tmp[k];
			tmp[k] = helper;
		}
		
		return String.valueOf(tmp);
	}

	public void start(Stage primaryStage) {
		VBox root = new VBox(10);
		
		HBox hbTop = new HBox(10);
		VBox vbLevi = new VBox(10);
		VBox vbDesni = new VBox(10);
		vbLevi.setPadding(new Insets(10, 0, 0, 10));
		vbDesni.setPadding(new Insets(10, 10, 0, 0));
		hbTop.getChildren().addAll(vbLevi, vbDesni);
		
		Label lblIme = new Label("Unesite Vase ime:");
		TextField tfUnos = new TextField();
		vbLevi.getChildren().addAll(lblIme, tfUnos);

		Button btnUnos = new Button("Potvrdi");
		Button btnOcisti = new Button("Ocisti");
		Button btnIzadji = new Button("Izadji");
		vbDesni.getChildren().addAll(btnUnos, btnOcisti, btnIzadji);

		Label lblIspis = new Label("Ispis: ");
		TextArea taIspis = new TextArea();
		Label lblPoruka = new Label();
		lblPoruka.setTextFill(Color.RED);
		
		root.getChildren().addAll(hbTop, lblIspis, taIspis, lblPoruka);
		Scene scene = new Scene(root, 400, 400);
		primaryStage.setScene(scene);
		primaryStage.setTitle("Anagrami");
		
		btnUnos.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String korisnikiUnos = tfUnos.getText();
				if (korisnikiUnos.isEmpty()) {
					lblPoruka.setText("Molimo unesite neki tekst.");
					return;
				}
				String anagram = izracunajAnagram(korisnikiUnos);
				taIspis.setText("Vas anagram je: " + anagram);
				lblPoruka.setText("");
			}
		});
		
		btnOcisti.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				tfUnos.clear();
				lblPoruka.setText("");
				taIspis.clear();
			}
		});
		
		btnIzadji.setOnAction(e ->  Platform.exit());
		primaryStage.show();
	}
}
