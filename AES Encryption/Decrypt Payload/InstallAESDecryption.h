#include <windows.h>

#ifndef INSTALLAESDECRYPTION_H
#define INSTALLAESDECRYPTION_H

BOOL InstallAesDecryptionViaCtAes(IN PBYTE cipher_text_buffer, IN SIZE_T cipher_text_size, IN PBYTE aes_key, IN PBYTE aes_iv, OUT PBYTE* plain_text_buffer, OUT SIZE_T* plain_text_size);

#endif // ENCRYPTIONSUBMITTEDKEY_H