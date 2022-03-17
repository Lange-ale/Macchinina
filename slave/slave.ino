#include <Arduino.h>
#include <Wire.h>

//FARE LE FUNZIONI PER SPEGNERE FRECCIE e per far star la macchina ferma

int DxAvantiMotor = 1;
int DxIndietroMotor = 2;
int SxAvantiMotor = 3;
int SxIndietroMotor = 4;
int frecciaDx = 5;
int frecciaSx = 6;
int fari = 7;

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

void accendiDx()
{
  digitalWrite(frecciaDx, HIGH);
}
void accendiSx()
{
  digitalWrite(frecciaSx, HIGH);
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