#include "rtc.h"
#include "esp_log.h"

void app_main()
{
    rtc_ext_init();

    rtc_ext_set_time((time_t)100);
    while(1)
    {
        ESP_LOGI("rtc", "%lld", (long long)rtc_ext_get_time());
        vTaskDelay(100);
    }
}