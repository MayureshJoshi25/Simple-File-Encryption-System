# Simple-File-Encryption-System
A simple file encryption system made in C++ for a college project which takes a text file and encrypts it in ASCII, AES &amp; RSA.

This system requires the installation of the Crypto++ Library for some functions within. Link: https://www.cryptopp.com/wiki/Main_Page

The flow of the project starts with the user entering or inputting a file (text file) into the system. After that the user will be prompted to select between the 3 encryption schemes (Character based, AES and RSA) to be applied to the file in order to encrypt it. After encrypting the required file, the user can choose to decrypt it.

Flow:


![Picture1](https://user-images.githubusercontent.com/60180388/186090294-07b34fe0-8087-4f96-86df-87599a1df8d5.png)


Here, fescpp.cpp is the main file that accepts a test file named test.txt.
An encypted file named tmp.txt s obtained.
Decryption facility also available.
