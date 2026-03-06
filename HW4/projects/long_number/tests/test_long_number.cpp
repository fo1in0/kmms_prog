#include <gtest/gtest.h>
#include "long_number.hpp"

using bvs::LongNumber;

TEST(LongNumberTest, Addition) {
    LongNumber a("789");
    LongNumber b("211");
    EXPECT_EQ(a + b, LongNumber("1000"));
}

TEST(LongNumberTest, Subtraction) {
    LongNumber a("1000");
    LongNumber b("567");
    EXPECT_EQ(a - b, LongNumber("433"));
}

TEST(LongNumberTest, Multiplication) {
    LongNumber a("222");
    LongNumber b("333");
    EXPECT_EQ(a * b, LongNumber("73926"));
}

TEST(LongNumberTest, Division) {
    LongNumber a("200");
    LongNumber b("7");
    EXPECT_EQ(a / b, LongNumber("28"));
}

TEST(LongNumberTest, Modulo) {
    LongNumber a("200");
    LongNumber b("7");
    EXPECT_EQ(a % b, LongNumber("4"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}