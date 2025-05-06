## **Payload Obfuscation**

### **Setup**

```cmd
git clone https://github.com/SilentisVox/Payload-Obfuscation
cd Payload-Obfuscation
powershell ./Build.ps1
```

### **Usage**

```cmd
cd "./AES Encryption"

& "./Encrypt Payload/Encrypt Payload.exe" "./Encrypt Payload/Shellcode.bin" # calc.exe
& "./Decrypt Payload/Decrypt Payload.exe"
```
```cmd
cd "./MAC Obfuscation"

& "./Obfuscate Payload/Obfuscate Payload.exe"
& "./DeObfuscate Payload/DeObfuscate Payload.exe"
```

## **Brief Explanation**

![payload](https://github.com/user-attachments/assets/da45ff0c-ca14-44fa-8d57-9fc7da8a4746)

### **What is Obfuscation?**

Obfuscation is the action of making something obscure, unclear, or unintelligible, especially code, data, or information, in order to conceal its true purpose or logic. While the functionality remains the same, the clarity and readability are intentionally reduced. This technique is often used in programming, cybersecurity, and digital content protection.

### **How does it work with Shellcode?**

Well, there are many ways to obfuscate shellcode, but the primary methods used here are AES Encryption and MAC string translation.

#### **AES Encryption**

What we do here, is generate a random 32 byte key and 16 byte initialization vector (IV). We use this to encrypt given shellcode from a file. We then generate a random byte to xor encrypt both the key and IV. Once completed, we print the encrypted shellcode, encrypted key/IV, and key/IV decryption functions.

#### **MAC Obfuscation**

For MAC address string translation, we take every 6 bytes of shellcode, and represent them as strings in the MAC address format `FD:3E:CB:3D:38:E4`. Once obfuscated, print the MAC array to the screen.
