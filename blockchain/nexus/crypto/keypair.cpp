#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/ec.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class KeyPair {
public:
    KeyPair();
    std::string getPrivateKey();
    std::string getPublicKey();

private:
    EC_KEY* keyPair_;
};

KeyPair::KeyPair() {
    // Generate a new key pair using ECDSA
    keyPair_ = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(keyPair_);
}

std::string KeyPair::getPrivateKey() {
    // Get the private key from the key pair
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_ECPrivateKey(bio, keyPair_, NULL, NULL, 0, NULL, NULL);
    char* privateKey = NULL;
    long privateKeyLen = BIO_get_mem_data(bio, &privateKey);
    std::string privateKeyStr(privateKey, privateKeyLen);
    BIO_free(bio);
    return privateKeyStr;
}

std::string KeyPair::getPublicKey() {
    // Get the public key from the key pair
    BIO* bio = BIO_new(BIO_s_mem());
    PEM_write_bio_EC_PUBKEY(bio, keyPair_);
    char* publicKey = NULL;
    long publicKeyLen = BIO_get_mem_data(bio, &publicKey);
    std::string publicKeyStr(publicKey, publicKeyLen);
    BIO_free(bio);
    return publicKeyStr;
}

BOOST_CLASS_EXPORT_GUID(KeyPair, "KeyPair")
