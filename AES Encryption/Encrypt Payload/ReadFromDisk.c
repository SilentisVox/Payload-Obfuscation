#include "ReadFromDisk.h"

BOOL ReadFileFromDiskA(IN LPCSTR file_name, OUT PBYTE* file_buffer, OUT PDWORD file_size)
{
    HANDLE            file_handle                   = INVALID_HANDLE_VALUE;
    DWORD             local_file_size               = 0;
    DWORD             bytes_read                    = 0;
    PBYTE             base_address                  = NULL;

    if (!file_name || !file_size || !file_buffer)
    {
        goto _END_OF_FUNC;
    }

    if ((file_handle = CreateFileA(file_name, GENERIC_READ, 0x00, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        printf("[!] CreateFileA Failed With Error: %d \n", GetLastError());
        goto _END_OF_FUNC;
    }

    if ((local_file_size = GetFileSize(file_handle, NULL)) == INVALID_FILE_SIZE)
    {
        printf("[!] GetFileSize Failed With Error: %d \n", GetLastError());
        goto _END_OF_FUNC;
    }

    if (!(base_address = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, local_file_size)))
    {
        printf("[!] HeapAlloc Failed With Error: %d \n", GetLastError());
        goto _END_OF_FUNC;
    }

    if (!ReadFile(file_handle, base_address, local_file_size, &bytes_read, NULL) || local_file_size != bytes_read)
    {
        printf("[!] ReadFile Failed With Error: %d \n[i] Read %d Of %d Bytes \n", GetLastError(), bytes_read, local_file_size);
        goto _END_OF_FUNC;
    }

    *file_buffer                                    = base_address;
    *file_size                                      = local_file_size;

_END_OF_FUNC:

    if (file_handle != INVALID_HANDLE_VALUE)
    {
        CloseHandle(file_handle);
    }

    if (base_address && !*file_buffer)
    {
        HeapFree(GetProcessHeap(), 0x00, base_address);
    }

    return (*file_buffer && *file_size) ? TRUE : FALSE;
}