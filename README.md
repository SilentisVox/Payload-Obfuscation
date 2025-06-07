# Payload-Obfuscation

Realizing a powerful malicious application is detected by AV is a crushing setback.

```diff
- .\Malware.exe : Operation did not complete successfully because the file contains a virus or potentially unwanted software.
```

Evading detection is crucial in the domain of cyber. Let's explore how these techniques to mask payloads and challenge even advanced defensive mechanisms.

### Setup
```powershell
git clone https://github.com/SilentisVox.com/Payload-Obfuscation
cd Payload-Obfuscation
cmake .
```

###### Visual Studio
```powershell
cmake . -B build -G "Visual Studio 17 2022"
```

### Usage

```powershell
cd "./AES Encryption"

& "./Encrypt Payload/Encrypt Payload.exe" "./Encrypt Payload/Shellcode.bin" # calc.exe
& "./Decrypt Payload/Decrypt Payload.exe"
```
```powershell
cd "./MAC Obfuscation"

& "./Obfuscate Payload/Obfuscate Payload.exe"
& "./DeObfuscate Payload/DeObfuscate Payload.exe"
```