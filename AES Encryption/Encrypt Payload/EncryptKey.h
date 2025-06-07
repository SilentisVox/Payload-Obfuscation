#include <windows.h>

#ifndef ENCRYPTIONSUBMITTEDKEY_H
#define ENCRYPTIONSUBMITTEDKEY_H

BOOL EncryptSubmittedKey(IN PBYTE key_array, IN SIZE_T key_size, OUT BYTE* out_key);

#endif // ENCRYPTIONSUBMITTEDKEY_H