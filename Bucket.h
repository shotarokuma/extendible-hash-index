#ifndef BUCKET_H
#define BUCKET_H

#include <vector>

class Bucket {
public:
    int size;
    int currSize;
    int* keys; 
    int localDepth;

    Bucket(int depth, int size, int localDepth);

    Bucket(const Bucket& other);
    Bucket& operator=(const Bucket& other);
    ~Bucket();

    bool find(int key);
    bool insert(int key);
    void remove(int key);
};

#endif // BUCKET_H