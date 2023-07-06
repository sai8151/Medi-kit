#include <ESP8266WiFi.h>
#include <Wire.h>
#include "MAX30105.h"

int gpio_num;
const char* ssid = "12345678";
const char* password = "12345678";
String s;
int val;
WiFiServer server(80);
MAX30105 particleSensor;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(2, OUTPUT); 
  digitalWrite(2, 0);
  // Add other pin initialization here
  
  Wire.begin(D2, D1); // Specify SDA and SCL pins for Wire library
  
  // Initialize MAX30105 sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) {
    Serial.println("MAX30105 was not found. Please check wiring/power.");
    while (1);
  }
  particleSensor.setup(); // Configure sensor. Use 6.4mA for LED drive
  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println("New client");
  
  while(!client.available()){
    delay(1);
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Handle GPIO control requests
  if (req.indexOf("/gpio2/0") != -1) {
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>CONNECTED<br> gpio2 off </h1><br><h6>from esp 8255";
    digitalWrite(2, 0);
    val = 0;
    gpio_num = 2;
  }
  // Add other GPIO control conditions here
  
  // Handle sensor reading request
  else if (req.indexOf("/sensor") != -1) {
    int redValue = particleSensor.getRed();
    int irValue = particleSensor.getIR();
    int greenValue = particleSensor.getGreen();
    
    // Calculate heart rate (BPM) using red LED data
    float redAvgValue = redValue / 100.0; // Convert to floating-point value
    float heartRate = 60 / redAvgValue; // Calculate heart rate in BPM
    
    // Read temperature from sensor
    float temperature = particleSensor.readTemperature();
    
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n<h1>MAX30105 Sensor Readings</h1>";
    s += "<br>Red: " + String(redValue);
    s += "<br>IR: " + String(irValue);
    s += "<br>Green: " + String(greenValue);
    s += "<br>Heart Rate: " + String(heartRate) + " BPM";
    s += "<br>Temperature: " + String(temperature) + " °C";
    s += "<br><a href=\"/gpio2/0\">Turn off gpio2</a";
    // Add other GPIO control links here
    s += "</html>\n";
  }
  else {
    Serial.println("Invalid request");
    client.stop();
    return;
  }
  
  client.print(s);
  delay(1);
  Serial.println("Client disconnected");
}
