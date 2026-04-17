#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// SHELLCODE WILL GO HERE.
//
// CHAR SHELLCODE[420] = { ... };

VOID GenerateKey(PCHAR KEY) {
        srand(time(NULL));

        for (INT index = 0; index < 256; index++)
                KEY[index] = rand();
}

VOID GenerateTable(PCHAR TABLE) {
        srand(time(NULL));

        for (INT index = 0, SEED = rand() * 7; index < 256; index++)
                TABLE[index] = (SEED + (147 * index)) % 256;
}

INT indexof(PCHAR A, INT B) {
        for (INT I = 0; I < 255; I++)
                if (A[I] == B)
                        return I;
}

VOID ENCRYPT(PCHAR BUFFER, ULONG SIZE, PCHAR TABLE, PCHAR KEY, PCHAR OUTPUT) {
        for (INT index = 0; index < SIZE; index++)
                OUTPUT[index] = TABLE[(indexof(TABLE, BUFFER[index]) + indexof(TABLE, KEY[index])) % 256];
}

VOID PrintBufferAsHex(PUCHAR BufferName, PUCHAR Buffer, ULONG BufferSize) {
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
        CHAR TABLE[256];
        CHAR KEY[256];

        GenerateTable(TABLE);
        GenerateKey(KEY);

        CHAR OUTPUT[sizeof(/* NAME OF SHELLCODE */)];
        ENCRYPT(/* NAME OF SHELLCODE */, sizeof(/* NAME OF SHELLCODE */), TABLE, KEY, OUTPUT);

        PrintBufferAsHex("TABLE", TABLE, 256);
        PrintBufferAsHex("KEY", KEY, 256);
        PrintBufferAsHex("ENCRYPTED", OUTPUT, sizeof(/* NAME OF SHELLCODE */));
}