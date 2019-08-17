
#include <ESP8266WiFi.h>


void setup() {
  Serial.begin(115200);
  Serial.println("Running setup");
  setupSoftAp();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin("ESP", "password");
  
}

void loop() {
  // put your main code here, to run repeatedly:
   delay(1000);
   Serial.println("Done loop");
}


void setupSoftAp()
{
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("ESPsoftAP_01", "password") ? "Ready" : "Failed!");

  Serial.print("Soft-AP local network IP address = ");
  Serial.println(WiFi.softAPIP());
}
