#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <mbedtls/md.h>
#include <stdio.h>
#include <string.h>

void totp_init(mbedtls_md_type_t md_type);
void totp_generate(char* secret_key, uint64_t counter, unsigned char* message_hash);
void totp_free();