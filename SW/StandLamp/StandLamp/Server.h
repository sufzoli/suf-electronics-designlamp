#pragma once
#include <ESP8266WebServer.h>
extern ESP8266WebServer server;

void web_Init();
void web_Worker();
// void web_RegisterUrl(const char* uri, HTTPMethod method, std::function<void(void)> ufn);
void web_RegisterGetUrl(const char* uri, std::function<void(void)> ufn);
String web_GetUri();