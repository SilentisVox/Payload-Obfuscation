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

& "./Encrypt Payload/Encrypt Payload" "Your Shellcode.bin"
& "./Decrypt Payload/Decrypt Payload"
```
```cmd
cd "./MAC Obfuscation"

& "./Obfuscate Payload/Obfuscate Payload"
& "./DeObfuscate Payload/DeObfuscate Payload"
```

## **Brief Explanation**

![payload](https://github.com/user-attachments/assets/da45ff0c-ca14-44fa-8d57-9fc7da8a4746)

### **What is Obfuscation?**

Obfuscation is the action of making something obscure, unclear, or unintelligible, especially code, data, or information, in order to conceal its true purpose or logic. While the functionality remains the same, the clarity and readability are intentionally reduced. This technique is often used in programming, cybersecurity, and digital content protection.

### **How does it work with Shellcode?**

Well, there are many ways to obfuscate shellcode, but the primary methods used here are AES Encryption and MAC string translation.

#### **AES Encryption**

#### **MAC Obfuscation**
