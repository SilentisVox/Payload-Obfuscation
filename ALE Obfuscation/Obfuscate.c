#include <windows.h>
#include <stdio.h>

// SHELLCODE WILL GO HERE.
//
// CHAR SHELLCODE[420] = { ... };

UCHAR ENCODE[16] = {
        0x73, 0x61, 0x6C, 0x20,
        0x65, 0x74, 0x63, 0x6F,
        0x6E, 0x68, 0x75, 0x62,
        0x70, 0x69, 0x6D, 0x2E
};

UCHAR RAND() {
        UCHAR HI, LO;
        __asm__ volatile ("rdtsc" : "=a" (LO), "=d" (HI));
        return (HI ^ LO) & 0xFF;
}

UCHAR UPPER(UCHAR A) {
        return (97 < A) && (A < 122) ? A - 32 : A;
}

VOID ENCODE_ALE(
        PCHAR BUFFER,
        ULONG BUFFER_LENGTH,
        PCHAR ENCODED
) {
        for (INT index = 0; index < BUFFER_LENGTH * 2; index += 2) {
                INT A = (BUFFER[index / 2] & 0xF0) >> 4;
                INT B = (BUFFER[index / 2] & 0x0F);

                UCHAR C = (!index) || ((index > 0) && ((BUFFER[(index - 1) / 2] & 0x0F) == 0xF)) ? UPPER(ENCODE[A]) : ENCODE[A];
                UCHAR D = A == 0xF ? UPPER(ENCODE[B]) : ENCODE[B];

                ENCODED[index + 0] = C;
                ENCODED[index + 1] = D;
        }
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
        CHAR ENCODED[sizeof(/* SHELLCODE NAME */) * 2];
        ENCODE_ALE(/* SHELLCODE NAME */, sizeof(/* SHELLCODE NAME */), ENCODED);

        PrintBufferAsHex("ENCODED", ENCODED, sizeof(ENCODED));
}