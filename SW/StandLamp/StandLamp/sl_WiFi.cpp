#include <FS.h>
#include <user_interface.h>
#include <IPAddress.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

#include "main.h"
#include "sl_WiFi.h"

DNSServer _dnsServer;


void wifi_off()
{
	WiFi.softAPdisconnect();
	WiFi.disconnect();
	WiFi.mode(WIFI_OFF);
	delay(100);
}

bool wifi_Init_ClientMode(String ssid, String password)
{
	int i;
	bool retval;
	wl_status_t wifistate;
	WiFi.mode(WIFI_STA);
	delay(100);

#ifdef SERIAL_DEBUG
	Serial.println("Wi-Fi: Client Mode");
	Serial.print("Wi-Fi: Connecting to ");
	Serial.println(ssid);
#endif
	WiFi.begin(ssid.c_str(), password.c_str());
	for(i=0; (i < WIFI_TIMEOUT*2) && (WiFi.status() != WL_CONNECTED);i++)
	{
#ifdef SERIAL_DEBUG
		Serial.print(".");
//		Serial.println(WiFi.status());
#endif
		delay(500);
	}
	wifistate = WiFi.status();
	retval = wifistate == WL_CONNECTED;
#ifdef SERIAL_DEBUG
	Serial.println();
	switch (wifistate)
	{
		case WL_IDLE_STATUS:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_IDLE_STATUS");
			break;
		case WL_NO_SSID_AVAIL:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_NO_SSID_AVAIL");
			break;
		case WL_SCAN_COMPLETED:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_SCAN_COMPLETED");
			break;
		case WL_CONNECTED:
			Serial.print("Wi-Fi: Connected - ");
			Serial.println(WiFi.localIP());
			break;
		case WL_CONNECT_FAILED:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_CONNECT_FAILED");
			break;
		case WL_CONNECTION_LOST:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_CONNECTION_LOST");
			break;
		case WL_DISCONNECTED:
			Serial.print("Wi-Fi: Failed - ");
			Serial.println("WL_DISCONNECTED");
			break;
		default:
			break;
	}
#endif
	return retval;
}

void wifi_Init_APMode()
{
	String ssid = WIFI_AP_NAME_PREFIX + String(ESP.getChipId());
	WiFi.mode(WIFI_AP);
	delay(100);
#ifdef SERIAL_DEBUG
	Serial.println("Wi-Fi: AP Mode");
#endif
	WiFi.softAP(ssid.c_str());
#ifdef SERIAL_DEBUG
	Serial.println("Wi-Fi: AP Started:");
	Serial.print("    SSID: ");
	Serial.println(ssid);
	Serial.print("    PWD : ");
	Serial.println("None");
	Serial.print("    IP  : ");
	Serial.println(WiFi.localIP());
#endif
}

void wifi_startCaptive(ESP8266WebServer srv)
{
	_dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
	// _dnsServer.start(53, "*", WiFi.localIP);
}

void wifi_stopCaptive(ESP8266WebServer srv)
{
	_dnsServer.stop();
}
