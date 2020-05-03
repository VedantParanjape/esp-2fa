#ifndef NVS_H
#define NVS_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_log.h"

void save_to_nvs(char* message);
void get_from_nvs(char** value);

#endif