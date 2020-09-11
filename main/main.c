#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <u8g2.h>

#include "sdkconfig.h"
#include "u8g2_esp32_hal.h"
#include "ntp.h"
#include "totp.h"
#include "nvs.h"
#include "display.h"
#include "rtc.h"
#include "sync.h"

void authenticator()
{
	display_init();

	char res[10];
	char *key = NULL;

	get_from_nvs(&key);
	save_to_nvs("donikc64w6qaqjnrezzheynhsoj5fgj4q63gjn5kedqw7k5n5i2efkr5");
	
	if (key == NULL)
	{
		save_to_nvs("donikc64w6qaqjnrezzheynhsoj5fgj4q63gjn5kedqw7k5n5i2efkr5");
		get_from_nvs(&key);
	}
	
	while(1)
	{
		totp_init(MBEDTLS_MD_SHA1);
		totp_generate(key, ((unsigned)time(NULL))/30, 6, res);	
		// ESP_LOGI("hmac", "%s: %s", key, res);
		totp_free();

		display_write(res);
		vTaskDelay(100);
	}
}

void app_main()
{
	xTaskCreatePinnedToCore(sync_time, "sync_time", 4096, NULL, 1, NULL, 0);
	vTaskDelay(1000 / portTICK_PERIOD_MS);	
    xTaskCreatePinnedToCore(authenticator, "2fa", 4096, NULL, 2, NULL, 1);
}