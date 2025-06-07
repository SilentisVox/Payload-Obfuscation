#include <windows.h>

#ifndef MACDESPOOFER_H
#define MACDESPOOFER_H

BOOL MacDeobfuscation(IN CHAR* mac_array[], IN SIZE_T mac_array_size, OUT PBYTE* deobfuscated_buffer, OUT SIZE_T* deobfuscated_size);

#endif // MACDESPOOFER_H