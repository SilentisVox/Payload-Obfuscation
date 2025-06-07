#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef GENERATERANDOMKEY_H
#define GENERATERANDOMKEY_H

BOOL GenerateRandomKey3(IN DWORD key_size, OUT PBYTE* out_key);

#endif // GENERATERANDOMKEY_H