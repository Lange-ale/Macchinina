#include <Wire.h>

struct DistanceSensor{
  int trig, echo;
  DistanceSensor (int trig, int echo) : trig(trig), echo(echo) {}
};

//DistanceSensor s1( ?, ? );

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
 // Serial.write(distance(s1));
    trasmetti('w');
    delay(2000);
    trasmetti('a');
    delay(2000);
    trasmetti('s');
    delay(2000);
    trasmetti('d');
    delay(2000);
}

void trasmetti(char message){
  Wire.beginTransmission(7);
  Wire.write(message);
  Wire.endTransmission();  
}

long distance(DistanceSensor sensor){ 
  // Send 10µs pulse 
  digitalWrite(sensor.trig, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(sensor.trig, LOW); 
  // Read pulse duration 
  int duration = pulseIn(sensor.echo, HIGH); 
  return duration/ 58; 
}
