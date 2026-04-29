#include <windows.h>
#include <stdio.h>

// ENCODED ARRAY WILL GO HERE.
//
// PCHAR ENCODED[420] = { ... };

UCHAR ENCODE[16] = {
        0x73, 0x61, 0x6C, 0x20,
        0x65, 0x74, 0x63, 0x6F,
        0x6E, 0x68, 0x75, 0x62,
        0x70, 0x69, 0x6D, 0x2E
};

INT INDEX(
        PCHAR A,
        ULONG A_LENGTH,
        CHAR B
) {
        for (INT index = 0; index < A_LENGTH; index++)
                if (A[index] == B)
                        return index;
}

UCHAR LOWER(UCHAR A) {
        return (64 < A) && (A < 90) ? A + 32 : A;
}

VOID DECODE_ALE(
        PCHAR ENCODED,
        ULONG ENCODED_LENGTH,
        PCHAR OUTPUT
) {
        for (INT index = 0; index < ENCODED_LENGTH; index += 2)
                OUTPUT[index / 2] = (INDEX(ENCODE, 16, LOWER(ENCODED[index])) << 4) | (INDEX(ENCODE, 16, LOWER(ENCODED[index + 1])));
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
        CHAR DECODED[sizeof(/* ENCODED NAME */) / 2];
        DECODE_ALE(/* ENCODED NAME */, sizeof(/* ENCODED NAME */), DECODED);

        PrintBufferAsHex("DECODED", DECODED, sizeof(DECODED))
}