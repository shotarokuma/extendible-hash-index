#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <vector>
#include <iostream>
#include "Bucket.h"

class ExtensibleHashTable {
private:
    int globalDepth;
    std::vector<Bucket> directory;

    int DEFAULT_BUCKET_SIZE = 4;
    int INIT_DEPTH = 1;

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
