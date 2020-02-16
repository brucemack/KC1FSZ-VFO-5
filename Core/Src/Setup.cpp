#include "Setup.h"
#include "I2CInterface.h"
#include "si5351a.h"

extern I2C_HandleTypeDef hi2c1;
static kc1fsz::I2CInterface ic21(&hi2c1);

void Setup_init() {
	si5351aInit(&ic21);
	si5351aSetFrequency(10000000);
}

