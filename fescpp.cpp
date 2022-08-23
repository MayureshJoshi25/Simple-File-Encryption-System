#include <files.h>
#include <modes.h>
#include <osrng.h>
#include "cryptlib.h"
#include "rijndael.h"
#include "hex.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <default.h> 
#include <math.h>
#include <string>
#include <rsa.h>
#include <cassert>  
using namespace std;
using namespace CryptoPP;


//Functions for basic encryption start from here
int encryp() {

    char fileName[30], ch;
    fstream fps, fpt;
    cout << "Enter the File name: ";
    cin >> gets_s(fileName); //Getting the file to encrypt
    fps.open(fileName, fstream::in);
    if (!fps)//If the file is not present then...
    {
        cout << "\nError!, Opening the Source File (to Read)!";
        return 0;
    }
    fpt.open("tmp.txt", fstream::out);//We create a temporary file to store cipher text
    if (!fpt)
    {
        cout << "\nError!, Opening/Creating the tmp File!";
        return 0;
    }
    while (fps >> noskipws >> ch) // adding 100 to the characters without skipping white spaces
    {
        ch = ch + 100;
        fpt << ch;
    }
    fps.close();
    fpt.close();
    fps.open(fileName, fstream::out);
    if (!fps)
    {
        cout << "\nError!, Opening the Source File (to write)!";
        return 0;
    }
    fpt.open("tmp.txt", fstream::in);//The cipher text is written to the original file.
    if (!fpt)
    {
        cout << "\nError!, Opening the tmp File!";
        return 0;
    }
    while (fpt >> noskipws >> ch)
        fps << ch;
    fps.close();
    fpt.close();
    cout << "\nFile '" << fileName << "' File Encrypted Successfully!";
    cout << endl;
};

int decryp() {
    char fileName[30], ch;
    fstream fps, fpt;
    cout << "Enter the Name of File: ";
    cin >> gets_s(fileName);
    fps.open(fileName, fstream::out);
    if (!fps)
    {
        cout << "\nError Occurred while Opening the Source File!";
        return 0;
    }
    fpt.open("tmp.txt", fstream::in);
    if (!fpt)
    {
        cout << "\nError Occurred while Opening/Creating tmp File!";
        return 0;
    }
    while (fpt >> noskipws >> ch)
    {
        ch = ch - 100;
        fps << ch;
    }
    fps.close();
    fpt.close();
    cout << "\nFile '" << fileName << "' Decrypted Successfully!";
    cout << endl;

};
//Functions for basic encryption end over here

//Functions for aes encryption start from here
int aesencrypt() {
    char fileName[30], ch;
    fstream fps, fpt;
    cout << "Enter the File name: ";
    cin >> gets_s(fileName); //Getting the file to encrypt
    fps.open(fileName, fstream::in);
    if (!fps)//If the file is not present then...
    {
        cout << "\nError!, Opening the Source File (to Read)!";
        return 0;
    }
    string password;
    string encrypted;
    password = "SecureComms123";
    cout << "Password (authentication tag): " << password << endl;
    FileSource fs1(fileName, true,
        new DefaultEncryptorWithMAC(
            (byte*)&password[0], password.size(),
              new HexEncoder(
                   new StringSink(encrypted)
                )
        )
    );
        cout << "Encrypted: \n\n" << encrypted << endl;

   

};

int aesdecrypt() {
    char fileName[30], ch;
    fstream fps, fpt;
    cout << "Enter the File name: ";
    cin >> gets_s(fileName); //Getting the file to encrypt
    fps.open(fileName, fstream::in);
    if (!fps)//If the file is not present then...
    {
        cout << "\nError!, Opening the Source File (to Read)!";
        return 0;
    }
    string password = "SecureComms123";
    cout << "Password (authentication tag): " << password << endl;
    string encrypted, decrypted;

    FileSource fs1(fileName, true,
        new DefaultEncryptorWithMAC(
            (byte*)&password[0], password.size(),
            new HexEncoder(
                new StringSink(encrypted)
            )
        )
    );

    StringSource ss1(encrypted, true,
        new HexDecoder(
            new DefaultDecryptorWithMAC(
                (byte*)&password[0], password.size(),
                new StringSink(decrypted)
            )
        )
    );

    cout << "Decrypted: \n\n" << decrypted << endl;

};

//Functions for aes encryption end over here

//Functions for rsa encryption start over here
int rsaencrypt() {
    // Generate keys
    AutoSeededRandomPool rng;

    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 1536);

    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    string cipher, recovered;
    char fileName[30], ch;
    fstream fps, fpt;
    cout << "Enter the File name: ";
    cin >> gets_s(fileName); //Getting the file to encrypt
    fps.open(fileName, fstream::in);
    if (!fps)//If the file is not present then...
    {
        cout << "\nError!, Opening the Source File (to Read)!";
        return 0;
    }
    RSAES_OAEP_SHA_Encryptor e(publicKey);

    FileSource f1(fileName, true,
        new PK_EncryptorFilter(rng, e,
            new StringSink(cipher)
        ) // PK_EncryptorFilter
    ); 

    cout << "Encrypted File Contents:\n\n" << cipher;

}

int rsadecrypt() {
    AutoSeededRandomPool rng;

    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 1536);

    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    char fileName[30], ch;
    string cipher, recovered; 

    fstream fps, fpt;
    cout << "Enter the File name: ";
    cin >> gets_s(fileName); //Getting the file to encrypt
    fps.open(fileName, fstream::in);
    if (!fps)//If the file is not present then...
    {
        cout << "\nError!, Opening the Source File (to Read)!";
        return 0;
    }
    RSAES_OAEP_SHA_Encryptor e(publicKey);

    FileSource f1(fileName, true,
        new PK_EncryptorFilter(rng, e,
            new StringSink(cipher)
        ) // PK_EncryptorFilter
    );

    RSAES_OAEP_SHA_Decryptor d(privateKey);

    StringSource ss2(cipher, true,
        new PK_DecryptorFilter(rng, d,
            new StringSink(recovered)
        ) // PK_DecryptorFilter
    ); // StringSource

    cout << "Decrypted File Contents:\n\n" << recovered;

    assert(fileName == recovered);

}


//Functions for rsa encryption end over here



//Main function 
//Switch case used for a simple GUI
int main()
{

    int ch;
    while (1)
    {
        cout << "\n\n===FILE ENCRYPTION SYSTEM===\n";

        cout << "\n[1] Basic Encryption\n[2] AES encryption\n[3] RSA encryption\n[4] Basic decryption\n[5] AES decryption\n[6] RSA decryption\n[7] Exit\n\n";
        cout << "Enter choice:\t";
        cin >> ch; 

        switch(ch){
        case 1:
            encryp();
            break;
        case 2:
            aesencrypt();
            break;
        case 3:
            rsaencrypt();
            break;
        case 4:
            decryp();
            break;
        case 5:
            aesdecrypt();
            break;
        case 6:
            rsadecrypt();
            break;
        case 7:
            exit(1);
            break;
       
        default:"Invalid Choice";
        }
    }


    return 0;
}