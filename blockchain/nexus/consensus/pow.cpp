#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/sha.h>

class ProofOfWork {
public:
    ProofOfWork(std::string blockHash, int difficulty, int nonce);
    bool validateProof(std::string proof);
    std::string calculateProof();

private:
    std::string blockHash_;
    int difficulty_;
    int nonce_;
    std::vector<std::string> hashes_;
};

ProofOfWork::ProofOfWork(std::string blockHash, int difficulty, int nonce)
    : blockHash_(blockHash), difficulty_(difficulty), nonce_(nonce) {}

bool ProofOfWork::validateProof(std::string proof) {
    // Validate proof using cryptographic hash function
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (unsigned char*)proof.c_str(), proof.size());
    SHA256_Final(hash, &sha256);

    std::string hashStr = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }

    int leadingZeros = 0;
    for (char c : hashStr) {
        if (c == '0') {
            leadingZeros++;
        } else {
            break;
        }
    }

    return leadingZeros >= difficulty_;
}

std::string ProofOfWork::calculateProof() {
    // Calculate proof using cryptographic hash function
    std::string proof = blockHash_ + std::to_string(nonce_);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (unsigned char*)proof.c_str(), proof.size());
    SHA256_Final(hash, &sha256);

    std::string hashStr = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }

    while (!validateProof(proof)) {
        nonce_++;
        proof = blockHash_ + std::to_string(nonce_);
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, (unsigned char*)proof.c_str(), proof.size());
        SHA256_Final(hash, &sha256);

        hashStr = "";
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            char buffer[3];
            sprintf(buffer, "%02x", hash[i]);
            hashStr += buffer;
        }
    }

    return proof;
}
