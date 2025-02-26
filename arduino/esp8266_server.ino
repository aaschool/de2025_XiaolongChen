
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";


ESP8266WebServer server(80);


bool sessionActive = false;
int heartRate = 75;       
String stressLevel = "Moderate";
int breathingRate = 12;   

void handleRoot() {
  server.send(200, "text/plain", "Smart Meditation Corner - ESP8266");
}

void handleGetData() {
  
  String jsonResponse = "{";
  jsonResponse += "\"heartRate\": " + String(heartRate) + ",";
  jsonResponse += "\"stressLevel\": \"" + stressLevel + "\",";
  jsonResponse += "\"breathingRate\": " + String(breathingRate) + ",";
  jsonResponse += "\"sessionActive\": " + String(sessionActive ? "true" : "false");
  jsonResponse += "}";
  server.send(200, "application/json", jsonResponse);
}

void handleStartSession() {
  sessionActive = true;
  server.send(200, "text/plain", "Session started");
}

void handleEndSession() {
  sessionActive = false;
  server.send(200, "text/plain", "Session ended");
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println();

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  server.on("/", handleRoot);
  server.on("/data", handleGetData);
  server.on("/startSession", handleStartSession);
  server.on("/endSession", handleEndSession);

  
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
  
}
