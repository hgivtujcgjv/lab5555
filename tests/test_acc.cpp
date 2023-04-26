#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "gtest.hpp"


#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "gtest.hpp"


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

