cmake_minimum_required(VERSION 3.15)
project(Payload_Obfuscation)

add_subdirectory("AES Encryption/Encrypt Payload")
add_subdirectory("AES Encryption/Decrypt Payload")
add_subdirectory("MAC Obfuscation/Obfuscate Payload")
add_subdirectory("MAC Obfuscation/Deobfuscate Payload")