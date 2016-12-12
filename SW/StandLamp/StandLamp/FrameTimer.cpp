#include "Arduino.h"
#include "WString.h"
#include "HashMap.h"
#include <user_interface.h>
#include "FrameTimer.h"

CreateHashMap(_ftCallback, String, ftWorkerCallback*, 20);

os_timer_t ft_TimerObj;
bool ft_IsProcess;

void ft_Init()
{
	ft_IsProcess = false;
	os_timer_setfn(&ft_TimerObj, ft_TimerCallback, NULL);
	os_timer_arm(&ft_TimerObj, 1000 / FT_FRAMERATE, true);
}

void ft_Worker()
{
	int i;
	for (i = 0; i < _ftCallback.size(); i++)
	{
		_ftCallback.valueAt(i)();
	}
}

void ft_TimerCallback(void *pArg)
{
	ft_IsProcess = true;
}

void ft_AddCallback(String ID, ftWorkerCallback* cbFunc)
{
	_ftCallback[ID] = cbFunc;
}

void ft_DelCallback(String ID)
{
	_ftCallback.remove(ID);
}