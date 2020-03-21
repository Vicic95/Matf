package javaFX;

import java.util.Random;

import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;

public class JavaFXRadioB extends Application {
	public static void main(String[] args) {
		launch(args);
	}
	
	private int windowWidth = 450, windowHeight = 450;
	private int width = 400, height = 400, size = 150;

	@Override
	public void start(Stage primaryStage) {
		VBox root = new VBox(10);
		root.setAlignment(Pos.CENTER);
		
		Canvas canvas = new Canvas(width, height);
		GraphicsContext gc = canvas.getGraphicsContext2D();

		HBox hb = new HBox(10);
		hb.setAlignment(Pos.CENTER);
		ToggleGroup tgroup = new ToggleGroup();
		RadioButton rbKvadrat = new RadioButton("Kvadrat");
		RadioButton rbKrug = new RadioButton("Krug");
		
		rbKvadrat.setToggleGroup(tgroup);
		rbKrug.setToggleGroup(tgroup);

		Button btCrtaj = new Button("Crtaj");
		Button btBrisi = new Button("Brisi");
		Button btRand  = new Button("Nasumicno");
		
		hb.getChildren().addAll(rbKvadrat, rbKrug, btCrtaj, btBrisi, btRand);
		
		Random rand = new Random();
		
		btCrtaj.setOnAction(e -> {
			if (rbKrug.isSelected()) {
				gc.setFill(Color.RED);
				gc.fillOval(width/2 - size/2, height/2 - size/2, size/2, size/2);
			} else if (rbKvadrat.isSelected()) {
				gc.setFill(Color.BLUE);
				gc.fillRect(width/2 - size/2, height/2 - size/2, size/2, size/2);
			}
		});
		
		btBrisi.setOnAction(e -> {
			gc.clearRect(0, 0, width, height);
		});
		
		btRand.setOnAction(e -> {

			int x = rand.nextInt(width);
			int y = rand.nextInt(height);
			

			int a = rand.nextInt(width/2);
			int b = rand.nextInt(height/2);
			
			gc.setFill(Color.color(rand.nextDouble(), rand.nextDouble(), rand.nextDouble()));

			if (rand.nextBoolean())
				gc.fillOval(x, y, a, b);
			else
				gc.fillRect(x, y, a, b);
		});
		
		root.getChildren().addAll(hb, canvas);

		Scene scene = new Scene(root, windowWidth, windowHeight);
		primaryStage.setTitle("Hello Radio and Canvas");
		primaryStage.setScene(scene);
		primaryStage.show();
	}
}
