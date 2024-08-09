#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/sha.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Hash {
public:
    std::string sha256(std::string input);
    std::string sha3_256(std::string input);
    std::string blake2b(std::string input);

private:
    SHA256_CTX sha256Ctx_;
    SHA3_CTX sha3Ctx_;
    blake2b_state blake2bState_;
};

std::string Hash::sha256(std::string input) {
    // Compute SHA-256 hash of input
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, (unsigned char*)input.c_str(), input.size());
    SHA256_Final(hash, &sha256Ctx);
    std::string hashStr = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }
    return hashStr;
}

std::string Hash::sha3_256(std::string input) {
    // Compute SHA-3-256 hash of input
    unsigned char hash[SHA3_256_DIGEST_LENGTH];
    SHA3_CTX sha3Ctx;
    SHA3_Init(&sha3Ctx, 256);
    SHA3_Update(&sha3Ctx, (unsigned char*)input.c_str(), input.size());
    SHA3_Final(hash, &sha3Ctx);
    std::string hashStr = "";
    for (int i = 0; i < SHA3_256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }
    return hashStr;
}

std::string Hash::blake2b(std::string input) {
    // Compute BLAKE2b hash of input
    unsigned char hash[BLAKE2B_OUTBYTES];
    blake2b_state blake2bState;
    blake2b_init(&blake2bState, BLAKE2B_OUTBYTES);
    blake2b_update(&blake2bState, (unsigned char*)input.c_str(), input.size());
    blake2b_final(&blake2bState, hash);
    std::string hashStr = "";
    for (int i = 0; i < BLAKE2B_OUTBYTES; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }
    return hashStr;
}

BOOST_CLASS_EXPORT_GUID(Hash, "Hash")
