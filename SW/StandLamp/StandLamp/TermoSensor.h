#pragma once
typedef void TempWorkerCallback(void);
void temp_Init();
void temp_AddCallback(TempWorkerCallback* tempcb);