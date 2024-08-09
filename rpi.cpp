#include <WiFi.h>
#include <typeinfo>
#include <string.h>
#include <stdio.h>
#include "Keyboard.h"

// SSID and password for the access point
const char* ssid = "PicoClickAP";
const char* password = "12345678";

const int leftPin = 4;
const int rightPin = 5;

WiFiServer server(80);

void setup() {
  pinMode(leftPin, INPUT);
  pinMode(rightPin, INPUT);
  Keyboard.begin();
  Serial.begin(115200);

  // Set up the access point
  Serial.println("Setting up WiFi AP...");
  WiFi.softAP(ssid, password);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  // Start the server
  server.begin();

  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client is connected");
  }
}

void loop() {
String request;
// Check if a client has connected
  WiFiClient client = server.available();
      if (client.available()) {
        digitalWrite(LED_BUILTIN, HIGH);
        request = client.readStringUntil('\r');
        Serial.print("Received data: ");
        Serial.println(request); 

        digitalWrite(LED_BUILTIN, LOW);}
      digitalWrite(LED_BUILTIN, LOW);
   // Continuously update and apply motor control
  delay(100); // Delay to control loop speed


// Read pin states
  if (request == "NEXT") {
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(10); // Adjust delay as needed
    Keyboard.release(KEY_RIGHT_ARROW);
  }
  if (request == "PREV") {
    Keyboard.press(KEY_LEFT_ARROW);
    delay(10); // Adjust delay as needed
    Keyboard.release(KEY_LEFT_ARROW);
  }
  }
