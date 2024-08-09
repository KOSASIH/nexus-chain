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

class Transaction {
public:
    Transaction(std::string sender, std::string recipient, int amount);
    std::string getSender();
    std::string getRecipient();
    int getAmount();
    void signTransaction(EC_KEY* ecKey);
    bool isValid();

private:
    std::string sender_;
    std::string recipient_;
    int amount_;
    std::string signature_;
};

Transaction::Transaction(std::string sender, std::string recipient, int amount)
    : sender_(sender), recipient_(recipient), amount_(amount) {}

std::string Transaction::getSender() {
    return sender_;
}

std::string Transaction::getRecipient() {
    return recipient_;
}

int Transaction::getAmount() {
    return amount_;
}

void Transaction::signTransaction(EC_KEY* ecKey) {
    // Sign transaction using elliptic curve cryptography
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (unsigned char*)serialize().c_str(), serialize().size());
    SHA256_Final(hash, &sha256);

    ECDSA_SIG* sig = ECDSA_SIG_new();
    ECDSA_sign(0, hash, sizeof(hash), sig, ecKey_);
    signature_ = serializeSignature(sig);
    ECDSA_SIG_free(sig);
}

bool Transaction::isValid() {
    // Verify transaction signature using elliptic curve cryptography
    EC_KEY* ecKey = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_set_asn1_flag(ecKey, OPENSSL_EC_NAMED_CURVE);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (unsigned char*)serialize().c_str(), serialize().size());
    SHA256_Final(hash, &sha256);

    ECDSA_SIG* sig = deserializeSignature(signature_);
    int result = ECDSA_do_verify((unsigned char*)hash, sizeof(hash), sig, ecKey_);
    ECDSA_SIG_free(sig);
    EC_KEY_free(ecKey);

    return result == 1;
}

std::string Transaction::serialize() {
    // Serialize transaction using Boost Serialization
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << sender_;
    oa << recipient_;
    oa << amount_;
    return oss.str();
}

std::string Transaction::serializeSignature(ECDSA_SIG* sig) {
    // Serialize signature using Boost Serialization
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << sig;
    return oss.str();
}

ECDSA_SIG* Transaction::deserializeSignature(std::string signature) {
    // Deserialize signature using Boost Serialization
    std::istringstream iss(signature);
    boost::archive::text_iarchive ia(iss);
    ECDSA_SIG* sig;
    ia >> sig;
    return sig;
}

BOOST_CLASS_EXPORT_GUID(Transaction, "Transaction")
   
