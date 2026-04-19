#pragma once
#include <iostream>
#include <cstring>
#include "polynomial.h"

enum row_state {
    EMPTY, FILLED, DELETED
};

struct hash_row {
    char name[80];
    polynomial p;
    row_state state;
    hash_row() {
        state = EMPTY;
    }
    hash_row(const char* _name, polynomial _p,row_state _state) :p(_p),state(_state) {
        strncpy(name, _name, 80);
    }
};

class HashTable {
private:
    hash_row* rows;
    int cap;
    int sz;

    unsigned int hashFunction(const char* str) {
        int x = 2;
        int h = 0;
        op_count++;
        for (int i = 0; i < strlen(str); i++) {
            op_count++;
            h += str[i] * x;
            x *= 2;
        }
        return h;
    }

public:
    int op_count = 0;
    int conf = 0;
    HashTable(int _cap = 100):cap(_cap),sz(0) {
        rows = new hash_row[cap];
    }

    ~HashTable() {
        delete[] rows;
    }

    void add(const char* name, const polynomial& poly) {
        op_count = 1;
        if (sz >= cap / 2) {
            int old_cap = cap;
            hash_row* old_table = rows;
            cap *= 4;
            rows = new hash_row[cap];
            sz = 0;
            op_count++;
            for (int i = 0; i < old_cap; i++) {
                op_count += 2;
                if (old_table[i].state == FILLED) {
                    add(old_table[i].name, old_table[i].p);
                }
            }
            delete[] old_table;
        }
        int i = hashFunction(name) % cap;
        op_count++;
        if (rows[i].state == FILLED)conf++;
        while (i < cap) {
            op_count += 2;
            if (rows[i].state == EMPTY || rows[i].state == DELETED) {
                strncpy(rows[i].name, name, 79);
                rows[i].name[79] = '\0';

                rows[i].p = poly;
                rows[i].state = FILLED;
                sz++;
                return;
            }
            else if (rows[i].state == FILLED) {
                op_count += 2;
                if (strcmp(rows[i].name, name) == 0) {
                    throw"this name already exists";
                }
            }
            i=(i+1)%cap;
        }
    }

    polynomial* find(const char* name) {
        op_count = 0;
        unsigned int i = hashFunction(name) % cap;
        op_count++;
        for(int j=0;j<cap;j++,i++) {
            op_count += 2;
            if (rows[i].state == EMPTY) {
                return nullptr;
            }
            else if (rows[i].state == FILLED) {
                op_count += 2;
                if (strcmp(rows[i].name, name) == 0) {
                    return &(rows[i].p);
                }
            }
            i++;
        }
        return nullptr;
    }

    bool remove(const char* name) {
        op_count = 0;
        unsigned int i = hashFunction(name) % cap;
        op_count++;
        for (int j = 0; j < cap; j++, i++) {
            op_count += 2;
            if (rows[i].state == EMPTY) {
                return false;
            }
            else if (rows[i].state == FILLED) {
                op_count += 2;
                if (strcmp(rows[i].name, name) == 0) {
                    rows[i].state = DELETED;
                    sz--;
                    return true;
                }
            }
            i=(i+1)%cap;
        }
        return false;
    }
    int size() {
        return sz;
    }
};