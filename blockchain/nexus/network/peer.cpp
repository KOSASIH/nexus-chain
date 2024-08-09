#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "peer.h"
#include "node.h"
#include "packet.h"

using namespace boost::asio;
using namespace boost::asio::ip;

Peer::Peer(std::string peerId, std::string ipAddress, int port) :
    peerId_(peerId), ipAddress_(ipAddress), port_(port), node_(nullptr) {
    // Initialize the peer
    init();
}

void Peer::init() {
    // Create a new node object
    node_ = new Node(peerId_, ipAddress_, port_);
}

void Peer::connectToNode(std::string nodeId, std::string ipAddress, int port) {
    // Create a new packet to send to the node
    Packet packet(PacketType::ROUTE_REQUEST, peerId_, nodeId, 1);

    // Send the packet to the node
    node_->sendPacket(ipAddress, packet);
}

void Peer::disconnectFromNode(std::string nodeId) {
    // Remove the node from the routing table
    node_->routingTable_.removeNode(nodeId);
}

void Peer::sendData(std::string destination, std::string data) {
    // Create a new packet to send to the destination
    Packet packet(PacketType::DATA, peerId_, destination, data);

    // Send the packet to the destination
    node_->sendPacket(destination, packet);
}

void Peer::receiveData(Packet packet) {
    // Process the received data packet
    std::cout << "Received data from " << packet.getSource() << ": " << packet.getData() << std::endl;
}

BOOST_CLASS_EXPORT_GUID(Peer, "Peer")
