#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <openssl/sha.h>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Block {
public:
    Block(std::string previousHash, std::vector<Transaction> transactions);
    std::string getHash();
    std::string getPreviousHash();
    std::vector<Transaction> getTransactions();
    void setTransactions(std::vector<Transaction> transactions);
    void mineBlock(int difficulty);

private:
    std::string previousHash_;
    std::vector<Transaction> transactions_;
    std::string hash_;
    int nonce_;
};

Block::Block(std::string previousHash, std::vector<Transaction> transactions)
    : previousHash_(previousHash), transactions_(transactions), nonce_(0) {
    hash_ = calculateHash();
}

std::string Block::getHash() {
    return hash_;
}

std::string Block::getPreviousHash() {
    return previousHash_;
}

std::vector<Transaction> Block::getTransactions() {
    return transactions_;
}

void Block::setTransactions(std::vector<Transaction> transactions) {
    transactions_ = transactions;
    hash_ = calculateHash();
}

void Block::mineBlock(int difficulty) {
    // Mine block using Proof of Work
    ProofOfWork pow(hash_, difficulty, nonce_);
    std::string proof = pow.calculateProof();
    hash_ = proof;
}

std::string Block::calculateHash() {
    // Calculate block hash using cryptographic hash function
    std::string data = previousHash_ + serializeTransactions();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (unsigned char*)data.c_str(), data.size());
    SHA256_Final(hash, &sha256);

    std::string hashStr = "";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        char buffer[3];
        sprintf(buffer, "%02x", hash[i]);
        hashStr += buffer;
    }

    return hashStr;
}

std::string Block::serializeTransactions() {
    // Serialize transactions using Boost Serialization
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << transactions_;
    return oss.str();
}

BOOST_CLASS_EXPORT_GUID(Block, "Block")
