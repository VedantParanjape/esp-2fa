#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ssd1306.h"
#include "ssd1306_draw.h"
#include "ssd1306_font.h"
#include "ssd1306_default_if.h"

static const int I2CDisplayAddress = 0x3C;
static const int I2CDisplayWidth = 128;
static const int I2CDisplayHeight = 64;
static const int I2CResetPin = -1;

struct SSD1306_Device display;

bool bus_init(void);
void init_display(struct SSD1306_Device* display);
void write_display(struct SSD1306_Device* display, TextAnchor anchor, char* text);
void clear_display(struct SSD1306_Device* display);
void set_font_display(struct SSD1306_Device* display, const struct SSD1306_FontDef* font);

#endif