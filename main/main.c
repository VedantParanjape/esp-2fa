#include "ntp.h"
#include "display.h"

void app_main()
{
    time_t now;
    struct tm timeinfo;

    obtain_time();
    init_display(&display);
    setenv("TZ", "IST-05:30:00", 1);
    tzset();

    SSD1306_SetContrast(&display, 0xFF);
    while (1)
    {
        clear_display(&display);

        time(&now);
        localtime_r(&now, &timeinfo);
        char *buffer = (char*)malloc(sizeof(char)*30);
        memset(buffer, '\0', 100);
        
        if (timeinfo.tm_min < 10 && timeinfo.tm_sec < 10)
        {
            sprintf(buffer, "%d:0%d:0%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }
        else if(timeinfo.tm_min > 10 && timeinfo.tm_sec < 10)
        {
            sprintf(buffer, "%d:%d:0%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }
        else if(timeinfo.tm_min < 10 && timeinfo.tm_sec > 10)
        {
            sprintf(buffer, "%d:0%d:%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }
        else
        {
            sprintf(buffer, "%d:%d:%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        }
        
        set_font_display(&display, &Font_droid_sans_fallback_24x28);
        write_display(&display, TextAnchor_North ,buffer);
        
        sprintf(buffer, "%d/%d/%d", timeinfo.tm_mday, timeinfo.tm_mon, timeinfo.tm_year+1900);
        set_font_display(&display, &Font_droid_sans_fallback_11x13);
        write_display(&display, TextAnchor_Center, "Google");


        // ESP_LOGI("main app", "%d:%d:%d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
        vTaskDelay(100/portTICK_PERIOD_MS);
        free((void*)buffer);
    }
}