#include <windows.h>
#include <stdio.h>

#include "CtAes.h"
#include "InstallAESDecryption.h"

BOOL InstallAesDecryptionViaCtAes(IN PBYTE cipher_text_buffer, IN SIZE_T cipher_text_size, IN PBYTE aes_key, IN PBYTE aes_iv, OUT PBYTE* plain_text_buffer, OUT SIZE_T* plain_text_size)
{
    AES256_CBC_ctx    AesCtx                        = { 0x00 };

    if (!cipher_text_buffer || !cipher_text_size || !plain_text_buffer || !aes_key || !aes_iv)
    {
        return FALSE;
    }

    if (!(*plain_text_buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cipher_text_size)))
    {
        printf("[!] HeapAlloc Failed With Error: %d \n", GetLastError());
        return FALSE;
    }

    RtlSecureZeroMemory(&AesCtx, sizeof(AES256_CBC_ctx));

    AES256_CBC_init(&AesCtx, aes_key, aes_iv);
    AES256_CBC_decrypt(&AesCtx, (cipher_text_size / 16), *plain_text_buffer, cipher_text_buffer);

    *plain_text_size                                = cipher_text_size;

    return TRUE;
}