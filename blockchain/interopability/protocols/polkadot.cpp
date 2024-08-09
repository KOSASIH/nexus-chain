#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "polkadot.h"
#include "block.h"
#include "transaction.h"
#include "parachain.h"

using namespace boost::asio;
using namespace boost::asio::ip;

Polkadot::Polkadot(std::string networkId, std::string genesisBlockHash) :
    networkId_(networkId), genesisBlockHash_(genesisBlockHash), blockchain_(new Blockchain()) {
    // Initialize the Polkadot network
    init();
}

void Polkadot::init() {
    // Create a new blockchain with the genesis block
    blockchain_->addBlock(new Block(genesisBlockHash_, 0, std::vector<Transaction>()));

    // Start the Polkadot node
    startNode();
}

void Polkadot::startNode() {
    // Create a UDP socket
    udp::socket socket(ioService_);

    // Bind the socket to a random port
    udp::endpoint endpoint(udp::v4(), 0);
    socket.bind(endpoint);

    // Start listening for incoming connections
    socket.async_receive_from(buffer(1024), endpoint,
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // Process the incoming packet
                processPacket(buffer, length);
            } else {
                std::cerr << "Error receiving packet: " << ec.message() << std::endl;
            }
        });
}

void Polkadot::processPacket(char* buffer, std::size_t length) {
    // Deserialize the packet
    Packet packet;
    std::istringstream iss(buffer, length);
    boost::archive::text_iarchive ia(iss);
    ia >> packet;

    // Handle the packet based on its type
    switch (packet.getType()) {
        case PacketType::NEW_BLOCK:
            // Process the new block packet
            processNewBlockPacket(packet);
            break;
        case PacketType::NEW_TRANSACTION:
            // Process the new transaction packet
            processNewTransactionPacket(packet);
            break;
        case PacketType::PARACHAIN_REGISTRATION:
            // Process the parachain registration packet
            processParachainRegistrationPacket(packet);
            break;
        default:
            std::cerr << "Unknown packet type: " << packet.getType() << std::endl;
            break;
    }
}

void Polkadot::processNewBlockPacket(Packet packet) {
    // Get the new block from the packet
    Block block = packet.getBlock();

    // Verify the block
    if (verifyBlock(block)) {
        // Add the block to the blockchain
        blockchain_->addBlock(block);

        // Broadcast the new block to the network
        broadcastNewBlock(block);
    } else {
        std::cerr << "Invalid block: " << block.getHash() << std::endl;
    }
}

void Polkadot::processNewTransactionPacket(Packet packet) {
    // Get the new transaction from the packet
    Transaction transaction = packet.getTransaction();

    // Verify the transaction
    if (verifyTransaction(transaction)) {
        // Add the transaction to the transaction pool
        transactionPool_.addTransaction(transaction);

        // Broadcast the new transaction to the network
        broadcastNewTransaction(transaction);
    } else {
        std::cerr << "Invalid transaction: " << transaction.getHash() << std::endl;
    }
}

void Polkadot::processParachainRegistrationPacket(Packet packet) {
    // Get the parachain registration from the packet
    ParachainRegistration registration = packet.getParachainRegistration();

    // Verify the registration
    if (verifyParachainRegistration(registration)) {
        // Register the parachain
        registerParachain(registration);

        // Broadcast the parachain registration to the network
        broadcastParachainRegistration(registration);
    } else {
        std::cerr << "Invalid parachain registration: " << registration.getHash() << std::endl;
    }
}

void Polkadot::registerParachain(ParachainRegistration registration) {
    // Register the parachain with the relay chain
    blockchain_->registerParachain(registration);
}

void Polkadot::broadcastNewBlock(Block block) {
    // Create a new packet with the block
    Packet packet(PacketType::NEW_BLOCK, block);

    // Serialize the packet
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << packet;

    // Broadcast the packet to the network
    udp::socket socket(ioService_);
    socket.async_send_to(oss.str(), udp::endpoint(udp::v4(), 0),
        [this](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Error broadcasting new block: " << ec.message() << std::endl;
            }
        });
}

void Polkadot::broadcastParachainRegistration(ParachainRegistration registration) {
    // Create a new packet with the parachain registration
    Packet packet(PacketType::PARACHAIN_REGISTRATION, registration);

    // Serialize the packet
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << packet;

    // Broadcast the packet to the network
    udp::socket socket(ioService_);
    socket.async_send_to(oss.str(), udp::endpoint(udp::v4(), 0),
        [this](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Error broadcasting parachain registration: " << ec.message() << std::endl;
            }
        });
}

bool Polkadot::verifyBlock(Block block) {
    // Verify the block's hash
    if (!block.verifyHash()) {
        return false;
    }

    // Verify the block's transactions
    for (const auto& transaction : block.getTransactions()) {
        if (!verifyTransaction(transaction)) {
            return false;
        }
    }

    return true;
}

bool Polkadot::verifyTransaction(Transaction transaction) {
    // Verify the transaction's hash
    if (!transaction.verifyHash()) {
        return false;
    }

    // Verify the transaction's sender and recipient
    if (!verifySenderAndRecipient(transaction.getSender(), transaction.getRecipient())) {
        return false;
    }

    return true;
}

bool Polkadot::verifyParachainRegistration(ParachainRegistration registration) {
    // Verify the parachain registration's hash
    if (!registration.verifyHash()) {
        return false;
    }

    // Verify the parachain registration's parachain and relay chain
    if (!verifyParachainAndRelayChain(registration.getParachain(), registration.getRelayChain())) {
        return false;
    }

    return true;
}

bool Polkadot::verifySenderAndRecipient(std::string sender, std::string recipient) {
    // Verify the sender and recipient's addresses
    if (!verifyAddress(sender) || !verifyAddress(recipient)) {
        return false;
    }

    return true;
}

bool Polkadot::verifyParachainAndRelayChain(Parachain parachain, RelayChain relayChain) {
    // Verify the parachain and relay chain's addresses
    if (!verifyAddress(parachain.getAddress()) || !verifyAddress(relayChain.getAddress())) {
        return false;
    }

    return true;
}

bool Polkadot::verifyAddress(std::string address) {
    // Verify the address's format
    if (!isValidAddressFormat(address)) {
        return false;
    }

    return true;
}

bool Polkadot::isValidAddressFormat(std::string address) {
    // Check if the address is a valid Polkadot address
    return address.size() == 42 && address[0] == '0' && address[1] == 'x';
}
