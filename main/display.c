#include "display.h"

static const char* tag = "display";
bool bus_init() 
{
    assert(SSD1306_I2CMasterInitDefault() == true);
    assert(SSD1306_I2CMasterAttachDisplayDefault(&display, I2CDisplayWidth, I2CDisplayHeight, I2CDisplayAddress, I2CResetPin) == true);
 
    return true;
}

void init_display(struct SSD1306_Device* display)
{
    bool err = bus_init();
    
    if (err)
    {
        ESP_LOGI(tag, "%s", "Bus init successful");

        clear_display(display);
    }
}

void write_display(struct SSD1306_Device* display, TextAnchor anchor, char* text)
{
    SSD1306_FontDrawAnchoredString(display, anchor, text, SSD_COLOR_WHITE );
    SSD1306_Update(display);
}

void clear_display(struct SSD1306_Device* display)
{
    SSD1306_Clear(display, SSD_COLOR_BLACK);
}


void set_font_display(struct SSD1306_Device* display, const struct SSD1306_FontDef* font)
{
    SSD1306_SetFont(display, font);
}
