#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Classical {
public:
    Classical(std::string privateKey);
    std::string getPublicKey();
    std::string encrypt(std::string plaintext);
    std::string decrypt(std::string ciphertext);

private:
    AES_KEY aesKey_;
    std::string privateKey_;
};

Classical::Classical(std::string privateKey)
    : privateKey_(privateKey) {
    AES_set_encrypt_key((const unsigned char*)privateKey_.c_str(), privateKey_.size() * 8, &aesKey_);
}

std::string Classical::getPublicKey() {
    // Get public key from private key using RSA
    RSA* rsa = RSA_new();
    rsa->n = BN_new();
    rsa->e = BN_new();
    BN_set_word(rsa->e, 65537);
    BN_bin2bn((const unsigned char*)privateKey_.c_str(), privateKey_.size(), rsa->n);
    std::string publicKey = "";
    for (int i = 0; i < RSA_size(rsa); i++) {
        char buffer[3];
        sprintf(buffer, "%02x", (unsigned char)rsa->n->d[i]);
        publicKey += buffer;
    }
    RSA_free(rsa);
    return publicKey;
}

std::string Classical::encrypt(std::string plaintext) {
    // Encrypt plaintext using AES-256-CBC
    unsigned char iv[AES_BLOCK_SIZE];
    RAND_bytes(iv, AES_BLOCK_SIZE);
    std::string ciphertext = "";
    AES_CTX ctx;
    AES_init_ctx_iv(&ctx, &aesKey_, iv, AES_BLOCK_SIZE);
    int len = plaintext.size();
    int written = 0;
    while (written < len) {
        unsigned char buffer[1024];
        int blockSize = std::min(1024, len - written);
        AES_encrypt((unsigned char*)plaintext.c_str() + written, buffer, &ctx, blockSize);
        ciphertext += std::string((char*)buffer, blockSize);
        written += blockSize;
    }
    ciphertext += std::string((char*)iv, AES_BLOCK_SIZE);
    return ciphertext;
}

std::string Classical::decrypt(std::string ciphertext) {
    // Decrypt ciphertext using AES-256-CBC
    unsigned char iv[AES_BLOCK_SIZE];
    std::copy(ciphertext.begin(), ciphertext.begin() + AES_BLOCK_SIZE, iv);
    std::string plaintext = "";
    AES_CTX ctx;
    AES_init_ctx_iv(&ctx, &aesKey_, iv, AES_BLOCK_SIZE);
    int len = ciphertext.size() - AES_BLOCK_SIZE;
    int written = 0;
    while (written < len) {
        unsigned char buffer[1024];
        int blockSize = std::min(1024, len - written);
        AES_decrypt((unsigned char*)ciphertext.c_str() + written + AES_BLOCK_SIZE, buffer, &ctx, blockSize);
        plaintext += std::string((char*)buffer, blockSize);
        written += blockSize;
    }
    return plaintext;
}

BOOST_CLASS_EXPORT_GUID(Classical, "Classical") 
