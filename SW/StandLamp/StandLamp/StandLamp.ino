/*
 Name:		StandLamp.ino
 Created:	11/26/2016 4:54:08 AM
 Author:	zoli
*/
// #include <WiFiUdp.h>
// #include <WiFiServer.h>
// #include <WiFiClientSecure.h>
#include <WiFiClient.h>
// #include <ESP8266WiFiType.h>
// #include <ESP8266WiFiSTA.h>
// #include <ESP8266WiFiScan.h>
// #include <ESP8266WiFiMulti.h>
// #include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include "main.h"
#include "sl_WiFi.h"
#include "fs_spiffs.h"
#include "Settings.h"


#define SERIAL_DEBUG
#define SERIAL_BAUD 115200

void init_wifi()
{
	
}


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
		is_wifi_client = wifi_Init_ClientMode(settings_getValue("wlan", "ssid"), settings_getValue("wlan", "password"));
	}
	// Fall back to AP mode
	if (!is_wifi_client)
	{
		wifi_Init_APMode();
	}
}

// the loop function runs over and over again until power down or reset
void loop()
{
  
}
