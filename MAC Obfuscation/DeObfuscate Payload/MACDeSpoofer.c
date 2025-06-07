#include "MACDeSpoofer.h"

typedef long NTSTATUS;
typedef NTSTATUS(NTAPI* EtherStrToAddress)(PCSTR string, PCSTR* terminator, PVOID address);

BOOL MacDeobfuscation(IN CHAR* mac_array[], IN SIZE_T mac_array_size, OUT PBYTE* deobfuscated_buffer, OUT SIZE_T* deobfuscated_size)
{
    NTSTATUS                STATUS                  = 0x00;
    EtherStrToAddress       EtherStrToAddressFunc   = NULL;
    PBYTE                   deobfuscated_pointer     = NULL;
    PBYTE                   temp_buffer_pointer     = NULL;
    PCSTR                   terminator              = NULL;
    HMODULE                 ntdll_handle            = NULL;

    if (!(ntdll_handle = GetModuleHandle("ntdll")))
    {
        return FALSE;
    }

    if ((EtherStrToAddressFunc = (EtherStrToAddress) GetProcAddress(ntdll_handle, "RtlEthernetStringToAddressA")) == NULL)
    {
        return FALSE;
    }

    SIZE_T                  maximum_size            = mac_array_size * 6;
    PBYTE                   temp_buffer             = (PBYTE) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, maximum_size);

    if (temp_buffer == NULL)
    {
        return FALSE;
    }

    temp_buffer_pointer                             = temp_buffer;
    SIZE_T                  actual_size              = 0;

    for (INT index = 0; index < mac_array_size - 1; index++)
    {
        if ((STATUS = EtherStrToAddressFunc(mac_array[index], &terminator, temp_buffer_pointer)) != 0x0)
        {
            HeapFree(GetProcessHeap(), 0, temp_buffer);
            return FALSE;
        }

        memcpy(temp_buffer + actual_size, temp_buffer_pointer, 6);
        actual_size                                 += 6;
        temp_buffer_pointer                         += 6;
    }

    BYTE                    last_mac_bytes[6];

    if ((STATUS = EtherStrToAddressFunc(mac_array[mac_array_size - 1], &terminator, last_mac_bytes)) != 0x0)
    {
        HeapFree(GetProcessHeap(), 0, temp_buffer);
        return FALSE;
    }

    for (INT byte_index = 5; byte_index >= 0; byte_index--)
    {
        if (last_mac_bytes[byte_index] != 0xCC)
        {
            for (INT match_byte = 0; match_byte <= byte_index; match_byte++)
            {
                temp_buffer[actual_size++] = last_mac_bytes[match_byte];
            }

            break;
        }
    }

    deobfuscated_pointer = (PBYTE) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, actual_size);

    if (deobfuscated_pointer == NULL)
    {
        HeapFree(GetProcessHeap(), 0, temp_buffer);
        return FALSE;
    }

    memcpy(deobfuscated_pointer, temp_buffer, actual_size);
    HeapFree(GetProcessHeap(), 0, temp_buffer);

    *deobfuscated_buffer                            = deobfuscated_pointer;
    *deobfuscated_size                              = actual_size;

    return TRUE;
}
