#include <Arduino.h>
#include "Switch.h"
#include "FrameTimer.h"

#define SWITCH_CB_TAG "switch_cb"

int switch_state;
int switch_debounce_count;
SwitchWorkerCallback *sw_callback;

void switch_Worker()
{
	int pinstate;
	pinstate = digitalRead(SWITCH_PIN);
	if (switch_state == pinstate)
	{
		switch_debounce_count = SWITCH_DEBOUNCE_COUNT;
	}
	else
	{
		switch_debounce_count--;
	}
	if (switch_debounce_count == 0)
	{
		switch_state = pinstate;
		// trigger the switch (decide if a bool ext, or a delegate callback)
		sw_callback();
	}
}

void switch_Init()
{
	pinMode(SWITCH_PIN, INPUT);
	switch_state = digitalRead(SWITCH_PIN);
	switch_debounce_count = SWITCH_DEBOUNCE_COUNT;
	ft_AddCallback(SWITCH_CB_TAG, switch_Worker);
}

void switch_AddCallback(SwitchWorkerCallback* cbfunc)
{
	sw_callback = cbfunc;
}

