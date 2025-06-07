#include <windows.h>
#include <stdio.h>

#ifndef GENERATEMAC_H
#define GENERATEMAC_H

VOID GenerateMAC(IN INT A, IN INT B, IN INT C, IN INT D, IN INT E, IN INT F, OUT PCHAR mac_string);
BOOL GenerateMacOutput(IN PBYTE shellcode, IN SIZE_T shellcode_size);

#endif // GENERATEMAC_H
