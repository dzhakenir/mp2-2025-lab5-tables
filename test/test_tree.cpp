#include <gtest.h>
#include "tree.h"



TEST(AvlTreeTest, InsertAndFind) {
    AvlTree tree;
    polynomial p = test_poly();
    tree.add("p", p);
    polynomial* found = tree.find("p");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->size(), 3);
}

TEST(AvlTreeTest, FindNonExistentData) {
    AvlTree tree;
    polynomial p = test_poly();
    tree.add("existing", p);
    EXPECT_NE(tree.find("existing"), nullptr);
    EXPECT_EQ(tree.find("non_existing"), nullptr);
}

TEST(AvlTreeTest, TreeBalancingCheck) {
    AvlTree tree;
    polynomial p = test_poly();
    tree.add("p1", p);
    tree.add("p2", p);
    tree.add("p3", p);
    EXPECT_NE(tree.find("p1"), nullptr);
    EXPECT_NE(tree.find("p2"), nullptr);
    EXPECT_NE(tree.find("p3"), nullptr);
    EXPECT_EQ(strcmp(tree.root->name, "p2"), 0);
}

TEST(AvlTreeTest, RemoveNodeWithData) {
    AvlTree tree;
    polynomial p1 = test_poly();
    polynomial p2= test_poly(1);
    tree.add("p1", p1);
    tree.add("p2", p2);
    tree.remove("p2");
    EXPECT_EQ(tree.find("p2"), nullptr);
    EXPECT_NE(tree.find("p1"), nullptr);
}

TEST(AvlTreeTest, InsertDuplicateName) {
    AvlTree tree;
    polynomial p1 = test_poly(0);
    polynomial p2 = test_poly(2);
    tree.add("p", p1);
    ASSERT_ANY_THROW(tree.add("p", p2));
}