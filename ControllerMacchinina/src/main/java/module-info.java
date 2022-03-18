module macchinina.progetto.controllermacchinina {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires org.kordamp.bootstrapfx.core;

    opens macchinina.progetto.controllermacchinina to javafx.fxml;
    exports macchinina.progetto.controllermacchinina;
}