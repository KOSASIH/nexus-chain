#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "ethereum.h"
#include "block.h"
#include "transaction.h"
#include "smart_contract.h"

using namespace boost::asio;
using namespace boost::asio::ip;

Ethereum::Ethereum(std::string networkId, std::string genesisBlockHash) :
    networkId_(networkId), genesisBlockHash_(genesisBlockHash), blockchain_(new Blockchain()) {
    // Initialize the Ethereum network
    init();
}

void Ethereum::init() {
    // Create a new blockchain with the genesis block
    blockchain_->addBlock(new Block(genesisBlockHash_, 0, std::vector<Transaction>()));

    // Start the Ethereum node
    startNode();
}

void Ethereum::startNode() {
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

void Ethereum::processPacket(char* buffer, std::size_t length) {
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
        case PacketType::SMART_CONTRACT_CALL:
            // Process the smart contract call packet
            processSmartContractCallPacket(packet);
            break;
        default:
            std::cerr << "Unknown packet type: " << packet.getType() << std::endl;
            break;
    }
}

void Ethereum::processNewBlockPacket(Packet packet) {
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

void Ethereum::processNewTransactionPacket(Packet packet) {
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

void Ethereum::processSmartContractCallPacket(Packet packet) {
    // Get the smart contract call from the packet
    SmartContractCall call = packet.getSmartContractCall();

    // Execute the smart contract call
    executeSmartContractCall(call);
}

void Ethereum::executeSmartContractCall(SmartContractCall call) {
    // Get the smart contract from the call
    SmartContract contract = call.getContract();

    // Execute the smart contract
    contract.execute(call.getFunction(), call.getArguments());
}

void Ethereum::broadcastNewBlock(Block block) {
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

void Ethereum::broadcastNewTransaction(Transaction transaction) {
    // Create a new packet with the transaction
    Packet packet(PacketType::NEW_TRANSACTION, transaction);

    // Serialize the packet
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << packet;

    // Broadcast the packet to the network
    udp::socket socket(ioService_);
    socket.async_send_to(oss.str(), udp::endpoint(udp::v4(), 0),
        [this](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Error broadcasting new transaction: " << ec.message() << std::endl;
            }
        });
}

bool Ethereum::verifyBlock(Block block) {
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

    // Verify the block's smart contract calls
    for (const auto& call : block.getSmartContractCalls()) {
        if (!verifySmartContractCall(call)) {
            return false;
        }
    }

    return true;
}

bool Ethereum::verifyTransaction(Transaction transaction) {
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

bool Ethereum::verifySmartContractCall(SmartContractCall call) {
    // Verify the smart contract call's hash
    if (!call.verifyHash()) {
        return false;
    }

    // Verify the smart contract call's contract and function
    if (!verifySmartContractAndFunction(call.getContract(), call.getFunction())) {
        return false;
    }

    return true;
}

bool Ethereum::verifySenderAndRecipient(std::string sender, std::string recipient) {
    // Verify the sender and recipient's addresses
    if (!verifyAddress(sender) || !verifyAddress(recipient)) {
        return false;
    }

    return true;
}

bool Ethereum::verifySmartContractAndFunction(SmartContract contract, std::string function) {
    // Verify the smart contract's address
    if (!verifyAddress(contract.getAddress())) {
        return false;
    }

    // Verify the function's existence in the smart contract
    if (!contract.hasFunction(function)) {
        return false;
    }

    return true;
}

bool Ethereum::verifyAddress(std::string address) {
    // Verify the address's format
    if (!isValidAddressFormat(address)) {
        return false;
    }

    return true;
}

bool Ethereum::isValidAddressFormat(std::string address) {
    // Check if the address is a valid Ethereum address
    return address.size() == 42 && address[0] == '0' && address[1] == 'x';
}
