#include <iostream>
#include <string>
#include <vector>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <ethereum/ERC20.sol>

class ERC20Bridge {
public:
    std::string contractAddress;
    std::string abi;

    ERC20Bridge(std::string contractAddress, std::string abi)
        : contractAddress(contractAddress), abi(abi) {}

    void lockTokens(std::string tokenAddress, uint256 amount) {
        // Call the ERC20 contract's lockTokens function
        ethereum::ERC20 erc20(contractAddress, abi);
        erc20.lockTokens(tokenAddress, amount);
    }

    void unlockTokens(std::string tokenAddress, uint256 amount) {
        // Call the ERC20 contract's unlockTokens function
        ethereum::ERC20 erc20(contractAddress, abi);
        erc20.unlockTokens(tokenAddress, amount);
    }

    uint256 getLockedTokens(std::string tokenAddress) {
        // Call the ERC20 contract's getLockedTokens function
        ethereum::ERC20 erc20(contractAddress, abi);
        return erc20.getLockedTokens(tokenAddress);
    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & contractAddress;
        ar & abi;
    }
};

int main() {
    ERC20Bridge bridge("0xERC20ContractAddress", "ERC20ABI");
    bridge.lockTokens("0xTokenAddress", 100);
    std::cout << "Locked 100 tokens" << std::endl;
    return 0;
}
