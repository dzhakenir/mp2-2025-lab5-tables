#pragma once
#include "polynomial.h"


struct table_row {
    char name[80];
    polynomial p;
    table_row() {}
    table_row(const char* _name, polynomial _p) :p(_p) {
        strncpy(name, _name, 80);
    }
};

class Table {
private:
    table_row* rows;
    int cap;
    int sz=0;

public:
    int op_count = 0;
    Table(int _cap=10) {
        cap = _cap;
        rows = new table_row[cap];
    }

    ~Table() {
        delete[] rows;
    }

    void add(const char* name, const polynomial& poly) {
        op_count = 1;
        if (find(name))throw"this name already exists";
        op_count++;
        if (sz == cap) {
            cap *= 2;
            table_row* new_rows = new table_row[cap];
            op_count++;
            for (int i = 0; i < sz; ++i) {
                op_count++;
                new_rows[i] = rows[i];
            }
            delete[] rows;
            rows = new_rows;
        }
        strncpy(rows[sz].name, name, 80);
        rows[sz].p = poly;
        sz++;
    }

    polynomial* find(const char* name) {
        op_count = 1;
        for (int i = 0; i < sz; i++) {
            op_count += 2;
            if (strcmp(rows[i].name, name) == 0) {
                return &(rows[i].p);
            }
        }
        return nullptr;
    }

    bool remove(const char* name) {
        op_count = 1;
        for (int i = 0; i < sz; ++i) {
            op_count += 2;
            if (strcmp(rows[i].name, name) == 0) {
                op_count++;
                if (i != sz - 1) {
                    rows[i] = rows[sz - 1];
                }
                sz--;
                return true;
            }
        }
        return false;
    }

    int size() const {
        return sz;
    }

};