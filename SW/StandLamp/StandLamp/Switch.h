#pragma once
#define SWITCH_PIN 4
#define SWITCH_DEBOUNCE_COUNT 10

typedef void SwitchWorkerCallback(void);

void switch_Init();
void switch_AddCallback(SwitchWorkerCallback* cbfunc);
