#include "../lib/BinarySearchTree.h"
#include <gtest/gtest.h>
#include <cstring>

TEST(InsertTest, insert_test) {
    BinarySearchTree<int> tree;
    tree.Insert(10);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(8);
    auto i1 = *tree.extract(10)->key;
    auto i2 = *tree.extract(8)->key;
    auto i3 = *tree.extract(7)->key;
    auto i4 = *tree.extract(6)->key;
    ASSERT_TRUE(i1 == 10);
    ASSERT_TRUE(i2 == 8);
    ASSERT_TRUE(i3 == 7);
    ASSERT_TRUE(i4 == 6);
}


TEST(PreOrderCheck, PreOrder_check) {
    BinarySearchTree<int> tree;
    tree.Insert(10);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(8);
    auto it = tree.begin<BinarySearchTree<int>::PreOrder>();

    std::cout << *it->key;
    ASSERT_TRUE(*it->key == 10);
    ++it;
    ASSERT_TRUE(*it->key == 6);
    ++it;
    ASSERT_TRUE(*it->key == 7);
    ++it;
    ASSERT_TRUE(*it->key == 8);
    --it;
    ASSERT_TRUE(*it->key == 7);
}

TEST(InOrderCheck, InOrder_check) {
    BinarySearchTree<int> tree;
    tree.Insert(10);
    tree.Insert(6);
    tree.Insert(7);
    tree.Insert(8);
    auto it = tree.begin();

    ASSERT_TRUE(*it->key == 6);
    ++it;
    ASSERT_TRUE(*it->key == 7);
    ++it;
    ASSERT_TRUE(*it->key == 8);
    ++it;
    ASSERT_TRUE(*it->key == 10);
}

TEST(PostorderCheck, Postorder_check) {
    BinarySearchTree<int> tree;
    tree.Insert(10);
    tree.Insert(9);
    tree.Insert(13);
    tree.Insert(11);
    auto it = tree.begin<BinarySearchTree<int>::PostOrder>();
    ASSERT_TRUE(*it->key == 9);
    ++it;
    ASSERT_TRUE(*it->key == 11);
    ++it;
    ASSERT_TRUE(*it->key == 13);
    ++it;
    ASSERT_TRUE(*it->key == 10);
}

