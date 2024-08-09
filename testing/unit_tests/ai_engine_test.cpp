#include <gtest/gtest.h>
#include "ai_engine/ai_engine.hpp"

class AiEngineTest : public ::testing::Test {
protected:
    AiEngine aiEngine;

    void SetUp() override {
        aiEngine.init();
    }
};

TEST_F(AiEngineTest, ProcessTransaction) {
    Transaction transaction = createTransaction();
    aiEngine.processTransaction(transaction);
    ASSERT_TRUE(aiEngine.getTransactionStatus(transaction) == TransactionStatus::PROCESSED);
}

TEST_F(AiEngineTest, GetTransactionStatus) {
    Transaction transaction = createTransaction();
    aiEngine.processTransaction(transaction);
    TransactionStatus status = aiEngine.getTransactionStatus(transaction);
    ASSERT_TRUE(status == TransactionStatus::PROCESSED);
}
