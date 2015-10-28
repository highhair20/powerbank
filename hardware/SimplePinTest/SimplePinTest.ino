/*
  SimplePinTest

  Run a simple test to cycle through each of the plugs
  to test that they are functional.

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

  Arduino communicates with the WiFi shield using the
  SPI (Serial Peripheral Interface) bus on digital pins 11, 12, and 13.

  created 2015.09.28
  by Jason Kelly
 */

void setup() {
  pinMode(2, OUTPUT);  // Plug 1
  pinMode(3, OUTPUT);  // Plug 2
  pinMode(5, OUTPUT);  // Plug 3
  pinMode(6, OUTPUT);  // Plug 4
  pinMode(8, OUTPUT);  // Plug 5
  pinMode(9, OUTPUT);  // Plug 6
  pinMode(A5, OUTPUT); // Plug 7
  pinMode(A4, OUTPUT); // Plug 8
}

void loop() {
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A4, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(A5, LOW);
  digitalWrite(A4, LOW);
  delay(500);

}
