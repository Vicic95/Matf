package javaFXKalkulator;

import java.util.ArrayList;
import java.util.List;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class Main extends Application {

	public static void main(String[] args) {
		launch(args);
	}
	@Override
	public void start(Stage primaryStage) {
		VBox root = new VBox(10);
		root.setPadding(new Insets(10, 10, 10, 10));

		HBox hbTop = new HBox(10);
		Label lblRezultat = new Label("Rezultat:");
		TextField tfIzlaz = new TextField();
		Label lblGreska = new Label();
		lblGreska.setTextFill(Color.RED);
		lblGreska.setText("");
		root.getChildren().addAll(hbTop, lblRezultat, tfIzlaz, lblGreska);
		
		VBox vbLevi = new VBox(10);
		VBox vbDesni = new VBox(10);
		vbDesni.setPadding(new Insets(40, 0, 0, 10)); 
		hbTop.getChildren().addAll(vbLevi, vbDesni);

		Label lblOperand1 = new Label("Prvi operand:");
		TextField tfOperand1 = new TextField();
		Label lblOperand2 = new Label("Drugi operand:");
		TextField tfOperand2 = new TextField();
		vbLevi.getChildren().addAll(lblOperand1, tfOperand1, lblOperand2, tfOperand2);
		
		HBox hbDugmici1 = new HBox(10);
		HBox hbDugmici2 = new HBox(10);
		vbDesni.getChildren().addAll(hbDugmici1, hbDugmici2);
		
		Button btPlus = new Button("+");
		Button btMinus = new Button("-");
		Button btPuta = new Button("*");
		hbDugmici1.getChildren().addAll(btPlus, btMinus, btPuta);

		Button btPodeljeno = new Button("/");
		Button btKoren = new Button("√");
		Button btC = new Button("C");
		hbDugmici2.getChildren().addAll(btPodeljeno, btKoren, btC);
		
		btPlus.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String rezultat = izvrsiOperaciju(tfOperand1, tfOperand2, lblGreska, Operacija.SABIRANJE);
				if (! rezultat.isEmpty()) tfIzlaz.setText(rezultat);
			}
		});
		
		btMinus.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String rezultat = izvrsiOperaciju(tfOperand1, tfOperand2, lblGreska, Operacija.ODUZIMANJE);
				if (! rezultat.isEmpty()) tfIzlaz.setText(rezultat);
			}
		});

		btPodeljeno.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String rezultat = izvrsiOperaciju(tfOperand1, tfOperand2, lblGreska, Operacija.DELJENJE);
				if (! rezultat.isEmpty()) tfIzlaz.setText(rezultat);
			}
		});
		
		btPuta.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String rezultat = izvrsiOperaciju(tfOperand1, tfOperand2, lblGreska, Operacija.MNOZENJE);
				if (! rezultat.isEmpty()) tfIzlaz.setText(rezultat);
			}
		});
		
		btKoren.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				String rezultat = izvrsiOperaciju(tfOperand1, tfOperand2, lblGreska, Operacija.KOREN);
				if (! rezultat.isEmpty()) tfIzlaz.setText(rezultat);
			}	
		});

		btC.setOnAction(new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent event) {
				tfIzlaz.clear();
				tfOperand1.clear();
				tfOperand2.clear();
				lblGreska.setText("");
			}
		});

		Scene scene = new Scene(root, 340, 240);
		primaryStage.setTitle("Kalkulator");
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	private static List<Double> unesiOperande(TextField tf1, TextField tf2, Label izlazZaGresku) {
		List<Double> brojevi = new ArrayList<>();
		try {
			double a = Double.parseDouble(tf1.getText());
			double b = Double.parseDouble(tf2.getText());
			brojevi.add(a);
			brojevi.add(b);
		} catch (NumberFormatException e) {
			izlazZaGresku.setText("Operandi nisu u odgovarajucem formatu!");
		}
		return brojevi;
	}
	private static String izvrsiOperaciju(TextField tfOperand1, TextField tfOperand2, Label izlazZaGresku, Operacija op) {
		List<Double> operandi = unesiOperande(tfOperand1, tfOperand2, izlazZaGresku);
		if (operandi.isEmpty()) return "";
		Izraz i = new Izraz(operandi.get(0), operandi.get(1), op);
		return i.toString();
	}

}