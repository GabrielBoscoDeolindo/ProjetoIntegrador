#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"
 
  // GABRIEL BOSCO DEOLINDO
 
  const char* ssid = "ARI";
  const char* password = "a1234567";
 
  const char *GScriptId = "AKfycbysfHc3VtuL62G5ktvpioITkVwgYACA0WPtY8Cxj1oD4ZAOtZufJQPizR22CpMNTIMR";
 
  String payload_base = "{\"command\": \"insert_row\", \"sheet_name\": \"Sheet1\", \"values\": ";
  String payload = "";
 
  const char* host = "script.google.com";
  const int httpsPort = 443;
  const char* fingerprint = "";
  String url = String("/macros/s/") + GScriptId + "/exec";
  HTTPSRedirect* client = nullptr;
 
  int esteira1 = 0;
  int esteira2 = 0;
  int esteira3 = 0;
 
void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');
 
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody (true);
  client->setContentTypeHeader("application/json");
 
  Serial.print("Connecting to ");
  Serial.println(host);
 
  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client->connect (host, httpsPort);
    if (retval == 1){
      flag = true;
      Serial.println("Connected");
      break;
  }
  else
    Serial.println("Connection failed. Retrying...");
  }
  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host); return;
  }
  delete client; 
  client = nullptr; 
  }
 
void loop() {
 
  esteira1 ++;
  esteira2 = random (0,1000);
  esteira3 = random(0,100000);
 
  static bool flag = false;
  if (!flag){
    client = new HTTPSRedirect (httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody (true);
    client->setContentTypeHeader("application/json");
}
  if (client != nullptr) {
    if (!client->connected()){
      client->connect (host, httpsPort);
      client->connect(host, httpsPort);
    }
  }
  else{
  Serial.println("Error creating client object!");
  }
 

  payload = payload_base + "\"" + value0 + "," + value1 + "," + value2 + "\"}";
 

  Serial.println("Publishing data...");
  Serial.println(payload);
  if(client->POST(url, host, payload)) {

  }
  else{
 
 
  Serial.println("Error while connecting");
  }
 
  delay(5000);
  }
