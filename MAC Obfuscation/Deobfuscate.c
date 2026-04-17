#include <windows.h>
#include <stdio.h>

// MAC ARRAY WILL GO HERE.
//
// PCHAR MAC_ARRAY[420] = { ... };

INT FROMCHAR(INT A) {
        return A < 64 ? A - 48 : A - 55;
}

VOID MAC2CODE(PUCHAR String, PUCHAR Address) {
        for (INT StringIndex = 0, AddressIndex = 0; AddressIndex < 6; StringIndex += 3, AddressIndex++)
                Address[AddressIndex] = (FROMCHAR(String[StringIndex]) << 4) | (FROMCHAR(String[StringIndex + 1]));
}

VOID MacDeobfuscation(
        PCHAR  Array[],
        ULONG  ArraySize, 
        PCHAR  BUFFER
) {
        for (INT ArrayIndex = 0, BufferIndex = 0; ArrayIndex < ArraySize; ArrayIndex++, BufferIndex += 6) {
                UCHAR Address[6];
                
                MAC2CODE(Array[ArrayIndex], Address);

                BUFFER[BufferIndex]     = Address[0];
                BUFFER[BufferIndex + 1] = Address[1];
                BUFFER[BufferIndex + 2] = Address[2];
                BUFFER[BufferIndex + 3] = Address[3];
                BUFFER[BufferIndex + 4] = Address[4];
                BUFFER[BufferIndex + 5] = Address[5];
        }
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
        ULONG SIZE = /* SIZE OF MAC ARRAY */ * 6;
        CHAR SHELLCODE[SIZE];

        for (INT index = 0; index < SIZE; index++)
                SHELLCODE[index] = 0;

        MacDeobfuscation(/* NAME OF MAC ARRAY */, 28, SHELLCODE);
        PrintBufferAsHex("SHELLCODE", SHELLCODE, SIZE);
}