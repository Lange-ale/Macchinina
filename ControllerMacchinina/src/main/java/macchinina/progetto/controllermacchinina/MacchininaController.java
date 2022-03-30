package macchinina.progetto.controllermacchinina;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class MacchininaController {
    @FXML
    private Button stopButton, avantiButton, indietroButton, sinistraButton, destraButton, frecciaSinistraButton, frecciaDestraButton, fanaliButton;

    @FXML
    private void initialize(){

    }

    private void trasmetti(char c){
        System.out.println(c);
    }

    @FXML
    private void onavantiButtonClick() {
        trasmetti('w');
    }

    @FXML
    private void onindietroButtonClick() {
        trasmetti('s');
    }

    @FXML
    private void onsinistraButtonClick() {
        trasmetti('a');
    }

    @FXML
    private void ondestraButtonClick() {
        trasmetti('d');
    }

    @FXML
    private void onfrecciaSinistraButtonClick() {
        trasmetti('x');
        trasmetti('y');
    }

    @FXML
    private void onfrecciaDestraButtonClick() {
        trasmetti('z');
        trasmetti('x');
    }

    @FXML
    private void onfanaliButtonClick() {
        trasmetti('f');
        trasmetti('g');
    }

    @FXML
    private void onstopButtonClick() {
        trasmetti('z');
    }
}