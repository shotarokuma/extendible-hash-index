#ifndef BUCKET_H
#define BUCKET_H

#include <vector>

class Bucket {
public:
    int localDepth;
    std::vector<int> keys;

    Bucket(int depth);
};

#endif // BUCKET_H