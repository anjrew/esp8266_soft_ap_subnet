


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>

// Variables
#define SSID "ESPsoftAP_01"
IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);


// The Webserver
ESP8266WebServer server(80);           

// PAGES
#include "Page_Admin.h"
//#include "global.h"


void setup() {
  
  EEPROM.begin(512);
  Serial.begin(115200);
  Serial.println("Running setup");
  setupSoftAp();
  server.begin();
  setupRoutes();
  Serial.println("Setup Finished");
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
    server.handleClient();
    Serial.println("Loop");
    delay(1000);
}


void setupSoftAp()
{
  Serial.print("Setting up the soft access point");
  WiFi.begin("");
  WiFi.mode(WIFI_AP_STA);
//  Serial.print("Setting soft-AP configuration ... ");
//  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  bool setUpSuccess = WiFi.softAP(SSID, "password");
  delay(100);
  Serial.println(setUpSuccess ? "Ready" : "Failed!");
  delay(1000);
  Serial.print("Soft-AP local network IP address = ");
  Serial.println(WiFi.softAPIP());
}

void setupRoutes(){
  Serial.println("Setting up routes");
  // Admin page
      server.on ( "/", []() {
        Serial.println("admin.html");
        server.send ( 200, "text/html", PAGE_AdminMainPage );  // const char top of page
      }  );
  }
