#include "display.h"

static const char* tag = "display";
static u8g2_t u8g2;

void display_init()
{
    u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	u8g2_esp32_hal.sda   = PIN_SDA;
	u8g2_esp32_hal.scl  = PIN_SCL;
	u8g2_esp32_hal_init(u8g2_esp32_hal);

	u8g2_Setup_ssd1306_i2c_128x32_univision_f(
		&u8g2,
		U8G2_R0,
		//u8x8_byte_sw_i2c,
		u8g2_esp32_i2c_byte_cb,
		u8g2_esp32_gpio_and_delay_cb);
	u8x8_SetI2CAddress(&u8g2.u8x8,0x78);

	ESP_LOGI(tag, "u8g2_InitDisplay");
	u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,

	ESP_LOGI(tag, "u8g2_SetPowerSave");
	u8g2_SetPowerSave(&u8g2, 0); // wake up display
	ESP_LOGI(tag, "u8g2_ClearBuffer");
	u8g2_ClearDisplay(&u8g2);
}

void display_write(char* totp)
{
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_luBIS12_te);
    u8g2_DrawStr(&u8g2, 25, 19, totp);
	u8g2_DrawBox(&u8g2, 4, 28, 4*((unsigned)time(NULL)%30), 4);
    ESP_LOGI(tag, "u8g2_SendBuffer");   
	u8g2_SendBuffer(&u8g2);
}