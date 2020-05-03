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

void app_main()
{
	time_t now;
    display_init();
    rtc_ext_init();
    obtain_time();

    ESP_LOGI("time", "%d", (unsigned)time(&now));

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
		// get_from_nvs(&key);
		totp_init(MBEDTLS_MD_SHA1);
		// ESP_LOGI("time", "%d", ((unsigned)time(NULL))/30);
		totp_generate(key, ((unsigned)time(NULL))/30, 6, res);

	
		ESP_LOGI("hmac", "%s: %s", key, res);
		totp_free();
		display_write(res);
		// task_test_SSD1306i2c(res);
		vTaskDelay(100);
	}
}