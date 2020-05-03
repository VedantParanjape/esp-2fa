#include "rtc.h"

static i2c_dev_t dev;

void rtc_ext_init()
{
    ESP_ERROR_CHECK(i2cdev_init());

    memset(&dev, 0, sizeof(i2c_dev_t));
    ESP_ERROR_CHECK(ds1307_init_desc(&dev, 0, SDA_GPIO, SCL_GPIO));

    xTaskCreatePinnedToCore(&rtc_periodic_update, "rtc_periodic_update_task", 2048, NULL, 2, NULL, 0);
}

void rtc_ext_set_time(time_t time)
{
    while(ds1307_set_time(&dev, localtime(&time)) != ESP_OK)
    {
        ESP_LOGE("rtc", "%s: %s", "setting rtc time", asctime(localtime(&time)));
    }

    ESP_LOGI("rtc", "%lld", (long long)time);
}

time_t rtc_ext_get_time()
{
    struct tm time;
    while(ds1307_get_time(&dev, &time) != ESP_OK);

    return mktime(&time);
}

void rtc_periodic_update()
{
    while (1)
    {
        time_t time = rtc_ext_get_time();
        struct timeval tm = {.tv_sec = time};

        settimeofday(&tm, NULL);
        ESP_LOGI("rtc", "%s: %lld", "periodic time update from RTC", (long long)time);

        vTaskDelay(6000);
     
    }
}
