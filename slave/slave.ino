#include <Arduino.h>
#include <Wire.h>

int DxAvantiMotor = 2;
int DxIndietroMotor = 3;
int SxAvantiMotor = 4;
int SxIndietroMotor = 5;
int fari = 6;
int frecciaDx = 7;
int frecciaSx = 8;

void avanti()
{
  digitalWrite(DxAvantiMotor, HIGH);
  digitalWrite(DxIndietroMotor, LOW);
  digitalWrite(SxAvantiMotor, LOW);
  digitalWrite(SxIndietroMotor, HIGH);
}
void indietro()
{
  digitalWrite(DxAvantiMotor, LOW);
  digitalWrite(DxIndietroMotor, HIGH);
  digitalWrite(SxAvantiMotor, HIGH);
  digitalWrite(SxIndietroMotor, LOW);
}
void destra()
{
  digitalWrite(DxAvantiMotor, LOW);
  digitalWrite(DxIndietroMotor, HIGH);
  digitalWrite(SxAvantiMotor, LOW);
  digitalWrite(SxIndietroMotor, HIGH);
}
void sinistra()
{
  digitalWrite(DxAvantiMotor, HIGH);
  digitalWrite(DxIndietroMotor, LOW);
  digitalWrite(SxAvantiMotor, HIGH);
  digitalWrite(SxIndietroMotor, LOW);
}
void fermo(){
  digitalWrite(DxAvantiMotor, LOW);
  digitalWrite(DxIndietroMotor, LOW);
  digitalWrite(SxAvantiMotor, LOW);
  digitalWrite(SxIndietroMotor, LOW);
}

void accendiDx()
{
  digitalWrite(frecciaDx, HIGH);
}
void accendiSx()
{
  digitalWrite(frecciaSx, HIGH);
}

void spegniDx()
{
  digitalWrite(frecciaDx, LOW);
}
void spegniSx()
{
  digitalWrite(frecciaSx, LOW);
}

void accendiFari()
{
  digitalWrite(fari, HIGH);
}
void spegniFari()
{
  digitalWrite(fari, LOW);
}

void riceviDati() {
  char comando = Wire.read();
  switch (comando){
    case 'w': avanti(); break;
    case 'a': sinistra(); break;
    case 's': indietro(); break;
    case 'd': destra(); break;
    case 'z': accendiDx(); break;
    case 'x': accendiSx(); break;
    case 'f': accendiFari(); break;
    case 'g': spegniFari(); break;
    case 'b': spegniDx(); break;
    case 'n': spegniSx(); break;
    case 'm': fermo(); break;
  }
}

void initOutputPin(int pin){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void setup() {
  Wire.begin(7);
  Wire.onReceive(riceviDati);
  initOutputPin(DxAvantiMotor);
  initOutputPin(DxIndietroMotor);
  initOutputPin(SxAvantiMotor);
  initOutputPin(SxIndietroMotor);
  initOutputPin(frecciaDx);
  initOutputPin(frecciaSx);
  initOutputPin(fari);
}

void loop() {}
