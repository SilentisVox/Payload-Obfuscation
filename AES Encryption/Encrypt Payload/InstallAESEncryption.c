#include "CtAes.h"
#include "InstallAesEncryption.h"

BOOL InstallAesEncryptionViaCtAes(IN PBYTE raw_buffer, IN SIZE_T raw_size, IN PBYTE aes_key, IN PBYTE aes_iv, OUT PBYTE* encrypted_content, OUT SIZE_T* encrypted_size)
{
    if (!raw_buffer || !raw_size || !encrypted_content || !encrypted_size || !aes_key || !aes_iv)
    {
        return FALSE;
    }

    PBYTE             raw_buff_copy                 = raw_buffer;
    PBYTE             cipher_buffer                 = NULL;
    SIZE_T            cipher_size                   = raw_size;
    AES256_CBC_ctx    aes_context                   = { 0x00 };

    if (raw_size % 16 != 0x00)
    {
        cipher_size                                 = raw_size + 16 - (raw_size % 16);
        raw_buff_copy                               = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cipher_size);

        if (!raw_buff_copy)
        {
            printf("[!] HeapAlloc Failed With Error: %d \n", GetLastError());
            return FALSE;
        }

        memcpy(raw_buff_copy, raw_buffer, raw_size);
    }

    if (!(cipher_buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cipher_size)))
    {
        printf("[!] HeapAlloc Failed With Error: %d \n", GetLastError());
        return FALSE;
    }

    RtlSecureZeroMemory(&aes_context, sizeof(AES256_CBC_ctx));

    AES256_CBC_init(&aes_context, aes_key, aes_iv);
    AES256_CBC_encrypt(&aes_context, (cipher_size / 16), cipher_buffer, raw_buff_copy);

    *encrypted_content                              = cipher_buffer;
    *encrypted_size                                 = cipher_size;

    return TRUE;
}