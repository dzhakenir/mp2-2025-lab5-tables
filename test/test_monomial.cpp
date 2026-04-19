#include <gtest.h>
#include <polynomial.h>
#include "polynomial.h"

TEST(MonomialTest, Constructor) {
    monomial m(123, 5);
    EXPECT_EQ(m.power, 123);
    EXPECT_DOUBLE_EQ(m.coef, 5);
    EXPECT_EQ(m.x(), 1);
    EXPECT_EQ(m.y(), 2);
    EXPECT_EQ(m.z(), 3);

    monomial m1(0, 3);
    EXPECT_EQ(m1.power, 0);
    EXPECT_DOUBLE_EQ(m1.coef, 3);
    EXPECT_EQ(m1.x(), 0);
    EXPECT_EQ(m1.y(), 0);
    EXPECT_EQ(m1.z(), 0);
    EXPECT_TRUE(m1==3);
}

TEST(MonomialTest, InvalidPowerThrows) {
    EXPECT_ANY_THROW(monomial(1000, 1));
    EXPECT_ANY_THROW(monomial(-1, 1));
}

TEST(MonomialTest, Comparation) {
    monomial m1(100, 2);
    monomial m2(200, 3);
    monomial m3(100, 5);
    EXPECT_TRUE(m1 < m2);
    EXPECT_TRUE(m2 > m1);
    EXPECT_TRUE(m1 == m3);
}

TEST(MonomialTest, Multiplication) {
    monomial m1(111, 2);
    monomial m2(222, 3);
    monomial m3 = m1 * m2;
    EXPECT_EQ(m3.power, 333);
    EXPECT_DOUBLE_EQ(m3.coef, 6);
}

TEST(MonomialTest, MultiplicationOverflowThrows) {
    monomial m1(500, 1);
    monomial m2(500, 1);
    EXPECT_ANY_THROW(m1 * m2);
}

TEST(MonomialTest, Addition) {
    monomial m1(100, 2);
    monomial m2(100, 3);
    monomial m3 = m1 + m2;
    EXPECT_EQ(m3.power, 100);
    EXPECT_DOUBLE_EQ(m3.coef, 5);
}