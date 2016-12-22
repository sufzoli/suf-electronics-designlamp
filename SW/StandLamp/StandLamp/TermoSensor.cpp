#include <OneWire.h>
#include <DallasTemperature.h>

#include "main.h"
#include "FrameTimer.h"
#include "TermoSensor.h"

#define ONE_WIRE_BUS 5
#define TEMP_INTERVALL 50
#define TEMP_CB_TAG "temp_cb"

#define TEMP_HYSTERESIS 1.0

TempWorkerCallback *tempalarm;

float temp_ValueFloat;
char temp_ValueStr[6];
int temp_interval;

bool _temp_en = true;

float tempArr[10];

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
/*
void temp_ReadSensor()
{
	int i;
	for (i = 0; i<10; i++)
	{
		DS18B20.requestTemperatures();
		temp_ValueFloat = DS18B20.getTempCByIndex(0);
		if (temp_ValueFloat != 85.0 && temp_ValueFloat != (-127.0))
		{
			dtostrf(temp_ValueFloat, 2, 2, temp_ValueStr);
			break;
		}
		delay(10);
	}
	#ifdef SERIAL_DEBUG
		Serial.print("Temp: ");
		Serial.println(temp_ValueStr);
	#endif
}

void temp_Worker()
{
	int i;
	temp_interval++;
	if (temp_interval >= TEMP_INTERVALL)
	{
		temp_ReadSensor();
		if ((tempArr[0] + TEMP_HYSTERESIS) < temp_ValueFloat)
		{
			// signal fire
			tempalarm();
		}
		// shift array
		for (i = 0; i < 9; i++)
		{
			tempArr[i] = tempArr[i + 1];
		}
		tempArr[9] = temp_ValueFloat;
		temp_interval = 0;
	}
}
*/

bool temp_ready;

void temp_ReadSensor()
{
	int i;
	for (i = 0; i<10; i++)
	{
		DS18B20.requestTemperatures();
		temp_ValueFloat = DS18B20.getTempCByIndex(0);
		if (temp_ValueFloat != 85.0 && temp_ValueFloat != (-127.0))
		{
			dtostrf(temp_ValueFloat, 2, 2, temp_ValueStr);
			break;
		}
		delay(10);
	}
#ifdef SERIAL_DEBUG
	Serial.print("Temp: ");
	Serial.println(temp_ValueStr);
#endif
}

void temp_Worker()
{
	int i;
	if (_temp_en)
	{
		temp_interval++;
		if (!temp_ready)
		{
			DS18B20.requestTemperatures();
			temp_ValueFloat = DS18B20.getTempCByIndex(0);
			if (temp_ValueFloat != 85.0 && temp_ValueFloat != (-127.0))
			{
				dtostrf(temp_ValueFloat, 2, 2, temp_ValueStr);
				temp_ready = true;
			}
		}
		if (temp_interval >= TEMP_INTERVALL)
		{
			// temp_ReadSensor();
			if ((tempArr[0] + TEMP_HYSTERESIS) < temp_ValueFloat)
			{
				// signal fire
				tempalarm();
			}
			// shift array
			for (i = 0; i < 9; i++)
			{
				tempArr[i] = tempArr[i + 1];
			}
			tempArr[9] = temp_ValueFloat;
			temp_interval = 0;
			temp_ready = false;
		}
	}
}




void temp_Init()
{
	int i;
	temp_ReadSensor();
	for (i = 0; i < 10; i++)
	{
		tempArr[i] = temp_ValueFloat;
	}
	ft_AddCallback(TEMP_CB_TAG, temp_Worker);
	temp_interval = 0;
}

void temp_AddCallback(TempWorkerCallback* tempcb)
{
	tempalarm = tempcb;
}

void temp_Enabled(bool en)
{
	int i;
	if (en)
	{
		if (!_temp_en)
		{
			temp_ReadSensor();
			for (i = 0; i < 10; i++)
			{
				tempArr[i] = temp_ValueFloat;
			}
			_temp_en = true;
			temp_interval = 0;
		}
	}
	else
	{
		_temp_en = false;
	}
}