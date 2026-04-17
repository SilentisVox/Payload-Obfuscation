#include <windows.h>
#include <stdio.h>

// SHELLCODE WILL GO HERE.
//
// CHAR SHELLCODE[420] = { ... };

VOID GenerateMacOutput(PCHAR ArrayName, PCHAR Buffer, ULONG BufferSize) {
        INT STABLE_SIZE = BufferSize + 6 - BufferSize % 6;
        UCHAR STABLE[STABLE_SIZE];

        for (INT index = 0; index < STABLE_SIZE; index++)
                STABLE[index] = 0;

        for (INT index = 0; index < BufferSize; index++)
                STABLE[index] = Buffer[index];

        printf("PCHAR %s[%d] = {", ArrayName, STABLE_SIZE / 6);

        for (INT index = 0, slice = 0; index < STABLE_SIZE; index += 6, slice++) {
                if (!(slice % 4))
                        printf("\n        ");

                printf(
                        "\"%02X-%02X-%02X-%02X-%02X-%02X\"",
                        STABLE[index],
                        STABLE[index + 1],
                        STABLE[index + 2],
                        STABLE[index + 3],
                        STABLE[index + 4],
                        STABLE[index + 5]
                );

                if (index + 6 != STABLE_SIZE)
                        printf(", ");
        }
        printf("\n};\n");
}

VOID main() {
        GenerateMacOutput("SHELLCODE", /* NAME OF SHELLCODE */, sizeof(/* NAME OF SHELLCODE */));
}