#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/ec.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Signature {
public:
    std::string sign(std::string message, EC_KEY* privateKey);
    bool verify(std::string message, std::string signature, EC_KEY* publicKey);

private:
    ECDSA_SIG* ecdsaSig_;
};

std::string Signature::sign(std::string message, EC_KEY* privateKey) {
    // Sign message using ECDSA
    ECDSA_SIG* ecdsaSig = ECDSA_SIG_new();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, (unsigned char*)message.c_str(), message.size());
    SHA256_Final(hash, &sha256Ctx);
    ECDSA_sign(privateKey, hash, ecdsaSig);
    std::string signature = "";
    for (int i = 0; i < ECDSA_SIG_size(ecdsaSig); i++) {
        char buffer[3];
        sprintf(buffer, "%02x", ecdsaSig->r[i]);
        signature += buffer;
    }
    for (int i = 0; i < ECDSA_SIG_size(ecdsaSig); i++) {
        char buffer[3];
        sprintf(buffer, "%02x", ecdsaSig->s[i]);
        signature += buffer;
    }
    ECDSA_SIG_free(ecdsaSig);
    return signature;
}

bool Signature::verify(std::string message, std::string signature, EC_KEY* publicKey) {
    // Verify signature using ECDSA
    ECDSA_SIG* ecdsaSig = ECDSA_SIG_new();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256Ctx;
    SHA256_Init(&sha256Ctx);
    SHA256_Update(&sha256Ctx, (unsigned char*)message.c_str(), message.size());
    SHA256_Final(hash, &sha256Ctx);
    int signatureLen = signature.size();
    unsigned char* signatureBytes = new unsigned char[signatureLen];
    for (int i = 0; i < signatureLen; i++) {
        signatureBytes[i] = (unsigned char)signature[i];
    }
    ECDSA_SIG_set0(ecdsaSig, signatureBytes, signatureLen);
    int result = ECDSA_verify(publicKey, hash, ecdsaSig);
    delete[] signatureBytes;
    ECDSA_SIG_free(ecdsaSig);
    return result == 1;
}

BOOST_CLASS_EXPORT_GUID(Signature, "Signature")
