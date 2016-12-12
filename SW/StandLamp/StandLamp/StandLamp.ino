/*
 Name:		StandLamp.ino
 Created:	11/26/2016 4:54:08 AM
 Author:	zoli
*/

#include <FS.h>
#include <user_interface.h>
#include <IPAddress.h>
// #include <WiFiUdp.h>
// #include <WiFiServer.h>
// #include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
// #include <ESP8266WiFiSTA.h>
// #include <ESP8266WiFiScan.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include <FastLED.h>

#include "main.h"
#include "HashMap.h"
#include "sl_WiFi.h"
#include "fs_spiffs.h"
#include "Settings.h"
#include "Server.h"
#include "Light.h"

/*
void SetVal()
{
#ifdef SERIAL_DEBUG
	Serial.print("WEB: File request - ");
	Serial.println(web_GetUri());
#endif
	server.send(200, "text/plain", "");
}
*/

// the setup function runs once when you press reset or power the board
void setup()
{
	bool fs_on;
	bool config_loaded = false;
	bool is_wifi_client = false;
#ifdef SERIAL_DEBUG
	Serial.begin(SERIAL_BAUD);
	delay(10);
	Serial.println();
#endif
	fs_on = fs_init();
	if (fs_on)
	{
		config_loaded = settings_LoadConfig();
	}
	if (config_loaded)
	{
		wifi_off();
		is_wifi_client = wifi_Init_ClientMode(settings_getValue("wlan", "ssid"), settings_getValue("wlan", "password"));
	}
	// Fall back to AP mode
	if (!is_wifi_client)
	{
		wifi_off();
		wifi_Init_APMode();
	}
	web_Init();
//	server.on("/setval", HTTP_GET, []() { server.send(200, "text/plain", ""); }, SetVal);
//	server.on("/setval", HTTP_GET, []() { server.send(200, "text/plain", ""); }, []() { Serial.println(server.uri); });
	light_init();

//	pinMode(4, INPUT);
//	pinMode(5, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop()
{
	web_Worker();
	light_Worker();
}
