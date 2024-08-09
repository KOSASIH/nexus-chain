#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Wallet {
public:
    Wallet(std::string privateKey);
    std::string getPublicKey();
    std::string getPrivateKey();
    void signTransaction(Transaction& transaction);

private:
    EC_KEY* ecKey_;
};

Wallet::Wallet(std::string privateKey) {
    ecKey_ = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_set_asn1_flag(ecKey_, OPENSSL_EC_NAMED_CURVE);
    EC_KEY_set_private_key(ecKey_, (const unsigned char*)privateKey.c_str());
}

std::string Wallet::getPublicKey() {
    // Get public key from private key using elliptic curve cryptography
    unsigned char publicKey[65];
    EC_KEY_get_public_key(ecKey_, publicKey);
    std::string publicKeyStr = "";
    for (int i = 0; i < 65; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", publicKey[i]);
        publicKeyStr += buffer;
    }
    return publicKeyStr;
}

std::string Wallet::getPrivateKey() {
    // Get private key from EC_KEY object
    unsigned char privateKey[32];
    EC_KEY_get_private_key(ecKey_, privateKey);
    std::string privateKeyStr = "";
    for (int i = 0; i < 32; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", privateKey[i]);
        privateKeyStr += buffer;
    }
    return privateKeyStr;
}

void Wallet::signTransaction(Transaction& transaction) {
    // Sign transaction using elliptic curve cryptography
    transaction.signTransaction(ecKey_);
}

BOOST_CLASS_EXPORT_GUID(Wallet, "Wallet")
