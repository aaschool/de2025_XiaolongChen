
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// 修改为你自己的 WiFi 信息
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// 创建一个 HTTP 服务器，端口 80
ESP8266WebServer server(80);

// 模拟数据变量
bool sessionActive = false;
int heartRate = 75;       // 模拟心率数据
String stressLevel = "Moderate";
int breathingRate = 12;   // 模拟呼吸率数据

void handleRoot() {
  server.send(200, "text/plain", "Smart Meditation Corner - ESP8266");
}

void handleGetData() {
  // 返回 JSON 格式的模拟数据
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

  // 连接 WiFi
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

  // 设置路由
  server.on("/", handleRoot);
  server.on("/data", handleGetData);
  server.on("/startSession", handleStartSession);
  server.on("/endSession", handleEndSession);

  // 启动服务器
  server.begin();
  Serial.println("HTTP server started.");
}

void loop() {
  server.handleClient();
  // 这里可以根据需要更新模拟数据，例如 heartRate = random(60, 100);
}
