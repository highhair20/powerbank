/*
  CycleTest

  Circuit:
  * Arduino Uno
  * WiFi Shield

                          --------------------------
                          |     Arduino Uno R3     |
                          |     w/ WiFi Shield     |
                          |                        |
                          |                    SCL |-
                          |                    SDA |-
                          |                   AREF |-
                          |                    GND |-
                          |                     13 |- Wifi comm via SPI
                         -|                     12 |- Wifi comm via SPI
                         -| IOREF         (pwm) 11 |- Wifi comm via SPI
                         -| 3.3V          (pwm) 10 |- WiFi Slave Select (SS)
    Power to Wifi Shield -| 5V            (pwm)  9 |- Plug 6
            Relay Ground -| GND                  8 |- Plug 5
              PIR Ground -| GND                    |
                         -| Vin                  7 |- Handshake
                          |               (pwm)  6 |- Plug 4
               PIR Power -| A0            (pwm)  5 |- Plug 3
         PIR Digital Out -| A1                   4 |- WiFi SS for SD card
                         -| A2            (pwm)  3 |- Plug 2
                         -| A3                   2 |- Plug 1
                  Plug 8 -| A4 (SDA)        TX-> 1 |-
                  Plug 7 -| A5 (SCL)        RX<- 0 |-
                          --------------------------

  Arduino communicates with the WiFi shield using the
  SPI (Serial Peripheral Interface) bus on digital pins 11, 12, and 13.

  Created 2015.09.28
  by Jason Kelly
*/

#include <Event.h>
#include <Timer.h>


Timer t;
int flashEvents[8];

int motionPower = A0;
int motionOut = A1;

int plugPins[8] = {
  2,  // Plug 1
  3,  // Plug 2
  5,  // Plug 3
  6,  // Plug 4
  8,  // Plug 5
  9,  // Plug 6
  A5, // Plug 7
  A4  // Plug 8
};
int level[] = {HIGH, LOW};
int numPins = sizeof( plugPins ) / sizeof( int );

void setup() {
  Serial.begin(9600);
  Serial.println("Cycle - begin setup");

  // set the pin modes
  Serial.println(numPins);
  for (int i  = 0; i < numPins; i++) {
    pinMode(plugPins[i], OUTPUT);
  }
  pinMode(motionPower, OUTPUT);
  pinMode(motionOut, INPUT);

  // set high
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A4, HIGH);
  //
  digitalWrite(motionPower, HIGH);

//  // test flash
//  flashAll();

  //
//  t.every(1000 * 30, flicker);

}


void loop() {
  int motionVal = analogRead(motionOut);
  Serial.println(motionVal); 
  if (motionVal > 100) {
    flicker();
  }
  t.update();
}


void flashAll() {
  for (int i = 0; i < numPins; i++) {
    flashEvents[i] = t.oscillate(plugPins[i], 250, LOW, 3);
  }
}


void flicker() {
  t.oscillate(2, 30, LOW, 100);
  t.oscillate(3, 30, LOW, 100);
}
