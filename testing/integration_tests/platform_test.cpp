#include <gtest/gtest.h>
#include "blockchain/blockchain.hpp"
#include "ai_engine/ai_engine.hpp"

class PlatformTest : public ::testing::Test {
protected:
    Blockchain blockchain;
    AiEngine aiEngine;

    void SetUp() override {
        blockchain.init();
        aiEngine.init();
    }
};

TEST_F(PlatformTest, CreateBlock) {
    Block block = blockchain.createBlock();
    ASSERT_TRUE(block.isValid());
}

TEST_F(PlatformTest, ProcessTransaction) {
    Transaction transaction = createTransaction();
    aiEngine.processTransaction(transaction);
    ASSERT_TRUE(aiEngine.getTransactionStatus(transaction) == TransactionStatus::PROCESSED);
}
