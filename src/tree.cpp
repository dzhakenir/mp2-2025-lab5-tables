#include "tree.h"

int height(node* p) {
    return p ? p->h : 0;
} 

void node::update_height() {
    h = max(height(left), height(right)) + 1;
}


AvlTree::~AvlTree() {
    clear(root);
}

void AvlTree::clear(node* p) {
    op_count++;
    if (p) {
        clear(p->left);
        clear(p->right);
        delete p;
    }
}

int AvlTree::balanceFactor(node* p) {
    return height(p->right) - height(p->left);
}

node* AvlTree::rotateRight(node* p) {
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    p->update_height();
    q->update_height();
    return q;
}

node* AvlTree::rotateLeft(node* q) {
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    p->update_height();
    q->update_height();
    return p;
}

node* AvlTree::balance(node* p) {
    p->update_height();
    op_count++;
    if (balanceFactor(p) == 2) {
        op_count++;
        if (balanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (balanceFactor(p) == -2) {
        op_count++;
        if (balanceFactor(p->left) > 0) {
            op_count++;
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}

node* AvlTree::add(node* p, const char* str, polynomial& pol) {
    op_count = 1;
    if (!p) return new node(str, pol, nullptr, nullptr);

    int cmp = strcmp(str, p->name);
    op_count++;
    if (cmp < 0) {
        p->left = add(p->left, str, pol);
    }
    else if (cmp > 0) {
        op_count++;
        p->right = add(p->right, str, pol);
    }
    else {
        op_count++;
        throw"this name already exists";
    }
    return balance(p);
}

void AvlTree::add(const char* str, polynomial& p) {
    root = add(root, str, p);
}

node* AvlTree::findMin(node* p) {
    op_count++;
    return p->left ? findMin(p->left) : p;
}

node* AvlTree::removeMin(node* p) {
    op_count++;
    if (!p->left) {
        return p->right;
    }
    p->left = removeMin(p->left);
    return balance(p);
}

node* AvlTree::remove(node* p, const char* str) {
    op_count = 1;
    if (!p) return nullptr;

    int cmp = strcmp(str, p->name);
    op_count++;
    if (cmp < 0) {
        p->left = remove(p->left, str);
    }
    else if (cmp > 0) {
        op_count++;
        p->right = remove(p->right, str);
    }
    else {
        node* q = p->left;
        node* r = p->right;
        delete p;
        op_count++;
        if (!r) return q;
        node* min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

void AvlTree::remove(const char* str) {
    root = remove(root, str);
}

polynomial* AvlTree::find(const char* str) {
    op_count = 0;
    node* t = root;
    while (t) {
        op_count++;
        int cmp = strcmp(str, t->name);
        if (cmp < 0)t = t->left;
        else if (cmp > 0)t = t->right;
        else return &(t->p);
    }
    return nullptr;
}