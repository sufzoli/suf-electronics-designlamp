#include <FS.h>
#include <user_interface.h>
#include "Settings.h"
#include "HashMap.h"

CreateHashMap(_settings, String, String, 20);

bool settings_LoadConfig()
{
	File configFile;
	String currentLine;
	String currentSection = "";
	String key;
	String hashKey;
	String value;
	int eqIndex;
	const char* hashKeyPtr;
	if (SPIFFS.exists(SETTINGS_PATH))
	{
#ifdef SERIAL_DEBUG
		Serial.print("SETTINGS: Reading config from ");
		Serial.println(SETTINGS_PATH);
#endif
		configFile = SPIFFS.open(SETTINGS_PATH, "r");
		if (configFile)
		{
			do
			{
				currentLine = configFile.readStringUntil('\n');
				// Section testing
				currentLine.trim(); // remove spaces
				if (currentLine.startsWith("[") && currentLine.endsWith("]"))
				{
					// This is a section
					currentSection = currentLine.substring(1, currentLine.length() - 1);
				}
				else
				{
					// This is a line
					if (currentSection != "")
					{
						eqIndex = currentLine.indexOf('=');
						if (eqIndex)
						{
							key = currentLine.substring(0, eqIndex);
							key.trim();
							value = currentLine.substring(eqIndex + 1);
							value.trim();
							if (value.startsWith("\"") && value.endsWith("\""))
							{
								value = value.substring(1, value.length() - 1);
							}
							_settings["/" + currentSection + "/" + key] = value;
							Serial.print(currentSection);
							Serial.print(" - ");
							Serial.print(key);
							Serial.print(" - ");
							Serial.println(value);
						}
					}
				}
			} while (configFile.position() < configFile.size());
			configFile.close();
		}
		else
		{
#ifdef SERIAL_DEBUG
			Serial.println("SETTINGS: File open failed");
#endif      
			return false;
		}
	}
	return true;
}

String settings_getValue(String section, String key)
{
	return _settings["/" + section + "/" + key];
}

void settings_saveConfig()
{

}