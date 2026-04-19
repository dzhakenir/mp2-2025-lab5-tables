#include <gtest.h>
#include <polynomial.h>
#include "polynomial.h"

TEST(PolynomialTest, DefaultConstructor) {
    polynomial p;
    EXPECT_TRUE(p.is_empty());
}

TEST(PolynomialTest, ArrayConstructor) {
    int powers[] = { 300, 200, 100 };
    double coefs[] = { 1, 2, 3 };
    polynomial p(3, powers, coefs);

    EXPECT_FALSE(p.is_empty());
    EXPECT_EQ(p.size(), 3);
    monomial* t = p.head.next;
    EXPECT_EQ(t->power, 100);
    EXPECT_EQ(t->coef, 3);
    t = t->next;
    EXPECT_EQ(t->power, 200);
    EXPECT_EQ(t->coef, 2);
    t = t->next;
    EXPECT_EQ(t->power, 300);
    EXPECT_EQ(t->coef, 1);
}

TEST(PolynomialTest, CopyConstructor) {
    int powers[] = { 100, 200 };
    double coefs[] = { 1, 2 };
    polynomial p1(2, powers, coefs);
    polynomial p2(p1);
    EXPECT_EQ(p1.size(), p2.size());
    monomial* t = p2.head.next;
    EXPECT_EQ(t->power, 100);
    EXPECT_EQ(t->coef, 1);
    t = t->next;
    EXPECT_EQ(t->power, 200);
    EXPECT_EQ(t->coef, 2);
}

TEST(PolynomialTest, AddMonomial) {
    polynomial p;
    p += monomial(100, 2.0);
    p += monomial(200, 3.0);
    p += monomial(100, 5.0); 
    EXPECT_EQ(p.size(), 2);;
    monomial* t = p.head.next;
    EXPECT_EQ(t->coef, 7);
}

TEST(PolynomialTest, AddMonomialWithCancellation) {
    polynomial p;
    p += monomial(100, 5.0);
    p += monomial(100, -5.0);
    EXPECT_TRUE(p.is_empty());
}

TEST(PolynomialTest, AddPolynomials) {
    int pow_1[] = { 100, 200 };
    double coefs_1[] = { 1, 2 };
    polynomial p1(2, pow_1, coefs_1);
    int pow_2[] = { 200, 300 };
    double coefs_2[] = { 3, 4 };
    polynomial p2(2, pow_2, coefs_2);
    polynomial sum = p1 + p2;
    EXPECT_EQ(sum.size(), 3);

    monomial* t = sum.head.next;
    EXPECT_EQ(t->power, 100);
    EXPECT_EQ(t->coef, 1);
    t = t->next;
    EXPECT_EQ(t->power, 200);
    EXPECT_EQ(t->coef, 5);
    t = t->next;
    EXPECT_EQ(t->power, 300);
    EXPECT_EQ(t->coef, 4);
}

TEST(PolynomialTest, SubtractPolynomials) {
    int powers[] = { 100, 200 };
    double coefs[] = { 5, 5 };
    polynomial p1(2, powers, coefs);
    polynomial p2(2, powers, coefs);
    polynomial diff = p1 - p2;
    EXPECT_TRUE(diff.is_empty());
    int powers1[] = { 200, 300,100};
    double coefs1[] = { 5, 5,2 };
    polynomial p3(3, powers1, coefs1);
    diff = p1 - p3;
    EXPECT_EQ(diff.size(), 2);
    monomial* t = diff.head.next;
    EXPECT_EQ(t->power, 100);
    EXPECT_EQ(t->coef, 3);
    t = t->next;
    EXPECT_EQ(t->power, 300);
    EXPECT_EQ(t->coef, -5);

}

TEST(PolynomialTest, MultiplyByScalar) {
    int powers[] = { 100, 200 };
    double coefs[] = { 2, 3 };
    polynomial p(2, powers, coefs);
    polynomial res = p * 2.0;
    EXPECT_EQ(res.size(), 2);

    monomial* t = res.head.next;
    EXPECT_EQ(t->power, 100);
    EXPECT_EQ(t->coef, 4);
    t = t->next;
    EXPECT_EQ(t->power, 200);
    EXPECT_EQ(t->coef, 6);
    polynomial zero = p * 0.0;
    EXPECT_TRUE(zero.is_empty());
}

TEST(PolynomialTest, MultiplyPolynomials) {
    int powers1[] = { 100, 0 };
    double coefs1[] = { 1, 1 };
    polynomial p1(2, powers1, coefs1);

    int powers2[] = { 100, 0 };
    double coefs2[] = { 1, -1 };
    polynomial p2(2, powers2, coefs2);

    polynomial res = p1 * p2;
    EXPECT_EQ(res.size(), 2);
    monomial* t = res.head.next;
    EXPECT_EQ(t->power, 0);
    EXPECT_EQ(t->coef, -1);
    t = t->next;
    EXPECT_EQ(t->power, 200);
    EXPECT_EQ(t->coef, 1);
}
