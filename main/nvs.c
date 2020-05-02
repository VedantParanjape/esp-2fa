#include "nvs.h"

static const char *tag = "nvs";

void save_to_nvs(char* message)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    { 
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_LOGI(tag, "%s", "opening non-volatile storage (NVS)");
    nvs_handle handle;
    err = nvs_open("storage", NVS_READWRITE, &handle);

    if (err != ESP_OK) 
    {
        ESP_LOGE(tag, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    else 
    {
        err = nvs_set_str(handle, "secret_key", message);
        if (err != ESP_OK)
        {
            ESP_LOGE(tag, "%s", "failed in writing message in NVS");
        }
        else
        {
            ESP_LOGI(tag, "%s", "wrote message in NVS");
        }
        
        err = nvs_commit(handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(tag, "%s", "failed in committing message in NVS");
        }
        else
        {
            ESP_LOGI(tag, "%s", "committed message in NVS");
        }
        
        nvs_close(handle);
    }
}

void get_from_nvs(char** value)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) 
    { 
        ESP_ERROR_CHECK(nvs_flash_erase());
        ESP_ERROR_CHECK(nvs_flash_init());
    }

    ESP_LOGI(tag, "%s", "opening non-volatile storage (NVS)");
    nvs_handle handle;
    err = nvs_open("storage", NVS_READWRITE, &handle);

    if (err != ESP_OK) 
    {
        ESP_LOGE(tag, "Error (%s) opening NVS handle!", esp_err_to_name(err));
    }
    else 
    {
        ESP_LOGI(tag, "%s", "reading string value");
        
        size_t string_size;
        esp_err_t err = nvs_get_str(handle, "secret_key", NULL, &string_size);

        if (err == ESP_OK)
        {
            *value = (char*) malloc(string_size);
            err = nvs_get_str(handle, "secret_key", *value, &string_size);
        }

        switch (err) {
            case ESP_OK:
                ESP_LOGI(tag, "%s", "read secret_key");
                break;

            case ESP_ERR_NVS_NOT_FOUND:
                ESP_LOGE(tag, "%s", "The value is not initialized yet");
                break;
            
            default:
                ESP_LOGE(tag, "Error (%s) reading", esp_err_to_name(err));
                break;
        }

        nvs_close(handle);
    }
}