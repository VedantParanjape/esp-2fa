#include "rtc.h"
#include "ntp.h"
#include "esp_log.h"

void app_main()
{
    rtc_ext_init();
    obtain_time();

    rtc_ext_set_time(time(NULL));
    while(1)
    {
        ESP_LOGI("rtc", "%lld", (long long)rtc_ext_get_time());
        vTaskDelay(100);
    }
}


// #include <stdio.h>
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
// #include <ds1307.h>
// #include <string.h>

// #if defined(CONFIG_IDF_TARGET_ESP8266)
// #define SDA_GPIO 4
// #define SCL_GPIO 5
// #else
// #define SDA_GPIO 5
// #define SCL_GPIO 18
// #endif

// void ds1307_test(void *pvParameters)
// {
//     i2c_dev_t dev;
//     memset(&dev, 0, sizeof(i2c_dev_t));

//     ESP_ERROR_CHECK(ds1307_init_desc(&dev, 0, SDA_GPIO, SCL_GPIO));

//     // setup datetime: 2018-04-11 00:52:10
//     struct tm time = {
//         .tm_year = 120, //since 1900 (2018 - 1900)
//         .tm_mon  = 4,  // 0-based
//         .tm_mday = 4,
//         .tm_hour = 1,
//         .tm_min  = 17,
//         .tm_sec  = 10
//     };
//     ESP_ERROR_CHECK(ds1307_set_time(&dev, &time));

//     while (1)
//     {
//         ds1307_get_time(&dev, &time);

//         printf("%04d-%02d-%02d %02d:%02d:%02d\n", time.tm_year + 1900 /*Add 1900 for better readability*/, time.tm_mon + 1,
//             time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);

//         vTaskDelay(500 / portTICK_PERIOD_MS);
//     }
// }

// void app_main()
// {
//     ESP_ERROR_CHECK(i2cdev_init());

//     xTaskCreate(ds1307_test, "ds1307_test", configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL);
// }