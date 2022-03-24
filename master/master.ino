#include <Wire.h>

struct DistanceSensor{
  int trig, echo;
  DistanceSensor (int trig, int echo) : trig(trig), echo(echo) {}
};

DistanceSensor s1( 0, 1 );
DistanceSensor s2(13, 12);
DistanceSensor s3( 10 , 9 );
DistanceSensor s4( 3, 4 );

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Serial.write(distance(s1));
  Serial.write(distance(s2));
  Serial.write(distance(s3));
  Serial.write(distance(s4));
  int t = millis();
  while(millis()-t<=500)
    trasmetti('w');
  t = millis();
  while(millis()-t<=500)
    trasmetti('a');
  t = millis();
  while(millis()-t<=500)
    trasmetti('s');
  t = millis();
  while(millis()-t<=500)
    trasmetti('d');
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
