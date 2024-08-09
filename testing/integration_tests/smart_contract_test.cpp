#include <gtest/gtest.h>
#include "smart_contract/smart_contract.hpp"

class SmartContractTest : public ::testing::Test {
protected:
    SmartContract smartContract;

    void SetUp() override {
        smartContract.init();
    }
};

TEST_F(SmartContractTest, ExecuteContract) {
    // Create a sample contract
    Contract contract = createContract();
    smartContract.executeContract(contract);
    ASSERT_TRUE(smartContract.getContractStatus(contract) == ContractStatus::EXECUTED);
}

TEST_F(SmartContractTest, InteractWithContract) {
    // Create a sample contract
    Contract contract = createContract();
    smartContract.interactWithContract(contract);
    ASSERT_TRUE(smartContract.getContractStatus(contract) == ContractStatus::INTERACTED);
}
