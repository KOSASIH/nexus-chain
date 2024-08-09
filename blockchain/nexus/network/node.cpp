#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "node.h"
#include "peer.h"
#include "packet.h"
#include "routing_table.h"

using namespace boost::asio;
using namespace boost::asio::ip;

Node::Node(std::string nodeId, std::string ipAddress, int port) :
    nodeId_(nodeId), ipAddress_(ipAddress), port_(port), socket_(ioService_) {
    // Initialize the node
    init();
}

void Node::init() {
    // Create a UDP socket
    socket_.open(udp::v4());

    // Bind the socket to the IP address and port
    udp::endpoint endpoint(udp::v4(), port_);
    socket_.bind(endpoint);

    // Start receiving packets
    startReceive();
}

void Node::startReceive() {
    // Create a buffer to store the received packet
    char buffer[1024];

    // Start receiving packets asynchronously
    socket_.async_receive_from(buffer(1024), endpoint_,
        [this](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // Process the received packet
                processPacket(buffer, length);
            } else {
                std::cerr << "Error receiving packet: " << ec.message() << std::endl;
            }
        });
}

void Node::processPacket(char* buffer, std::size_t length) {
    // Deserialize the packet
    Packet packet;
    std::istringstream iss(buffer, length);
    boost::archive::text_iarchive ia(iss);
    ia >> packet;

    // Handle the packet based on its type
    switch (packet.getType()) {
        case PacketType::DATA:
            // Forward the data packet to the next hop
            forwardPacket(packet);
            break;
        case PacketType::ROUTE_REQUEST:
            // Handle the route request packet
            handleRouteRequest(packet);
            break;
        case PacketType::ROUTE_RESPONSE:
            // Handle the route response packet
            handleRouteResponse(packet);
            break;
        default:
            std::cerr << "Unknown packet type: " << packet.getType() << std::endl;
            break;
    }
}

void Node::forwardPacket(Packet packet) {
    // Get the next hop from the routing table
    std::string nextHop = routingTable_.getNextHop(packet.getDestination());

    // Send the packet to the next hop
    sendPacket(nextHop, packet);
}

void Node::handleRouteRequest(Packet packet) {
    // Get the source node ID from the packet
    std::string sourceNodeId = packet.getSource();

    // Check if the source node is in the routing table
    if (routingTable_.hasNode(sourceNodeId)) {
        // Send a route response packet to the source node
        sendRouteResponse(sourceNodeId);
    } else {
        // Forward the route request packet to the next hop
        forwardPacket(packet);
    }
}

void Node::handleRouteResponse(Packet packet) {
    // Get the source node ID from the packet
    std::string sourceNodeId = packet.getSource();

    // Update the routing table with the new route
    routingTable_.updateRoute(sourceNodeId, packet.getHopCount());
}

void Node::sendPacket(std::string destination, Packet packet) {
    // Serialize the packet
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << packet;

    // Send the packet to the destination node
    udp::endpoint endpoint(udp::v4(), port_);
    socket_.async_send_to(oss.str(), endpoint,
        [this](boost::system::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Error sending packet: " << ec.message() << std::endl;
            }
        });
}

void Node::sendRouteResponse(std::string destination) {
    // Create a route response packet
    Packet packet(PacketType::ROUTE_RESPONSE, nodeId_, destination, 1);

    // Send the packet to the destination node
    sendPacket(destination, packet);
}

BOOST_CLASS_EXPORT_GUID(Node, "Node")
