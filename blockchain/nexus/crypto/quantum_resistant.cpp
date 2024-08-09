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
#include <latticecrypto/latticecrypto.h>

class QuantumResistant {
public:
    QuantumResistant(std::string privateKey);
    std::string getPublicKey();
    std::string encrypt(std::string plaintext);
    std::string decrypt(std::string ciphertext);

private:
    LatticeCrypto* latticeCrypto_;
    std::string privateKey_;
};

QuantumResistant::QuantumResistant(std::string privateKey)
    : privateKey_(privateKey) {
    latticeCrypto_ = new LatticeCrypto();
    latticeCrypto_->init(privateKey_);
}

std::string QuantumResistant::getPublicKey() {
    // Get public key from private key using lattice cryptography
    std::string publicKey = latticeCrypto_->getPublicKey();
    return publicKey;
}

std::string QuantumResistant::encrypt(std::string plaintext) {
    // Encrypt plaintext using lattice cryptography
    std::string ciphertext = latticeCrypto_->encrypt(plaintext);
    return ciphertext;
}

std::string QuantumResistant::decrypt(std::string ciphertext) {
    // Decrypt ciphertext using lattice cryptography
    std::string plaintext = latticeCrypto_->decrypt(ciphertext);
    return plaintext;
}

  BOOST_CLASS_EXPORT_GUID(QuantumResistant, "QuantumResistant")
