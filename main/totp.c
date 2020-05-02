#include "totp.h"

static mbedtls_md_context_t ctx;
static mbedtls_md_type_t md_type;

void totp_init(mbedtls_md_type_t type)
{
    md_type = type;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 1);
}

void totp_generate(char* secret_key, uint64_t counter, unsigned char* message_hash)
{
    const size_t secret_key_length = strlen(secret_key);
    const size_t counter_length = sizeof(counter);
    unsigned char hmac_result[32];
    memset(message_hash, '\0', 64);

    uint32_t endianness = 0xdeadbeef;
    if ((*(const uint8_t *)&endianness) == 0xef) {
        counter = ((counter & 0x00000000ffffffff) << 32) | ((counter & 0xffffffff00000000) >> 32);
        counter = ((counter & 0x0000ffff0000ffff) << 16) | ((counter & 0xffff0000ffff0000) >> 16);
        counter = ((counter & 0x00ff00ff00ff00ff) <<  8) | ((counter & 0xff00ff00ff00ff00) >>  8);
    };

    mbedtls_md_hmac_starts(&ctx, (const unsigned char*)secret_key, secret_key_length);
    mbedtls_md_hmac_update(&ctx, (const unsigned char*)&counter, counter_length);
    mbedtls_md_hmac_finish(&ctx, hmac_result);
    mbedtls_md_free(&ctx);

    memcpy(message_hash, hmac_result, 32);
    // for(int i=0; i<sizeof(hmac_result); i++)
    // {
    //     char str[3];
    //     sprintf(str, "%02x", (int)hmac_result[i]);
    //     strcat(message_hash, str);
    // }
}

void totp_free()
{
    mbedtls_md_free(&ctx);
}