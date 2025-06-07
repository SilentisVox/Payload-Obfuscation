#include <windows.h>
#include <stdio.h>
#include <string.h>

#ifndef INSTALLAESENCRYPTION_H
#define INSTALLAESENCRYPTION_H

BOOL InstallAesEncryptionViaCtAes(IN PBYTE raw_buffer, IN SIZE_T raw_size, IN PBYTE aes_key, IN PBYTE aes_iv, OUT PBYTE* encrypted_content, OUT SIZE_T* encrypted_size);

#endif // INSTALLAESENCRYPTION_H