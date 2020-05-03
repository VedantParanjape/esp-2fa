# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c" "ntp.c" "u8g2_esp32_hal.c" "totp.c" "nvs.c" "display.c" "rtc.c")
set(COMPONENT_ADD_INCLUDEDIRS "include")

register_component()
