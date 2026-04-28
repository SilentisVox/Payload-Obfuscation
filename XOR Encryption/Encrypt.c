#include <windows.h>
#include <stdio.h>

// SHELLCODE WILL GO HERE.
//
// CHAR SHELLCODE[420] = { ... };

#define rand() ({UINT LO, HI; __asm__ volatile ("rdtsc" : "=a" (LO), "=d" (HI)); LO ^ HI;})

VOID GenerateKey(
        PCHAR KEY, 
        ULONG KEY_LENGTH
) {
        for (INT index = 0; index < KEY_LENGTH; index++)
                KEY[index] = (CHAR) rand();
}

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
        CHAR KEY[/* KEY LENGTH */];
        GenerateKey(KEY, sizeof(KEY));

        CHAR OUTPUT[sizeof(/* SHELLCODE NAME */)];
        XOR_CRYPT(/* SHELLCODE NAME */, sizeof(/* SHELLCODE NAME */), KEY, sizeof(KEY), OUTPUT);

        PrintBufferAsHex("KEY", KEY, sizeof(KEY));
        PrintBufferAsHex("ENCRYPTED", OUTPUT, sizeof(/* SHELLCODE NAME */));
}