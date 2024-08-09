#include <WiFi.h> //Library that has functions to help use WiFi to communicate
const int buttonPins[] = {25, 26}; // Change these pins as needed
const int numButtons = sizeof(buttonPins) / sizeof(buttonPins[0]);

const char* ssid = "PicoClickAP";  //SSID is your Raspberry Pi Pico W's WiFi's name!
const char* password = "12345678"; // keep it secret, or people might try to interfere during your final run XD
const char* host = "192.168.42.1"; // IP Address of the Pico
char click[3];
String packet;
int cmd;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop() {
  WiFiClient client;
  const int httpPort = 80;
  
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed");
    return;
  }
  for (int i = 0; i < numButtons; i++) {
    // Check if the button is pressed (LOW means pressed when using INPUT_PULLUP)
    if (digitalRead(buttonPins[i]) == LOW) {
      Serial.print(buttonPins[i]);
      cmd=i;
      while (digitalRead(buttonPins[i]) == LOW) {
        delay(10);
      }
    }
  }
  switch(cmd){
    case 25:
      packet="NEXT";
    case 26:
      packet="PREV";
  }
    client.print(String(packet));
    Serial.println(packet);

}
