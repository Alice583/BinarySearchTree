#include <iostream>
#include <../lib/BinarySearchTree.h>

int main () {
    BinarySearchTree<int> tree;
    tree.Insert(5);
    tree.Insert(1);
    tree.Insert(2);
    tree.Insert(3);
    auto it = tree.begin<BinarySearchTree<int>::PreOrder>();

    std::cout << *it->key;
    ++it;
    std::cout << *it->key;
    ++it;
    std::cout << *it->key;
    ++it;
    std::cout << *it->key;
    --it;
    std::cout << *it->key;
//    BinarySearchTree<int> bst;
//    bst.Insert(1);
//    bst.Insert(3);
//    bst.Insert(2);
//    bst.Insert(4);
//    bst.Insert(5);
//
//    auto u = bst.begin();
//    std::cout << *u->key << ' ';
//    ++u;
//    std::cout << *u->key << ' ';
//    ++u;
//    std::cout << *u->key << ' ';
//    ++u;
//    std::cout << *u->key << ' ';
//    ++u;
//    std::cout << *u->key << ' ';
//    ++u;
//    ++u;

}