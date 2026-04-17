#include <windows.h>
#include <stdio.h>

// ENCRYPTED SHELLCODE WILL GO HERE.
//
// CHAR ENCRYPTED[420] = { ... };

INT indexof(PCHAR A, INT B) {
        for (INT I = 0; I < 255; I++)
                if (A[I] == B)
                        return I;
}

VOID DECRYPT(PCHAR BUFFER, ULONG SIZE, PCHAR TABLE, PCHAR KEY, PCHAR OUTPUT) {
        for (INT index = 0; index < SIZE; index++)
                OUTPUT[index] = TABLE[(indexof(TABLE, BUFFER[index]) - indexof(TABLE, KEY[index]) + 256) % 256];
}

VOID PrintBufferAsHex(PUCHAR BufferName, PUCHAR Buffer, ULONG BufferSize) {
        printf("PCHAR %s[%d] = {", BufferName, BufferSize);

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
        CHAR OUTPUT[sizeof(/* NAME OF ENCRYPTED SHELLCODE */)];
        DECRYPT(/* NAME OF ENCRYPTED SHELLCODE */, sizeof(/* NAME OF ENCRYPTED SHELLCODE */), TABLE, KEY, OUTPUT);
        PrintBufferAsHex("SHELLCODE", OUTPUT, sizeof(OUTPUT));
}