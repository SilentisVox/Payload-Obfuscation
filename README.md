# Payload Obfuscation

The most common way to evade **Antivirus** (AV) is shellcode injection.
When shellcode is loaded into memory, it can be seen as malicious for being present.
A way to evade detections is simply disguising the shellcode;
Maintaining functionality while hiding in plain sight.

**Disclaimer**: The purpose of this is for educational purposes and testing only.
Do not use this on machines you do not have permission to use.
Do not use this to leverage and communicate with machines that you do not have authorization to use.

## The problem.

For the most part, shellcode gets injected from an originating **Executable File** (EXE).
The `.data` section of your executable contains publicly available variables;
Shellcode can be stored in a variable and referenced later.
If there are shellcode instructions within the `.data` section, something is seriously wrong.

AV tends to live on the safer side when it comes to recognizing malware;
Hiding shellcode should be a high priority.
Inserting random garbage for the shellcode can still get flagged as shellcode.
Inserting code that also looks like something it is not will even get flagged.

```diff
- .\Malware.exe : Operation did not complete successfully because the file contains a virus or potentially unwanted software.
```

## The solution.

2 solutions come to mind when I think of obfuscating shellcode.
A solution might just look like **Encyption**;
Scrambling our shellcode in a way that only we know, as it becomes unrecognizable.
Another solution may be **MAC Obfuscation**;
Disguising our shellcode as an array of MAC addresses, as quite a few EXEs come with MAC addresses embedded in the EXE.

### Encryption.

For brevity, and simplicity, my encryption algorithm will be one of the most simple.
By taking a randomized key of bytes, and XORing them according to a index of the shellcode bytes, we create an encryption.
This encryption is named as **XOR**, where a key becomes an encryption table.

Encrypting involves finding the index of the plain byte in the table, and adding the index of the key byte in the table.
For decryption, finding the index of the encrypted byte, subtract the index of the key byte will reveal the plain byte.

```c
VOID XOR_CRYPT(PCHAR BUFFER, ULONG BUFFER_LENGTH, PCHAR KEY, ULONG KEY_LENGTH, PCHAR OUTPUT) {
        for (INT index = 0; index < BUFFER_LENGTH; index++)
                OUTPUT[index] = BUFFER[index] ^ KEY[index % KEY_LENGTH];
}
```

### MAC Obfuscation.

Obfuscating the payload to appear as MAC addresses comes a little trickier, as we need to know how to deobfuscate.
Initially, printing the payload in increments of 6 is okay, as long as we have a padding.
But when deobfuscations come, I wanted to remain barebones in terms of importing functions.

Knowing how we obfuscated the payload allows us to use some tricks.
For each slot of the MAC address, we want to subtract the ordinal value from the character to get the byte piece.
Shifting the initial piece 4 bits, and unioning it with the second should get us the correct byte.
Skipping every 3 bytes, we collect the first 2 to create 1 byte of our payload.

```c
void OBFUSCATE (char *MAC_ARRAY, unsigned long MAC_ARRAY_SIZE) {
        for (int i = 0; i < MAC_ARRAY_SIZE; i += 6)
                printf(
                        "\"%02X-%02X-%02X-%02X-%02X-%02X\"",
                        MAC_ARRAY[i],
                        MAC_ARRAY[i + 1],
                        MAC_ARRAY[i + 2],
                        MAC_ARRAY[i + 3],
                        MAC_ARRAY[i + 4],
                        MAC_ARRAY[i + 5]
                );
}

void MAC2CODE(char *STRING, char *ADDRESS) {
        for (int i = 0, j = 0; i < 6; i++, j += 3)
                ADDRESS[i] = (fromchar(STRING[j]) << 4) | (fromchar(STRING[j + 1]));
}

void DEOBFUSCATE(char *ARRAY[], unsigned long SIZE, char *BUFFER) {
        for (int i = 0, j = 0; i < SIZE; i++, j += 6) {
                char ADDRESS[6];

                MAC2CODE(ARRAY[i], ADDRESS);

                BUFFER[j]     = Address[0];
                BUFFER[j + 1] = Address[1];
                BUFFER[j + 2] = Address[2];
                BUFFER[j + 3] = Address[3];
                BUFFER[j + 4] = Address[4];
                BUFFER[j + 5] = Address[5];
        }
}
```