#include <iostream>
#include <string>
#include <vector>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <substrate/rpc.hpp>

class SubstrateBridge {
public:
    std::string nodeUrl;
    std::string parachainId;

    SubstrateBridge(std::string nodeUrl, std::string parachainId)
        : nodeUrl(nodeUrl), parachainId(parachainId) {}

    void transferTokens(std::string tokenAddress, uint256 amount) {
        // Create a Substrate RPC client
        substrate::RpcClient client(nodeUrl);

        // Create a transfer transaction
        substrate::Transaction transaction;
        transaction.set_module("balances");
        transaction.set_call("transfer");
        transaction.add_argument(tokenAddress);
        transaction.add_argument(amount);

        // Send the transaction
        client.send_transaction(transaction);
    }

    uint256 getBalance(std::string tokenAddress) {
        // Create a Substrate RPC client
        substrate::RpcClient client(nodeUrl);

        // Get the balance of the token
        substrate::RpcResponse response = client.rpc_call("balances", "balance", tokenAddress);
        return response.get_uint256();
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & nodeUrl;
        ar & parachainId;
    }
};

int main() {
    SubstrateBridge bridge("https://substrate-node.io", "parachain-id");
    bridge.transferTokens("token-address", 100);
    std::cout << "Transferred 100 tokens" << std::endl;
    return 0;
}
