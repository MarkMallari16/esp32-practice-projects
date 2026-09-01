#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "PLDTHOMEFIBRR2eYb";
const char* password = "PLDTWIFI9VUwm";

WebServer server(80);

const int ledPin = 13;
const int buzzerPin = 14;

void handleRoot() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP32 LED Control</title>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ESP32 LED Control</h1>";
  html += "<p>With Buzzer Control</p>";
  html += "<p><a href='/on'><button>TURN ON</button></a></p>";
  html += "<p><a href='/off'><button>TURN OFF</button></a></p>";
  html += "<br>";
  html += "<p><a href='/buzzerOn'><button>BUZZER ON</button></a></p>";
  html += "<p><a href='/buzzerOff'><button>BUZZER OFF</button></a></p>";
  html += "</body>";
  html += "</html>";

  server.send(200, "text/html", html);
}

void turnOn() {
  digitalWrite(ledPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void turnOff() {
  digitalWrite(ledPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void turnOnBuzzer(){
  digitalWrite(buzzerPin, HIGH);
  server.sendHeader("Location", "/");
  server.send(303);
}

void turnOffBuzzer(){
  digitalWrite(buzzerPin, LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/on", turnOn);
  server.on("/off", turnOff);
  server.on("/buzzerOn", turnOnBuzzer);
  server.on("/buzzerOff", turnOffBuzzer);

  server.begin();

  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}