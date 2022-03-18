package macchinina.progetto.controllermacchinina;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MacchininaApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(MacchininaApplication.class.getResource("macchinina-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Progetto macchinina.");
        stage.setScene(scene);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}