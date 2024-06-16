#ifndef BUCKET_H
#define BUCKET_H

#include <vector>

class Bucket {
public:
    // need to fix
    int localDepth;
    int index;
    int size;
    int currSize;
    int* keys; 

    Bucket(int depth);
    bool find(int key);
    bool insert(int key);
    void remove(int key);
};

#endif // BUCKET_H