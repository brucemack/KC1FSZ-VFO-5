#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Setup.h"

extern "C" {
	#include "ssd1306.h"
	#include "Rotary.h"
}

#include "I2CInterface.h"
#include "si5351a.h"

extern I2C_HandleTypeDef hi2c1;
static kc1fsz::I2CInterface ic21(&hi2c1);

int freq = 7255000;

// NOTE: Don't forget to update the screen after calling this
static void displayFreq() {
	char buf[32];
	int x = 50;
	// Print whole KHz
	sprintf(buf,"%5d",freq / 1000);
	ssd1306_SetCursor(x, 16);
	ssd1306_WriteString(buf, Font_11x18, White);
	// Print 100Hz increments
	sprintf(buf,".%d",(freq % 1000) / 100);
	ssd1306_SetCursor(x + 55, 16);
	ssd1306_WriteString(buf, Font_11x18, White);
}

void Setup_init() {

	si5351aInit(&ic21);

	// ----- SD1306 OLED
	ssd1306_Init();

	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString((char*)"KC1FSZ", Font_7x10, White);
	for (int x = 0; x < 128; x++)
		ssd1306_DrawPixel(x, 12, White);

	si5351aSetFrequency(freq);
	displayFreq();
	ssd1306_UpdateScreen();
}

void Setup_loop() {

	int d = Rotary_process();

	if (d != DIR_NONE) {

		if (d == DIR_CW) {
			freq += 500;
		} else if (d == DIR_CCW) {
			freq -= 500;
		}

		si5351aSetFrequency(freq);
		displayFreq();
		ssd1306_UpdateScreen();
	}
}
