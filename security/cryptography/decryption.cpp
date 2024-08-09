#include <iostream>
#include <fstream>
#include <string>
#include "cryptlib.h"
#include "rijndael.h"
#include "hex.h"

using namespace std;
using namespace CryptoPP;

class Decryption {
public:
    void decryptFile(const string& inputFile, const string& outputFile, const string& key) {
        // Create a AES-256-CBC decryptor
        AES::Decryption aesDecryption((byte*)key.c_str(), key.size());
        CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte*)key.c_str());

        // Open input and output files
        ifstream inputStream(inputFile, ios::binary);
        ofstream outputStream(outputFile, ios::binary);

        // Decrypt file
        StringSource(inputStream, true, new StreamTransformationFilter(cbcDecryption, new HexDecoder(new FileSink(outputStream))));
    }
};
