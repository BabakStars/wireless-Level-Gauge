#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include<ESP8266HTTPClient.h>
#include "index.h"
ESP8266WebServer server(80);
IPAddress local_IP(192,168,1,150);
IPAddress subnet(255,255,255,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  pinMode(D0,OUTPUT);
  pinMode(D1,INPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,local_IP,subnet);
  WiFi.softAP("Tank1","123456789");
  server.on("/",Root);
  server.on("/SET",SET);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void Root() {
  server.send(200,"text/html",index_page);

}
void SET() {
  String pass = server.arg("password");
  if(pass == "1234")
  {
    long duration, dist;
  digitalWrite(D0,0);   //D0 trig
  delayMicroseconds(2);
  digitalWrite(D0,1);
  delayMicroseconds(10);
  digitalWrite(D0,0);
  duration = pulseIn(D1,HIGH);   //D1 echo
  dist = duration * .017;
  Serial.println(dist);
  String sending = String(dist);
  server.send(200,"text/plain",sending);
  }
  
  
}
