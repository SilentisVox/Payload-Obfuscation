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
Another solution may be **ALE Obfuscation**;
Disguising our shellcode as an array of Alpha Lettering, as quite a few EXEs come with text embedded in the EXE.

### Encryption.

For brevity, and simplicity, my encryption algorithm will be one of the most simple.
By taking a randomized table of bytes, and shifting them according to a key of bytes, we create an encryption.
This encryption is named as **Vigenere**, where a row of ceasar ciphers becomes an encryption table.

Encrypting involves finding the index of the plain byte in the table, and adding the index of the key byte in the table.
For decryption, finding the index of the encrypted byte, subtract the index of the key byte will reveal the plain byte.

```c
void ENCRYPT(char *BUFFER, unsigned long SIZE, char *TABLE, char *KEY, char *OUTPUT) {
        for (int i = 0; i < SIZE; i++)
                OUTPUT[index] = TABLE[(indexof(TABLE, BUFFER[i]) + indexof(TABLE, KEY[i])) % 256];
}

void DECRYPT(char *BUFFER, unsigned long SIZE, char *TABLE, char *KEY, char *OUTPUT) {
        for (int i = 0; i < SIZE; i++)
                OUTPUT[index] = TABLE[(indexof(TABLE, BUFFER[i]) - indexof(TABLE, KEY[i]) + 256) % 256];
}
```

### ALE Obfuscation.

Obfuscating the payload to appear as ALE comes a little trickier, as we need to know how to deobfuscate.
Using the first nibble of the byte, index it to get the ecoded letter.
Then the same goes for each nibble of every byte.
To Have this look "TEXT-CODED", after every "." will come an uppercase letter.

For decoding our ALE, every byte will be reverse indexed from the encoding table.
For the even bytes, the will be bytewise shifted left 4 bits.
This will then be bytewsise OR with the second reverse indexed byte.
This will get us each byte in our encoding.

```c
UCHAR ENCODE[16] = {
        0x73, 0x61, 0x6C, 0x20,
        0x65, 0x74, 0x63, 0x6F,
        0x6E, 0x68, 0x75, 0x62,
        0x70, 0x69, 0x6D, 0x2E
};

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

VOID DECODE_ALE(
        PCHAR ENCODED,
        ULONG ENCODED_LENGTH,
        PCHAR OUTPUT
) {
        for (INT index = 0; index < ENCODED_LENGTH; index += 2)
                OUTPUT[index / 2] = (INDEX(ENCODE, 16, LOWER(ENCODED[index])) << 4) | (INDEX(ENCODE, 16, LOWER(ENCODED[index + 1])));
}
```