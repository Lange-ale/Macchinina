package macchinina.progetto.controllermacchinina;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;

public class MacchininaController {
    @FXML
    private Button stopButton, avantiButton, indietroButton, sinistraButton, destraButton, frecciaSinistraButton, frecciaDestraButton, fanaliButton;

    public void trasmetti(char c){
        System.out.println(c);
    }

    @FXML
    protected void onavantiButtonClick() {
        trasmetti('w');
    }

    @FXML
    protected void onindietroButtonClick() {
        trasmetti('s');
    }

    @FXML
    protected void onsinistraButtonClick() {
        trasmetti('a');
    }

    @FXML
    protected void ondestraButtonClick() {
        trasmetti('d');
    }

    @FXML
    protected void onfrecciaSinistraButtonClick() {
        trasmetti('x');
        trasmetti('y');
    }

    @FXML
    protected void onfrecciaDestraButtonClick() {
        trasmetti('z');
        trasmetti('x');
    }

    @FXML
    protected void onfanaliButtonClick() {
        trasmetti('f');
        trasmetti('g');
    }

    @FXML
    protected void onstopButtonClick() {
        trasmetti('z');
    }
}