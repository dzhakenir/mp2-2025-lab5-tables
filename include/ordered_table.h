#pragma once
#include <cstring>
#include "polynomial.h"

struct ordered_row {
    char name[80];
    polynomial p;
    ordered_row() {}
    ordered_row(const char* _name, polynomial _p) :p(_p) {
        strncpy(name, _name, 80);
    }
};

class OrderedTable  {
private:
    ordered_row* rows;
    int cap;
    int sz;

    int binarySearch(const char* str) {
        int l = 0;
        int r = sz;
        op_count++;
        while (l < r) {
            op_count++;
            int mid = l + (r - l) / 2;
            int cmp = strcmp(str, rows[mid].name);
            if (cmp == 0) {
                op_count++;
                return mid;
            }
            else if (cmp < 0) {
                op_count += 2;
                r = mid;
            }
            else {
                op_count += 2;
                l = mid + 1;
            }
        }
        return l;
    }
public:
    int op_count = 0;
    OrderedTable(int _cap = 10): cap(_cap), sz(0) {
        rows = new ordered_row[cap];
    }

    ~OrderedTable() {
        delete[] rows;
    }

    void add(const char* name, const polynomial& poly) {
        op_count = 0;
        int pos = binarySearch(name);
        op_count++;
        if(strcmp(name, rows[pos].name) == 0)throw"this name already exists";
        op_count++;
        if (sz == cap) {
            cap *= 2;
            ordered_row* new_rows = new ordered_row[cap];
            op_count++;
            for (int i = 0; i < sz; ++i) {
                op_count++;
                new_rows[i] = rows[i];
            }
            delete[] rows;
            rows = new_rows;
        }
        op_count++;
        for (int i = sz; i > pos; --i) {
            op_count++;
            rows[i] = rows[i - 1];
        }
        strncpy(rows[pos].name, name, 79);
        rows[pos].name[79] = '\0';
        rows[pos].p = poly;
        ++sz;
    }

    bool remove(const char* name) {
        op_count = 1;
        if (sz == 0)return false;
        int pos = binarySearch(name);
        op_count++;
        if (pos >= sz)return false;
        bool found = (strcmp(name, rows[pos].name) == 0);
        op_count++;
        if (!found) {
            return false;
        }
        op_count++;
        for (int i = pos; i < sz - 1; ++i) {
            op_count++;
            rows[i] = rows[i + 1];
        }
        --sz;
        return true;
    }

    polynomial* find(const char* name) {
        op_count = 1;
        if (sz == 0)return nullptr;
        int pos = binarySearch(name);
        op_count++;
        if (pos >= sz)return nullptr;
        bool found = (strcmp(name, rows[pos].name) == 0);
        op_count++;
        if (found) {
            return &(rows[pos].p);
        }
        return nullptr;
    }

    int size() const {
        return sz;
    }
};