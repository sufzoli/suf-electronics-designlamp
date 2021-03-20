
#include <FS.h>
#include <user_interface.h>

// ******* FastLed *******
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
#include "main.h"
#include "sr.h"
#include "Light.h"
#include "Server.h"
#include "FrameTimer.h"
#include "Switch.h"
#include "TermoSensor.h"

#define LIGHT_LWCB_TAG "light_lwcb"

#define FASTLED_PIN 14
#define FASTLED_NUM_PIX 72

#define FASTLED_COLOR_ORDER GRB
#define FASTLED_CHIPSET     WS2811
#define FASTLED_BRIGHTNESS  255

CRGB fastled_leds[FASTLED_NUM_PIX];

bool light_State;

void fastled_init()
{
	delay(3000); // sanity delay
	FastLED.addLeds<FASTLED_CHIPSET, FASTLED_PIN, FASTLED_COLOR_ORDER>(fastled_leds, FASTLED_NUM_PIX).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(FASTLED_BRIGHTNESS);
}


// ****** Frame Timer ********
// #define FRAMERATE 50

// os_timer_t frame_TimerObj;
// bool frame_IsProcess;

/*
void frame_TimerCallback(void *pArg)
{
	frame_IsProcess = true;
}

void init_FrameTimer()
{
	frame_IsProcess = false;
	os_timer_setfn(&frame_TimerObj, frame_TimerCallback, NULL);
	os_timer_arm(&frame_TimerObj, 1000 / FRAMERATE, true);
}
*/

// LightWorkerCallback *lwcb;
int stdRed = 0;
int stdGreen = 0;
int stdBlue = 0;

/*
void light_Worker()
{
	if (frame_IsProcess)
	{
		frame_IsProcess = false;
		lwcb();
		//    jb_Worker();
		//    fc_Worker();
		// fire_Worker();
	}
}
*/



void lwcb_Clear()
{
	int i;
	for (i = 0; i< FASTLED_NUM_PIX; i++)
	{
		fastled_leds[i] = CRGB::Black;
	}
	FastLED.show();
	ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Empty);
	// lwcb = lwcb_Empty;
	light_State = false;
	temp_Enabled(true);
}

void lwcb_Empty() {}


// ******* Jacob's Ladder *********
int jb_time = 100;
int jb_tc = 0; // time counter - used to calculate, when to show the next frame
int jb_pixc = 0; // pixel counter

void lwcb_Jacob()
{
	int i;
	if (jb_tc >= jb_time)
	{
		jb_tc = 0;
		for (i = 0; i< FASTLED_NUM_PIX; i++)
		{
			fastled_leds[i] = CRGB::Black;
		}
		fastled_leds[jb_pixc].setRGB(stdRed, stdGreen, stdBlue);
		FastLED.show();
		jb_pixc++;
		if (jb_pixc > FASTLED_NUM_PIX)
		{
			jb_pixc = 0;
		}
	}
	else
	{
		jb_tc += FT_FRAMERATE;
	}
	light_State = true;
	temp_Enabled(false);
}

// ******** Full light **********
void lwcb_FullLight()
{
	int i;
	for (i = 0; i< FASTLED_NUM_PIX; i++)
	{
		fastled_leds[i].setRGB(stdRed, stdGreen, stdBlue);
	}
	FastLED.show();
	light_State = true;
	temp_Enabled(false);
}

void lwcb_Fake()
{
	int i,j,k,width,empty;
	width = FASTLED_NUM_PIX / 24;
	empty = FASTLED_NUM_PIX / 6;
	j = 0;
	for (i = 0; i < FASTLED_NUM_PIX; i++)
	{
		fastled_leds[i] = CRGB::Black;
	}
	for (i = 0; i < 4; i++)
	{
		j += empty;
		k = j + width;
		fastled_leds[j-1].setRGB(255, 255, 255);
		for (; j < k; j++)
		{
			fastled_leds[j].setRGB(255, 255, 255);
		}
		fastled_leds[j].setRGB(255, 255, 255);
	}
	FastLED.show();
	ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Empty);
	// lwcb = lwcb_Empty;
	light_State = true;
	temp_Enabled(false);
}


void lwcb_Flash()
{
	int i;
	for (i = 0; i< FASTLED_NUM_PIX; i++)
	{
		fastled_leds[i].setRGB(255,255,255);
	}
	FastLED.show();
	ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Clear);
	// lwcb = lwcb_Clear;
}

int strobe_state=0;
int strobe_off = 5;
void lwcb_Strobe()
{
	int i;
	if (strobe_state == 0)
	{
		for (i = 0; i < FASTLED_NUM_PIX; i++)
		{
			fastled_leds[i].setRGB(255, 255, 255);
		}
	}
	else
	{
		for (i = 0; i < FASTLED_NUM_PIX; i++)
		{
			fastled_leds[i].setRGB(0, 0, 0);
		}
	}
	FastLED.show();
	if (strobe_state < strobe_off)
	{
		strobe_state++;
	}
	else
	{
		strobe_state = 0;
	}
	light_State = true;
	temp_Enabled(false);
}

#define LIGHT_SIREN_ROTATION 200

byte light_siren_pos;
int light_siren_frame_pos;

