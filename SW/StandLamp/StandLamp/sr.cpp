#include <Arduino.h>
#include "sr.h"

void SR_SetFull()
{
	digitalWrite(SR_D_PIN, 1);
	for (int i = 0; i<8; i++)
	{
		digitalWrite(SR_CP_PIN, 0);
		delay(1);
		digitalWrite(SR_CP_PIN, 1);
		delay(1);
	}
}

void SR_Set(byte data)
{
	for (int i = 0; i<8; i++)
	{
		// set bit
		digitalWrite(SR_D_PIN, data & 0x80 ? 1 : 0);
		data = data << 1;
		delay(1);
		// toggle clock
		digitalWrite(SR_CP_PIN, 0);
		delay(1);
		digitalWrite(SR_CP_PIN, 1);
		delay(1);
	}
}


void SR_Clear()
{
	digitalWrite(SR_D_PIN, 0);
	for (int i = 0; i<8; i++)
	{
		digitalWrite(SR_CP_PIN, 0);
		delay(1);
		digitalWrite(SR_CP_PIN, 1);
		delay(1);
	}
}

void SR_Setup()
{
	pinMode(SR_D_PIN, OUTPUT);
	pinMode(SR_CP_PIN, OUTPUT);
	SR_Clear();
}
