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


  Arduino communicates with the WiFi shield using the
  SPI (Serial Peripheral Interface) bus on digital pins 11, 12, and 13.

  Retrieve program to run plugs.

  created 2015.09.28
  by Jason Kelly
*/

#include <SPI.h>
#include <WiFi.h>
#include <ArduinoJson.h>
//#include <WiFiRestClient.h>


char ssid[7] = "laLuna";      // network SSID (name)
char pass[9] = "leftyd0g";    // your network password
int keyIndex = 0;             // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;


//WiFiRestClient rest = WiFiRestClient("https://lit-cove-2559.herokuapp.com");

// Initialize the Wifi client library (port 90 is default)
// WiFiClient client;

// last time we connected to the server, in milliseconds
unsigned long lastConnectionTime = 0;
// delay between updates, in milliseconds
const unsigned long configInterval = 10L * 1000L;

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if ( fv != "1.1.0" )
    Serial.println("Please upgrade the Wifi shield firmware");

  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();

  // get the initial configuration
  // first first time startup this is the default config
  // for power outages this will reset us to our latest config
  updateConfiguration();

  // tell the server where we are

//  rest.dhcp();
}


//String response;
void loop(){
//  response = "";
//  int statusCode = rest.get("/get", &response);
//  Serial.print("Status code from server: ");
//  Serial.println(statusCode);
//  Serial.print("Response body from server: ");
//  Serial.println(response);
//  delay(1000);
}



//void loop() {
//  // if there's incoming data from the net connection.
//  // send it out the serial port.  This is for debugging
//  // purposes only:
////  while (client.available()) {
////    char c = client.read();
////    Serial.write(c);
////  }
//
//  // if ten seconds have passed since your last connection,
//  // then connect again and send data:
////  if (millis() - lastConnectionTime > configInterval) {
////    httpRequest("/config");
////  }
//
//  // if the server's disconnected, stop the client:
//  if (!client.connected()) {
//    Serial.println();
//    Serial.println("disconnecting from server.");
//    client.stop();
//
//    // do nothing forevermore:
//    while(true);
//  }
//
//}





/*
  httpRequest

  Generic function for making a web request
 */
// this method makes a HTTP connection to the server:
char* httpRequest(char *endpoint, char *server = "frozen-oasis-5671.herokuapp.com") {

  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  char response[1000] = {};
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    char requestHeader[80];
    strcpy(requestHeader, "GET ");
    strcat(requestHeader, endpoint);
    strcat(requestHeader, " HTTP/1.1");
    client.println(requestHeader);
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();

    // wait for some time for the connection to be established
    delay(2000);
    int i = 0;
    char c;
    while (client.available()) {
      c = client.read();
//      Serial.print(c);
      response[i] = c;
      i++;
      //Serial.print(response);


//      byte bTmp = client.read();
//      response[len] = (char)bTmp;
//      ++len;
//      Serial.write(bTmp);
////      const char *cTmp = (char)bTmp;
////      response = strcat(response, *cTmp);
////      Serial.write(response);
    }
    response[i] = '\0';
//    Serial.println(response);

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
  return response;
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void parseJson(char *json) {
  StaticJsonBuffer<200> jsonBuffer;

//  char json[] =
//      "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

  JsonObject& root = jsonBuffer.parseObject(json);

  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  const char* sensor = root["sensor"];
  long time = root["time"];
  double latitude = root["data"][0];
  double longitude = root["data"][1];

  Serial.println(sensor);
  Serial.println(time);
  Serial.println(latitude, 6);
  Serial.println(longitude, 6);
}

/*
  updateConfiguration

  Makes a call to the server to determine the most recent configuration.
 */
char* updateConfiguration() {
  // retreive configuration
  char *conf = httpRequest("/config");
  Serial.println("===");
  Serial.println(conf);
  Serial.println("===");
  parseJson(conf);
  return conf;
}
