#include <Arduino.h>
#include <Wire.h>


#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"

#include "BluefruitConfig.h"

#if SOFTWARE_SERIAL_AVAILABLE
  #include <SoftwareSerial.h>
#endif

#define FACTORYRESET_ENABLE         1
#define MINIMUM_FIRMWARE_VERSION    "0.6.6"
#define MODE_LED_BEHAVIOUR          "MODE"

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

// function prototypes over in packetparser.cpp
uint8_t readPacket(Adafruit_BLE *ble, uint16_t timeout);
float parsefloat(uint8_t *buffer);
void printHex(const uint8_t * data, const uint32_t numBytes);

// the packet buffer
extern uint8_t packetbuffer[];

void bluetooth_error() {
    send_to_slave('x');
    send_to_slave('z');
    while (1);
}


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
/*
DistanceSensor s1(9 , 10);
DistanceSensor s2(21, 22);
DistanceSensor s3(19, 18);
DistanceSensor s4(13, 12);
*/
const int max_distance = 15;
int dir = 0; // w = 5, a = 7, s = 6, d = 8
bool led_sx = false, led_dx = false,
acceso_sx = false, acceso_dx = false;
unsigned long timer_sx, timer_dx;

void send_to_slave(char message){
    Wire.beginTransmission(7);
    Wire.write(message);
    Wire.endTransmission();
}

void animation_turn_on() {
    for(int i = 0; i<3; i++){
        delay(500);
        send_to_slave('x');
        send_to_slave('z');
        delay(500);
        send_to_slave('b');
        send_to_slave('n');
    }
}

void setup() {
    Wire.begin();
    /*
    s1.init();
    s2.init();
    s3.init();
    s4.init();
     */


    if ( !ble.begin(VERBOSE_MODE) ) //Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?
        bluetooth_error();

    if ( FACTORYRESET_ENABLE )
        if ( ! ble.factoryReset() ) //Couldn't factory reset
            bluetooth_error();

    ble.echo(false);  // Disable command echo from Bluefruit
    ble.verbose(false);  // debug info is a little annoying after this point!

    while (! ble.isConnected()) //Wait for connection
        delay(10);

    if ( ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION) ) // Change Mode LED Activity to MODE_LED_BEHAVIOUR, LED Activity command is only supported from 0.6.6
        ble.sendCommandCheckOK("AT+HWModeLED=" MODE_LED_BEHAVIOUR);

    ble.setMode(BLUEFRUIT_MODE_DATA); // Set Bluefruit to DATA mode


    animation_turn_on();
}


void loop() {
/*
    if (dir == 5) {
        if (s1.distance() < max_distance || s2.distance() < max_distance) {
            send_to_slave('m');
            dir = 0;
        }
    } else if (dir == 6) {
        if (s3.distance() < max_distance || s4.distance() < max_distance) {
            send_to_slave('m');
            dir = 0;
        }
    }
*/
    if (led_sx)
        if(millis() > timer_sx){
            if (acceso_sx)
                send_to_slave('n');
            else
                send_to_slave('x');
            acceso_sx = !acceso_sx;
            timer_sx = millis() + 300;
        }
     if (led_dx)
        if(millis() > timer_dx){
            if (acceso_dx)
                send_to_slave('b');
            else
                send_to_slave('z');
            acceso_dx = !acceso_dx;
            timer_dx = millis() + 300;
        }


    /* Wait for new data to arrive */
    uint8_t len = readPacket(&ble, 100);
    if (len == 0 || packetbuffer[1] != 'B') return;
    uint8_t buttnum = packetbuffer[2] - '0';
    boolean pressed = packetbuffer[3] - '0';

    if (buttnum >= 5 && buttnum <= 8) {
        if (!pressed) {
            send_to_slave('m');
            dir = 0;
            return;
        }

        dir = buttnum;
        switch (buttnum) {
            case 5:
                //if (s1.distance() >= max_distance && s2.distance() >= max_distance)
                    send_to_slave('w');
                return;
            case 6:
                //if (s3.distance() >= max_distance && s4.distance() >= max_distance)
                    send_to_slave('s');
                return;
            case 7:
                send_to_slave('a');
                return;
            case 8:
                send_to_slave('d');
                return;
        }

    } else if (!pressed) {
        if (buttnum == 1) {
            if (!led_sx)
                send_to_slave('x');
            else
                send_to_slave('n');
            led_sx = !led_sx;
            acceso_sx = led_sx;
            timer_sx = millis() + 300;
            return;
        }
        if (buttnum == 2) {
            if (!led_dx)
                send_to_slave('z');
            else
                send_to_slave('b');
            led_dx = !led_dx;
            acceso_dx = led_dx;
            timer_dx = millis() + 300;
        }
    }
}

/*
    if (millis() > time_dir || dir == 4) {
        time_dir = millis() + 2000;
        dir = millis() % 4;

        switch (dir) {
            case 0:
                send_to_slave('w');
                break;
            case 1:
                send_to_slave('x');
                send_to_slave('a');
                start_rotation = millis();
                break;
            case 2:
                send_to_slave('s');
                break;
            case 3:
                send_to_slave('z');
                send_to_slave('d');
                start_rotation = millis();
                break;
            default:
                send_to_slave('m');
        }
    }

    if (dir == 0) {
        if (s1.distance() < max_distance || s2.distance() < max_distance) {
            send_to_slave('m');
            dir = 4;
        }
    } else if (dir == 2) {
        if (s3.distance() < max_distance || s4.distance() < max_distance) {
            send_to_slave('m');
            dir = 4;
        }
    } else if (millis() > start_rotation + 1000) {
        send_to_slave('m');
        if (dir == 1)
            send_to_slave('b');
        else if (dir == 3)
            send_to_slave('n');
        dir = 4;
    }
*/
