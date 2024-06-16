#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <vector>
#include <iostream>
#include "Bucket.h"

class ExtensibleHashTable {
private:
    int globalDepth;
    std::vector<Bucket*> directory;

    const int DEFAULT_BUCKET_SIZE = 4;
    const int INIT_DEPTH = 1;

    int hash(int key, int depth) const;
    void splitBucket(Bucket* bucket);
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
