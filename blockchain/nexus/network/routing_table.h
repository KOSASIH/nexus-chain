#ifndef ROUTING_TABLE_H
#define ROUTING_TABLE_H

#include <string>
#include <map>

class RoutingTable {
public:
    void addNode(std::string nodeId, std::string ipAddress, int port);
    void removeNode(std::string nodeId);
    std::string getNextHop(std::string destination);
    void updateRoute(std::string sourceNodeId, int hopCount);

private:
    std::map<std::string, std::string> nodeMap_;
    std::map<std::string, int> hopCountMap_;

    friend class boost::serialization::access;
    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & nodeMap_;
        ar & hopCountMap_;
    }
};

#endif // ROUTING_TABLE_H
