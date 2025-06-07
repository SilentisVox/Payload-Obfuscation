#include <stdlib.h>
#include "EncryptKey.h"

BOOL EncryptSubmittedKey(IN PBYTE key_array, IN SIZE_T key_size, OUT BYTE* out_key)
{
    if (!key_array || !key_size)
    {
        return FALSE;
    }

    BYTE              hint_byte                     = key_array[1];
    BYTE              encryption_byte               = (rand() * key_array[0]) % 0xFF;

    for (SIZE_T i = 0; i < key_size; i++)
    {
        key_array[i] ^= encryption_byte;
    }

    *out_key                                        = hint_byte;

    return TRUE;
}
