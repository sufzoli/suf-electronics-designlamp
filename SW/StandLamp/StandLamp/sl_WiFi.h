#pragma once
#define WIFI_TIMEOUT	20
#define WIFI_AP_NAME_PREFIX "STANDLAMP"

void wifi_off();
bool wifi_Init_ClientMode(String ssid, String password);
void wifi_Init_APMode();