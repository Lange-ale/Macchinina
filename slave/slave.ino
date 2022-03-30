#include <Arduino.h>
#include <Wire.h>

struct DistanceSensor{
    int trig, ech;
    DistanceSensor (int trig, int ech) : trig(trig), ech(ech) {}
    void init(){
        pinMode(trig, OUTPUT);
        pinMode(ech, INPUT);
    }
    long distance(){
        // Send 10µs pulse
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        // Read pulse duration
        int duration = pulseIn(ech, HIGH);
        return duration/ 58;
    }
};

DistanceSensor s1(11 , 10);
DistanceSensor s2(8, 9);
DistanceSensor s3(14, 15);
DistanceSensor s4(13, 12);

int DxAvantiMotor = 2;
int DxIndietroMotor = 3;
int SxAvantiMotor = 4;
int SxIndietroMotor = 5;
int frecciaDx = 6;
int frecciaSx = 7;

const int max_distance = 15;
int dir = 0;

void avanti()
{
    if (s1.distance() < max_distance || s2.distance() < max_distance) {
        fermo();
        return;
    }
    
    digitalWrite(DxAvantiMotor, HIGH);
    digitalWrite(DxIndietroMotor, LOW);
    digitalWrite(SxAvantiMotor, LOW);
    digitalWrite(SxIndietroMotor, HIGH);
    dir = 5;
}
void indietro()
{ 
    if (s3.distance() < max_distance || s4.distance() < max_distance) {
        fermo();
        return;
    }
    
    digitalWrite(DxAvantiMotor, LOW);
    digitalWrite(DxIndietroMotor, HIGH);
    digitalWrite(SxAvantiMotor, HIGH);
    digitalWrite(SxIndietroMotor, LOW);
    dir = 6;
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
  dir = 0;
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


void riceviDati() {
  char comando = Wire.read();
  switch (comando){
    case 'w': avanti(); break;
    case 'a': sinistra(); break;
    case 's': indietro(); break;
    case 'd': destra(); break;
    case 'z': accendiDx(); break;
    case 'x': accendiSx(); break;
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
  s1.init();
  s2.init();
  s3.init();
  s4.init();
}

void loop() {
    if (dir == 5) {
        if (s1.distance() < max_distance || s2.distance() < max_distance)
            fermo();
    } else if (dir == 6) {
        if (s3.distance() < max_distance || s4.distance() < max_distance)
            fermo();
    }
}
