#include <iostream>

#include "avl.h"

int main() {
    AVLTree T = AVLTree();
    auto l = {2, 1, 5, 4, 6, 3};
    T.build(l);
    AVLNode *a = T.find(5);
    AVLNode *b = T.find(4);
    AVLNode *c = T.find(7);

    std::cout << (T.find(1) ? "True" : "False") << std::endl;
    std::cout << (T.find(2) ? "True" : "False") << std::endl;;
    std::cout << (T.find(3) ? "True" : "False") << std::endl;;
    std::cout << (b->checkchild(a, c) ? "True" : "False") << std::endl;;
    std::cout << a->height() << std::endl; 
    std::cout << b->height() << std::endl; 
}