void lwcb_Siren()
{
	int i;
	temp_Enabled(false);
	if (light_siren_frame_pos == 0)
	{
		// clear
		for (i = 0; i< FASTLED_NUM_PIX; i++)
		{
			fastled_leds[i].setRGB(0,0,0);
		}
		FastLED.show();

		// Reset frame counter
		light_siren_frame_pos = LIGHT_SIREN_ROTATION;

		// shift the position
		// light_siren_pos <<= 1;
		// if overflowed reset to one
		if (light_siren_pos == 0)
		{
			light_siren_pos = 1;
		}
		// set the position
		SR_Set(light_siren_pos);
		// set color
		for (i = 0; i< FASTLED_NUM_PIX; i++)
		{
			fastled_leds[i].setRGB(stdRed, stdGreen, stdBlue);
		}
		FastLED.show();
	}
	else
	{
		light_siren_frame_pos--;
	}
}


// ******* Fire ********



// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 50, suggested range 20-100 
int fireCooling = 55;

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
int fireSparking = 120;

bool gReverseDirection = false;

void lwcb_Fire()
{
	// Array of temperature readings at each simulation cell
	static byte heat[FASTLED_NUM_PIX];

	// Step 1.  Cool down every cell a little
	for (int i = 0; i < FASTLED_NUM_PIX; i++) {
		heat[i] = qsub8(heat[i], random8(0, ((fireCooling * 10) / FASTLED_NUM_PIX) + 2));
	}

	// Step 2.  Heat from each cell drifts 'up' and diffuses a little
	for (int k = FASTLED_NUM_PIX - 1; k >= 2; k--) {
		heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
	}

	// Step 3.  Randomly ignite new 'sparks' of heat near the bottom
	if (random8() < fireSparking) {
		int y = random8(7);
		heat[y] = qadd8(heat[y], random8(160, 255));
	}

	// Step 4.  Map from heat cells to LED colors
	for (int j = 0; j < FASTLED_NUM_PIX; j++) {
		CRGB color = HeatColor(heat[j]);
		int pixelnumber;
		if (gReverseDirection) {
			pixelnumber = (FASTLED_NUM_PIX - 1) - j;
		}
		else {
			pixelnumber = j;
		}
		fastled_leds[pixelnumber] = color;
	}
	// Step 5.  Display it
	FastLED.show();
	light_State = true;
	temp_Enabled(false);
}

void light_switch()
{
	if (light_State)
	{
		ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Clear);
	}
	else
	{
		ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Fake);
	}
}

void light_MyFire()
{
	ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Fire);
}

int light_sw_prev = 0;

void SetVal()
{
	int i;
	String xml;
#ifdef SERIAL_DEBUG
	Serial.print("WEB: File request - ");
	Serial.println(web_GetUri());
	/*
	Serial.print("GPIO4: ");
	Serial.print(digitalRead(4));
	Serial.print(" GPIO5: ");
	Serial.println(digitalRead(5));
	*/
#endif
	for (i = 0; i < server.args(); i++)
	{
		if (server.argName(i) == "stdcolr")
		{
			stdRed = server.arg(i).toInt();
		}
		if (server.argName(i) == "stdcolg")
		{
			stdGreen = server.arg(i).toInt();
		}
		if (server.argName(i) == "stdcolb")
		{
			stdBlue = server.arg(i).toInt();
		}
		if (server.argName(i) == "firecooling")
		{
			fireCooling = server.arg(i).toInt();
		}
		if (server.argName(i) == "firesparking")
		{
			fireSparking = server.arg(i).toInt();
		}
		if (server.argName(i) == "sw")
		{
			if (light_sw_prev != server.arg(i).toInt())
			{
				SR_SetFull();
				switch (server.arg(i).toInt())
				{
				case 0:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Clear);
					break;
				case 1:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_FullLight);
					break;
				case 2:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Jacob);
					break;
				case 3:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Fire);
					break;
				case 4:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Flash);
					break;
				case 5:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Strobe);
					break;
				case 6:
					light_siren_pos = 1;
					light_siren_frame_pos = LIGHT_SIREN_ROTATION;
					lwcb_Clear();
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Siren);
					break;
				default:
					ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Clear);
					break;
				}
				light_sw_prev = server.arg(i).toInt();
			}
		}
	}
	xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
	xml += "<DesignLamp>";
	xml += "<stdcol_r>" + String(stdRed) + "</stdcol_r>";
	xml += "<stdcol_g>" + String(stdGreen) + "</stdcol_g>";
	xml += "<stdcol_b>" + String(stdBlue) + "</stdcol_b>";
	xml += "<fire_cooling>" + String(fireCooling) + "</fire_cooling>";
	xml += "<fire_sparking>" + String(fireSparking) + "</fire_sparking>";
	xml += "</DesignLamp>";
	
	server.send(200, "text/xml", xml);
}


void light_init()
{
	ft_AddCallback(LIGHT_LWCB_TAG, lwcb_Empty);
	// lwcb = lwcb_Empty;
	web_RegisterPostUrl("/api/setval", SetVal);
	// init_FrameTimer();
	SR_Setup();
	SR_SetFull();
	fastled_init();
	light_State = false;
	switch_AddCallback(light_switch);
	temp_AddCallback(light_MyFire);
	temp_Enabled(true);
}
