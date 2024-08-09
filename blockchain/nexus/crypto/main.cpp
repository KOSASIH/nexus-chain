#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "quantum_resistant.h"
#include "classical.h"
#include "hash.h"
#include "signature.h"
#include "keypair.h"

int main() {
    // Create a new key pair
    KeyPair keyPair;

    // Get the private and public keys
    std::string privateKey = keyPair.getPrivateKey();
    std::string publicKey = keyPair.getPublicKey();

    // Create a new quantum-resistant object
    QuantumResistant quantumResistant(privateKey);

    // Create a new classical object
    Classical classical(privateKey);

    // Create a new hash object
    Hash hash;

    // Create a new signature object
    Signature signature;

    // Test the quantum-resistant object
    std::string message = "Hello, World!";
    std::string encryptedMessage = quantumResistant.encrypt(message);
    std::string decryptedMessage = quantumResistant.decrypt(encryptedMessage);
    std::cout << "Quantum-Resistant Encryption/Decryption Test: " << decryptedMessage << std::endl;

    // Test the classical object
    encryptedMessage = classical.encrypt(message);
    decryptedMessage = classical.decrypt(encryptedMessage);
    std::cout << "Classical Encryption/Decryption Test: " << decryptedMessage << std::endl;

    // Test the hash object
    std::string hashValue = hash.sha256(message);
    std::cout << "SHA-256 Hash Test: " << hashValue << std::endl;

    // Test the signature object
    std::string signatureValue = signature.sign(message, privateKey);
    bool verificationResult = signature.verify(message, signatureValue, publicKey);
    std::cout << "ECDSA Signature Verification Test: " << verificationResult << std::endl;

    return 0;
}
