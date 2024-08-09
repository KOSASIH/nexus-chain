#include <iostream>
#include <fstream>
#include <string>
#include "cryptlib.h"
#include "rijndael.h"
#include "hex.h"

using namespace std;
using namespace CryptoPP;

class Encryption {
public:
    void encryptFile(const string& inputFile, const string& outputFile, const string& key) {
        // Create a AES-256-CBC encryptor
        AES::Encryption aesEncryption((byte*)key.c_str(), key.size());
        CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte*)key.c_str());

        // Open input and output files
        ifstream inputStream(inputFile, ios::binary);
        ofstream outputStream(outputFile, ios::binary);

        // Encrypt file
        StringSource(inputStream, true, new StreamTransformationFilter(cbcEncryption, new HexEncoder(new FileSink(outputStream))));
    }
};
