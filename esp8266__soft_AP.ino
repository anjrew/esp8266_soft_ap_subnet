

// Librarys
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <Ticker.h>
#include <EEPROM.h>

// Files
#include "credentials.h"
#include "helpers.h"
#include "global.h"
#include "NTP.h"

// Variables
#define SSID_CODE "ESPsoftAP_01"
IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

//
//
//// The Webserver
//ESP8266WebServer server(80);           

// PAGES
#include "Page_Root.h"
#include "Page_Admin.h"
#include "Page_Script.js.h"
#include "Page_Style.css.h"
#include "Page_NTPsettings.h"
#include "Page_Information.h"
#include "Page_General.h"
#include "Page_applSettings.h"
#include "PAGE_NetworkConfiguration.h"
#include "example.h"

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
}


void setupSoftAp()
{
  Serial.print("Setting up the soft access point");
  WiFi.begin("");
  WiFi.mode(WIFI_AP_STA);
  bool setUpSuccess = WiFi.softAP(SSID_CODE, "password");
  delay(100);
  Serial.println(setUpSuccess ? "Ready" : "Failed!");
  delay(1000);
  Serial.print("Soft-AP local network IP address = ");
  Serial.println(WiFi.softAPIP());
}

void setupRoutes(){
  Serial.println("Setting up routes");
    server.on ( "/", []() {
        Serial.println("Got route '/' and sending admin.html");
        server.send ( 200, "text/html", PAGE_AdminMainPage );  // const char top of page
      }  );

      server.on ( "", []() {
        Serial.println("Got route '' and sending admin.html");
        server.send ( 200, "text/html", PAGE_AdminMainPage );  // const char top of page
      }  );
      
      server.on ( "/favicon.ico",   []() {
        Serial.println("favicon.ico");
        server.send ( 200, "text/html", "" );
      }  );

//      // Network config
      server.on ( "/config.html", send_network_configuration_html );
      // Info Page
      server.on ( "/info.html", []() {
        Serial.println("info.html");
        server.send ( 200, "text/html", PAGE_Information );
      }  );
      server.on ( "/ntp.html", send_NTP_configuration_html  );

      server.on ( "/appl.html", send_application_configuration_html  );
      server.on ( "/general.html", send_general_html  );
      //  server.on ( "/example.html", []() { server.send ( 200, "text/html", PAGE_EXAMPLE );  } );
      server.on ( "/style.css", []() {
        Serial.println("style.css");
        server.send ( 200, "text/plain", PAGE_Style_css );
      } );
      server.on ( "/microajax.js", []() {
        Serial.println("microajax.js");
        server.send ( 200, "text/plain", PAGE_microajax_js );
      } );
      server.on ( "/admin/values", send_network_configuration_values_html );
      server.on ( "/admin/connectionstate", send_connection_state_values_html );
      server.on ( "/admin/infovalues", send_information_values_html );
      server.on ( "/admin/ntpvalues", send_NTP_configuration_values_html );
      server.on ( "/admin/applvalues", send_application_configuration_values_html );
      server.on ( "/admin/generalvalues", send_general_configuration_values_html);
      server.on ( "/admin/devicename",     send_devicename_value_html);


      server.onNotFound ( []() {
        Serial.println("Page Not Found sorry!");
        server.send ( 400, "text/html", "Page not Found soz" );
      }  );
  }
