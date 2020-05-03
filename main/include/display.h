#ifndef DISPLAY_H
#define DISPLAY_H

#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <u8g2.h>
#include "u8g2_esp32_hal.h"

#define PIN_SDA 21
#define PIN_SCL 22

void display_init();
void display_write(char* totp);

#endif