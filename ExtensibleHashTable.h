#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <vector>
#include <memory>
#include <iostream>
#include "Bucket.h"

class ExtensibleHashTable {
private:
    int globalDepth;
    int bucketSize;
    std::vector<std::shared_ptr<Bucket>> directory;

    int hash(int key) const;
    void splitBucket(int index);
    void doubleDirectory();

public:
    ExtensibleHashTable();
    ExtensibleHashTable(int bucketSize);

    ExtensibleHashTable(const ExtensibleHashTable& other);
    ExtensibleHashTable& operator=(const ExtensibleHashTable& other);
    ~ExtensibleHashTable();

    bool find(int key) const;
    void insert(int key);
    bool remove(int key);
    void print() const;
};

#endif
