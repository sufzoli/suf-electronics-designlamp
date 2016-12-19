#pragma once

#define FT_FRAMERATE 50

typedef void ftWorkerCallback(void);


void ft_Init();
void ft_Worker();
void ft_AddCallback(String ID, ftWorkerCallback* cbFunc);
void ft_DelCallback(String ID);