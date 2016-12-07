#pragma once
#include <user_interface.h>

#define SETTINGS_PATH "/config.ini"

bool settings_LoadConfig();
String settings_getValue(String section, String key);
