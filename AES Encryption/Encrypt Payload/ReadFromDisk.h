#include <windows.h>
#include <stdio.h>

#ifndef READFROMDISK_H
#define READFROMDISK_H

BOOL ReadFileFromDiskA(IN LPCSTR file_name, OUT PBYTE* file_buffer, OUT PDWORD file_size);

#endif // READFROMDISK_H