#include <gtest/gtest.h>
#include "blockchain/blockchain.hpp"

class BlockchainTest : public ::testing::Test {
protected:
    Blockchain blockchain;

    void SetUp() override {
        blockchain.init();
    }
};

TEST_F(BlockchainTest, CreateBlock) {
    Block block = blockchain.createBlock();
    ASSERT_TRUE(block.isValid());
}

TEST_F(BlockchainTest, AddBlock) {
    Block block = blockchain.createBlock();
    blockchain.addBlock(block);
    ASSERT_TRUE(blockchain.getBlockchainSize() == 1);
}

TEST_F(BlockchainTest, GetBlock) {
    Block block = blockchain.createBlock();
    blockchain.addBlock(block);
    Block retrievedBlock = blockchain.getBlock(0);
    ASSERT_TRUE(retrievedBlock.isValid());
}
