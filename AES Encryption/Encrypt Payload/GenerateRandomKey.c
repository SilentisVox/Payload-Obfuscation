#include "GenerateRandomKey.h"

BOOL GenerateRandomKey3(IN DWORD key_size, OUT PBYTE* out_key)
{
    PBYTE             key_pointer                  = NULL;
    unsigned short    right_bytes                  = 0;
    unsigned int      seed                         = 0x00;
    static int        seeded                       = 0;

    if (!seeded)
    {
        srand((unsigned int)time(NULL));
        seeded                                     = 1;
    }

    key_pointer                                    = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, key_size);

    if (!key_pointer)
    {
        printf("[!] HeapAlloc Failed With Error: %d \n", GetLastError());
        return FALSE;
    }

    right_bytes                                    = (unsigned short)((ULONG_PTR)key_pointer & 0xFFFF);

    for (SIZE_T i = 0; i < key_size; i++)
    {
        seed                                       = ((unsigned int)rand() << 16) | ((unsigned int)rand() & 0xFFFF);

        if (i % 2 == 0)
        {
            key_pointer[i]                         = (BYTE)(((right_bytes ^ seed) & 0xFF) % 0xFF);
        }
        else
        {
            key_pointer[i]                         = (BYTE)((((right_bytes ^ seed) >> 8) & 0xFF) % 0xFF);
        }
    }

    *out_key                                       = key_pointer;
    return TRUE;
}