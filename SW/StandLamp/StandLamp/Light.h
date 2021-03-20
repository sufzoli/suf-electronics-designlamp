#pragma once

typedef void LightWorkerCallback(void);

extern bool light_State;

void lwcb_Fire();
void lwcb_Jacob();

void lwcb_Empty();
void lwcb_Clear();

void lwcb_FullLight();
void lwcb_Fake();
void lwcb_Flash();
void lwcb_Strobe();
void lwcb_Siren();

void light_Worker();
void light_init();
