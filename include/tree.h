#pragma once
#include "polynomial.h"

struct node {
    char name[80];
    polynomial p;
    int h;
    node* left;
    node* right;

    node(const char* str, polynomial _p, node* _left = nullptr, node* _right = nullptr) :left(_left), right(_right), p(_p){
        strncpy(name, str, 80);
        update_height();
    }
    void update_height();
};

class AvlTree {
private:

    int balanceFactor(node* p);

    node* rotateRight(node* p);
    node* rotateLeft(node* q);
    node* balance(node* p);

    node* add(node* p, const char* str, polynomial& pol);
    node* findMin(node* p);
    node* removeMin(node* p);
    node* remove(node* p, const char* str);

    void clear(node* p);

public:
    int op_count = 0;
    node* root=nullptr;
    ~AvlTree();

    void add(const char* str, polynomial& p);
    void remove(const char* str);
    polynomial* find(const char* str);
};
