#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <boost/serialization/string.hpp>

enum class PacketType {
    DATA,
    ROUTE_REQUEST,
    ROUTE_RESPONSE
};

class Packet {
public:
    Packet(PacketType type, std::string source, std::string destination, int hopCount = 0, std::string data = "");
    PacketType getType() const;
    std::string getSource() const;
    std::string getDestination() const;
    int getHopCount() const;
    std::string getData() const;

private:
    PacketType type_;
    std::string source_;
    std::string destination_;
    int hopCount_;
    std::string data_;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & type_;
        ar & source_;
        ar & destination_;
        ar & hopCount_;
        ar & data_;
    }
};

#endif // PACKET_H
