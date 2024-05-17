#include <Arduino_MKRIoTCarrier.h>
#include <SPI.h>
#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include "arduino_secrets.h"
#include <SD.h>
#include <Arduino.h>
#include <bsec.h>
MKRIoTCarrier carrier;

char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the WiFi radio's status

const int serverPort = 5063;
const char* endPoint = "/api/UserColors";
//const char* serverAddress = "https://h3-projektv2-24q2h3-gruppe2.onrender.com";
const char* serverAddress = "172.20.10.4";
WiFiSSLClient wifi;
HttpClient client = HttpClient(wifi, serverAddress, serverPort);

// Specify IP address or hostname
String hostName = "www.google.com";
int pingResult;
void setup() {
    carrier.begin();
  carrier.display.fillScreen(ST77XX_BLACK); // Start med en ren skærm
  carrier.leds.setBrightness(255); // Sæt LED'ernes maksimale lysstyrke
  // Initialiser kommunikation
  Serial.begin(9600);
 
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    carrier.display.setCursor(60, 110);
    carrier.display.print("Connecting to wifi");

    // wait 5 seconds for connection:
    delay(5000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  carrier.display.setCursor(30, 125);
  carrier.display.print("Connected to wifi!");
  printCurrentNet();
  printWiFiData();

}

void loop() {
  
    if (carrier.Buttons.onTouchDown(TOUCH4)) {
  if(client.connect(serverAddress, serverPort)) {
  Serial.println("Connected to server");
} else {
  Serial.println("connection failed");
}
   }

  carrier.Buttons.update();
  // Tjek om en farveaflæsning er tilgængeligs
  while (!carrier.Light.colorAvailable()) {
    delay(5);
  }
  
  int r, g, b;

 if (carrier.Buttons.onTouchDown(TOUCH0)) {
  carrier.Light.readColor(r, g, b); // Læs data fra RGB-sensoren
 

 r = min(r, 255);
g = min(g, 255);
b = min(b, 255);


  Serial.print("R: "); Serial.print(r);
  Serial.print(", G: "); Serial.print(g);
  Serial.print(", B: "); Serial.println(b);

sendPostRequest(String (r));

  // Konverterer RGB-værdier til en enkelt 32-bit farveværdi (for DotStar LEDs)
  uint32_t color = carrier.leds.Color(r, g, b);

  // Sæt alle 5 LEDs til den læste farve
  carrier.leds.fill(color, 0, 5);
  carrier.leds.show(); // Opdater LED'ernes tilstand

  // Opdater skærmens baggrundsfarve til at matche den læste farve
  uint16_t displayColor = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
  carrier.display.fillScreen(displayColor);

  // Vælg en kontrastfarve for teksten
  uint16_t textColor = (r > 127 || g > 127 || b > 127) ? ST77XX_BLACK : ST77XX_WHITE;
  carrier.display.setTextColor(textColor);
  carrier.display.setTextSize(2);

  String colourName = getColourName(r, g, b); // Få navnet på den detekterede farve

  Serial.print(" R2: "); Serial.print(r);
Serial.print(", G2: "); Serial.print(g);
Serial.print(", B2: "); Serial.println(b);


  // Vis RGB værdier på skærmen
 carrier.display.setCursor(30, 110);
    carrier.display.print("RGB: ");
    carrier.display.setCursor(30, 125);
    carrier.display.print(r);
    carrier.display.setCursor(30, 140);
    carrier.display.print(g);
    carrier.display.setCursor(30, 155);
    carrier.display.print(b);

     // Vis navnet på den detekterede farve
  carrier.display.setCursor(30, 170);
  carrier.display.print("Farve: ");
  carrier.display.println(colourName);

  delay(100); // Vent lidt før næste måling
 }
  if (carrier.Buttons.onTouchDown(TOUCH1)) {
 Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");

  pingResult = WiFi.ping(hostName);

  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }
  }

}

String getColourName(int r, int g, int b) {
  if (r > 200 && g < 50 && b < 50) return "Red";
  else if (r < 50 && g > 200 && b < 50) return "Green";
  else if (r < 50 && g < 50 && b > 200) return "Blue";
  else if (r > 200 && g > 200 && b < 50) return "Yellow";
  else if (r > 200 && g < 50 && b > 200) return "Magenta";
  else if (r < 50 && g > 200 && b > 200) return "Cyan";
  else if (r > 200 && g > 200 && b > 200) return "White";
  else if (r < 50 && g < 50 && b < 50) return "Black";
  else return "Unknown";
}
void printWiFiData() {
  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP address : ");
  Serial.println(ip);

  Serial.print("Subnet mask: ");
  Serial.println((IPAddress)WiFi.subnetMask());

  Serial.print("Gateway IP : ");
  Serial.println((IPAddress)WiFi.gatewayIP());

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC address: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);
  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type: ");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}


void sendPostRequest(String r) {
    // Create a JSON payload    Serial.println(payload);
    DynamicJsonDocument doc(1024);
    doc["R"] = r.c_str();

    // Serialize JSON to string
    String payload;
    serializeJson(doc, payload);

    Serial.println("Payload: ");
    Serial.println(payload);

    // Send POST request
    Serial.println("Sending POST request");
    client.beginRequest();
    client.post(endPoint);
    client.sendHeader("Content-Type", "application/json");
    client.sendHeader("Content-Length", payload.length());
    client.endRequest();
    client.print(payload);

    // Print some debug info if needed
    Serial.println("POST request sent");
    

    int statusCode = client.responseStatusCode();
    String response = client.responseBody();
    //makes a json object
    Serial.print("HTTP Response Code: ");
    Serial.println(statusCode);
    Serial.print("Response Body: ");
    Serial.println(response);
    Serial.println();
    
}

