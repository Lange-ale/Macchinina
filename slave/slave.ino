#include <Arduino.h>
#include <Wire.h>

int DxAvantiMotor = 2;
int DxIndietroMotor = 3;
int SxAvantiMotor = 4;
int SxIndietroMotor = 5;
int frecciaDx = 6;
int frecciaSx = 7;
int fari = 1;

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
  if(comando == 'w') avanti();
  else if(comando == 'a') sinistra();
  else if(comando =='s') indietro();
  else if(comando == 'd') destra();
  else if(comando == 'z') accendiDx();
  else if(comando == 'x') accendiSx();
  else if(comando == 'f') accendiFari();
  else if(comando == 'g') spegniFari();
  else if(comando == 'x') spegniDx();
  else if(comando == 'y') spegniSx();
  else if(comando == 'z') fermo();
}

void setup() {
  Wire.begin(7);
  Wire.onReceive(riceviDati);
  pinMode(DxAvantiMotor, OUTPUT);
  pinMode(DxIndietroMotor, OUTPUT);
  pinMode(SxAvantiMotor, OUTPUT);
  pinMode(SxIndietroMotor, OUTPUT);
  pinMode(frecciaDx, OUTPUT);
  pinMode(frecciaSx, OUTPUT);
  pinMode(fari, OUTPUT);
  digitalWrite(DxAvantiMotor, LOW);
  digitalWrite(DxIndietroMotor, LOW);
  digitalWrite(SxAvantiMotor, LOW);
  digitalWrite(SxIndietroMotor, LOW);
  digitalWrite(frecciaDx, LOW);
  digitalWrite(frecciaSx, LOW);
  digitalWrite(fari, LOW);
}

void loop() {}
