#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Transaction.h"
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};


class MockTransaction : public Transaction {
public:
    MOCK_METHOD(bool, Make, (Account& from, Account& to, int sum), ());
    MOCK_METHOD(void, set_fee, (int fee), ());
    MOCK_METHOD(int, fee, (), ());
};


TEST(MockAccount, Getter) {
    MockAccount account(1,10);
    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(10));
    EXPECT_EQ(10, account.GetBalance());
}

TEST(MockAccount, ChangeBalance) {
    MockAccount account(1,10);
    EXPECT_CALL(account, Lock());
    EXPECT_CALL(account, ChangeBalance(5));
    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(15));
    account.Lock();
    account.ChangeBalance(5);
    EXPECT_EQ(15, account.GetBalance());
}

TEST(MockAccount, Lock) {
    MockAccount account(1,10);
    EXPECT_CALL(account, Lock()).Times(2).WillOnce(testing::Return()).WillOnce(testing::Throw(std::runtime_error("Already locked")));
    account.Lock();
    EXPECT_THROW(account.Lock(), std::runtime_error);
}
TEST(MockAccount, Unlock) {
    MockAccount account(1,10);
    EXPECT_CALL(account, Lock());
    EXPECT_CALL(account, ChangeBalance(5));
    EXPECT_CALL(account, Unlock());
    EXPECT_CALL(account, ChangeBalance(-5));
    EXPECT_CALL(account, GetBalance()).WillOnce(testing::Return(10));
    account.Lock();
    account.ChangeBalance(5);
    account.Unlock();
    account.ChangeBalance(-5);
    EXPECT_EQ(10, account.GetBalance());
}






TEST(TransactionTest, Make) {
MockTransaction transaction;
EXPECT_CALL(transaction, set_fee(10));
transaction.set_fee(10);
EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));
EXPECT_EQ(transaction.fee(), 10);
MockAccount from(1, 200);
MockAccount to(2, 100);
EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 100)).WillOnce(testing::Return(true));
EXPECT_TRUE(transaction.Make(from, to, 100));
EXPECT_CALL(from, GetBalance()).WillOnce(testing::Return(100));
EXPECT_EQ(from.GetBalance(), 100);
EXPECT_CALL(to, GetBalance()).WillOnce(testing::Return(200));
EXPECT_EQ(to.GetBalance(), 200);


}

TEST(TransactionTest, MakeException) {
MockTransaction transaction;
MockAccount from(1, 200);
MockAccount to(2, 100);
EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 10)).WillOnce(testing::Throw(std::runtime_error("too small")));
EXPECT_THROW(transaction.Make(from, to, 10), std::runtime_error);
}

TEST(TransactionTest, MakeNot) {
MockTransaction transaction;
MockAccount from(1, 200);
MockAccount to(2, 100);
EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 300)).WillOnce(testing::Return(false));
EXPECT_FALSE(transaction.Make(from, to, 300));
}

TEST(TransactionTest, MakeException2) {
MockTransaction transaction;
MockAccount from(1, 200);
MockAccount to(2, 100);
EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), -100)).WillOnce(testing::Throw(std::runtime_error("sum can't be negative")));
EXPECT_THROW(transaction.Make(from, to, -100), std::runtime_error);
}

TEST(TransactionTest, MakeException3) {
MockTransaction transaction;
MockAccount from(1, 200);
MockAccount to(2, 100);
EXPECT_CALL(transaction, set_fee(10));
transaction.set_fee(10);
EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));
EXPECT_EQ(transaction.fee(), 10);
EXPECT_CALL(transaction, Make(testing::Ref(from), testing::Ref(to), 20)).WillOnce(testing::Return(false));
EXPECT_FALSE(transaction.Make(from, to, 20));
}

TEST(TransactionTest, SetFee) {
MockTransaction transaction;
EXPECT_CALL(transaction, set_fee(10));
transaction.set_fee(10);
}

TEST(TransactionTest, Fee) {
MockTransaction transaction;
EXPECT_CALL(transaction, fee()).WillOnce(testing::Return(10));
EXPECT_EQ(transaction.fee(), 10);
}
