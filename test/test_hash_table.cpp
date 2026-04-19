#include <gtest.h>
#include <cstring>
#include "hash_table.h"
#include "polynomial.h"

TEST(HashTest, CreatingEmptyTable) {
    HashTable table;
    EXPECT_EQ(table.size(), 0);
    EXPECT_EQ(table.find("any_name"), nullptr);
}

TEST(HashTest, AddAndFindRow) {
    HashTable table;
    polynomial p = test_poly();
    table.add("p", p);
    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("p")->size(), 3);
}

TEST(HashTest, FindNonExistingRow) {
    HashTable table;
    table.add("p", test_poly());
    EXPECT_EQ(table.find("p1"), nullptr);
}

TEST(HashTest, ModifyRow) {
    HashTable table;
    table.add("p", test_poly());

    polynomial* found = table.find("p");
    ASSERT_NE(found, nullptr);

    *(found) += monomial(100, 1);

    polynomial* found_again = table.find("p");
    ASSERT_NE(found_again, nullptr);
    EXPECT_EQ(found_again->size(), 4);
}

TEST(HashTest, RemoveRow) {
    HashTable table;
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

TEST(HashTest, Resize) {
    HashTable table;
    const int poly_num = 20;
    char name[80] = "p_a";
    for (int i = 0; i < poly_num; i++) {
        name[2] = 'a' + i;

        int powers[] = { i + 1 };
        double coefs[] = { i * 1.5 + 1 };

        table.add(name, test_poly(i));
    }
    EXPECT_EQ(table.size(), poly_num);
    for (int i = 0; i < poly_num; i++) {
        name[2] = 'a' + i;
        polynomial* found = table.find(name);
        ASSERT_NE(found, nullptr);
        EXPECT_EQ(found->size(), i + 3);
    }
}