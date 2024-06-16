#include "Bucket.h"

#define INT_MAX 2147483647;

Bucket::Bucket(int depth, int bucketSize, int localDepth) : size(bucketSize), currSize(0), localDepth(localDepth)
{
  keys = new int[size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = INT_MAX;
  }
}

Bucket::Bucket(const Bucket &other) : size(other.size), currSize(other.currSize), localDepth(other.localDepth)
{
  keys = new int[other.size];
  for (int i = 0; i < size; i++)
  {
    keys[i] = other.keys[i];
  }
}

Bucket& Bucket::operator=(const Bucket &other) {
    if (this == &other) {
        return *this; 
    }
    
    delete[] keys; 

    size = other.size;
    currSize = other.currSize;
    localDepth = other.localDepth;

    keys = new int[other.size];
    for (int i = 0; i < size; i++) {
        keys[i] = other.keys[i];
    }

    return *this;
}

Bucket::~Bucket()
{
  delete[] keys;
}

bool Bucket::find(int key)
{
  for (int i = 0; i < currSize; i++)
  {
    if (key == keys[i])
    {
      return true;
    }
  }
  return false;
}

bool Bucket::insert(int key)
{
  if (currSize >= size)
  {
    return false;
  }
  keys[currSize] = key;
  currSize += 1;
  return true;
}

void Bucket::remove(int key)
{
  for (int i = 0; i < currSize; i++)
  {
    if (key == keys[i])
    {
      int j = i;
      for (; j < currSize; j++)
      {
        keys[j] = keys[j + 1];
        j += 1;
      }
      keys[j] = INT_MAX;
      currSize -= 1;
    }
  }
}