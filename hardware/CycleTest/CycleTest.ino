/*
  PowerStrip

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
                         -| GND                  8 |- Plug 5
                         -| GND                    |
                         -| Vin                  7 |- Handshake
                          |               (pwm)  6 |- Plug 4
                         -| A0            (pwm)  5 |- Plug 3
                         -| A1                   4 |- WiFi SS for SD card
                         -| A2            (pwm)  3 |- Plug 2
                         -| A3                   2 |- Plug 1
                  Plug 8 -| A4 (SDA)        TX-> 1 |-
                  Plug 7 -| A5 (SCL)        RX<- 0 |-
                          --------------------------

  created 2015.09.28
  by Jason Kelly

  This code is in the public domain.

  Arduino communicates with the WiFi shield using the
  SPI (Serial Peripheral Interface) bus on digital pins 11, 12, and 13.
*/

#include <Event.h>
#include <Timer.h>


Timer t;
int flashEvents[8];

int pins[8] = {
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
int numPins = sizeof( pins ) / sizeof( int );

void setup() {
  Serial.begin(9600);
  Serial.println("Cycle - begin setup");

  // set the pin modes
  Serial.println(numPins);
  for (int i  = 0; i < numPins; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // test flash
  flashAll();
  
  //
  t.every(1000 * 10, flicker);
}


void loop() {
  t.update();
}


void flashAll() {
  for (int i = 0; i < numPins; i++) {
    flashEvents[i] = t.oscillate(pins[i], 250, LOW, 3);
  }
}


void flicker() {
  t.oscillate(2, 10, LOW, 200);
}

