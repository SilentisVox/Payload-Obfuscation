#include <windows.h>
#include <stdio.h>

// ENCRYPTED SHELLCODE & KEY WILL GO HERE.
//
// CHAR ENCRYPTED[420] = { ... };
// CHAR KEY[16] = { ... };

VOID XOR_CRYPT(
        PCHAR BUFFER,
        ULONG BUFFER_LENGTH,
        PCHAR KEY,
        ULONG KEY_LENGTH,
        PCHAR OUTPUT
) {
        for (INT index = 0; index < BUFFER_LENGTH; index++)
                OUTPUT[index] = BUFFER[index] ^ KEY[index % KEY_LENGTH];
}

VOID PrintBufferAsHex(
        PUCHAR BufferName,
        PUCHAR Buffer,
        ULONG BufferSize
) {
        printf("CHAR %s[%d] = {", BufferName, BufferSize);

        for (INT index = 0; index < BufferSize; index++) {
                if (!(index % 12))
                        printf("\n        ");

                printf("0x%02X", Buffer[index]);

                if (index + 1 != BufferSize)
                        printf(", ");
        }
        printf("\n};\n");
}

VOID main() {
        CHAR OUTPUT[sizeof(/* ENCRYPTED NAME */)];
        XOR_CRYPT(/* ENCRYPTED NAME */, sizeof(/* ENCRYPTED NAME */), /* KEY NAME */, sizeof(/* KEY NAME */), OUTPUT);

        PrintBufferAsHex("SHELLCODE", OUTPUT, sizeof(OUTPUT));
}