#include "ExtensibleHashTable.h"
#include <algorithm>
#include <stdexcept>

ExtensibleHashTable::ExtensibleHashTable() : ExtensibleHashTable(4) {}

ExtensibleHashTable::ExtensibleHashTable(int bucketSize) : bucketSize(bucketSize), globalDepth(1) {
    directory.resize(2, std::make_shared<Bucket>(1));
}

ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable& other)
    : globalDepth(other.globalDepth), bucketSize(other.bucketSize) {
    directory.resize(other.directory.size());
    for (size_t i = 0; i < other.directory.size(); ++i) {
        directory[i] = std::make_shared<Bucket>(*other.directory[i]);
    }
}

ExtensibleHashTable& ExtensibleHashTable::operator=(const ExtensibleHashTable& other) {
    if (this != &other) {
        globalDepth = other.globalDepth;
        bucketSize = other.bucketSize;
        directory.resize(other.directory.size());
        for (size_t i = 0; i < other.directory.size(); ++i) {
            directory[i] = std::make_shared<Bucket>(*other.directory[i]);
        }
    }
    return *this;
}

ExtensibleHashTable::~ExtensibleHashTable() {}

int ExtensibleHashTable::hash(int key) const {
    return key & ((1 << globalDepth) - 1);
}

void ExtensibleHashTable::splitBucket(int index) {
    auto oldBucket = directory[index];
    int localDepth = oldBucket->localDepth;
    if (localDepth == globalDepth) {
        doubleDirectory();
    }
    
    int newLocalDepth = localDepth + 1;
    auto newBucket = std::make_shared<Bucket>(newLocalDepth);
    auto newBucketIndex = index ^ (1 << localDepth);

    directory[newBucketIndex] = newBucket;
    oldBucket->localDepth = newLocalDepth;

    auto keysToRehash = oldBucket->keys;
    oldBucket->keys.clear();

    for (int key : keysToRehash) {
        int newIndex = hash(key);
        directory[newIndex]->keys.push_back(key);
    }

    for (size_t i = 0; i < directory.size(); ++i) {
        if ((i & ((1 << newLocalDepth) - 1)) == newBucketIndex) {
            directory[i] = newBucket;
        }
    }
}

void ExtensibleHashTable::doubleDirectory() {
    size_t newSize = 1 << (globalDepth + 1);
    directory.resize(newSize);
    for (size_t i = 0; i < newSize / 2; ++i) {
        directory[i + newSize / 2] = directory[i];
    }
    globalDepth++;
}

bool ExtensibleHashTable::find(int key) const {
    int index = hash(key);
    auto bucket = directory[index];
    return std::find(bucket->keys.begin(), bucket->keys.end(), key) != bucket->keys.end();
}

void ExtensibleHashTable::insert(int key) {
    int index = hash(key);
    auto bucket = directory[index];

    if (bucket->keys.size() >= bucketSize) {
        splitBucket(index);
        insert(key); // Retry insertion
    } else {
        bucket->keys.push_back(key);
    }
}

bool ExtensibleHashTable::remove(int key) {
    int index = hash(key);
    auto bucket = directory[index];
    auto it = std::remove(bucket->keys.begin(), bucket->keys.end(), key);
    bool found = (it != bucket->keys.end());
    if (found) {
        bucket->keys.erase(it, bucket->keys.end());
    }
    return found;
}

void ExtensibleHashTable::print() const {
    std::cout << "Global Depth: " << globalDepth << std::endl;
    std::vector<bool> printed(directory.size(), false);
    for (size_t i = 0; i < directory.size(); ++i) {
        if (!printed[i]) {
            printed[i] = true;
            std::cout << i << ": " << directory[i].get() << " --> [";
            for (int key : directory[i]->keys) {
                std::cout << key << ",";
            }
            std::cout << "] (" << directory[i]->localDepth << ")" << std::endl;
        } else {
            std::cout << i << ": " << directory[i].get() << std::endl;
        }
    }
}
