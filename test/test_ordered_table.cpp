#include <gtest.h>
#include <cstdio> 
#include "ordered_table.h"
#include "polynomial.h"

TEST(OrderedTest, CreatingEmptyTable) {
    OrderedTable table;
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find("any_name"), nullptr);
}

TEST(OrderedTest, AddAndFindRow) {
    OrderedTable table;
    polynomial p = test_poly();
    table.add("p", p);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("p")->size(), 3);
}

TEST(OrderedTest, FindNonExistingRow) {
    OrderedTable table;
    table.add("p", test_poly());
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(OrderedTest, ModifyRow) {
    OrderedTable table;
    table.add("p", test_poly());

    polynomial* found = table.find("p");
    ASSERT_NE(found, nullptr);

    *(found) += monomial(100, 1);

    polynomial* found_again = table.find("p");
    ASSERT_NE(found_again, nullptr);
    EXPECT_EQ(found_again->size(), 4);
}

TEST(OrderedTest, RemoveRow) {
    OrderedTable table;
    table.add("p1", test_poly());
    table.add("p2", test_poly(2));
    EXPECT_EQ(table.size(), 2);
    bool is_removed = table.remove("p2");
    EXPECT_TRUE(is_removed);
    EXPECT_EQ(table.size(), 1);
    is_removed = table.remove("p2");
    EXPECT_FALSE(is_removed);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("p2"), nullptr);
    ASSERT_NE(table.find("p1"), nullptr);
    EXPECT_EQ(table.find("p1")->size(), 3);
}

TEST(OrderedTest, Resize) {
    OrderedTable table;
    const int poly_num = 20;
    char name[80] ;
    for (int i = 0; i < poly_num; i++) {
        sprintf(name, "p_%d", i);

        int powers[] = { i + 1 };
        double coefs[] = { i * 1.5 + 1 };

        table.add(name, test_poly(i));
    }
    EXPECT_EQ(table.size(), poly_num);
    for (int i = 0; i < poly_num; i++) {
        sprintf(name, "p_%d", i);
        polynomial* found = table.find(name);
        ASSERT_NE(found, nullptr);
        EXPECT_EQ(found->size(), i + 3);
    }
}

TEST(OrderedTest, SearchOfSomeRows) {
    OrderedTable table;
    int p[] = { 1 }; double c[] = { 1.0 };
    polynomial poly(1, p, c);
    table.add("Zeta", poly);
    table.add("Alpha", poly);
    table.add("Gamma", poly);
    table.add("Beta", poly);
    EXPECT_EQ(table.size(), 4);
    EXPECT_NE(table.find("Alpha"), nullptr);
    EXPECT_NE(table.find("Beta"), nullptr);
    EXPECT_NE(table.find("Gamma"), nullptr);
    EXPECT_NE(table.find("Zeta"), nullptr);
}
