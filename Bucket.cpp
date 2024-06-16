#include "Bucket.h"

Bucket::Bucket(int depth, int bucketSize, int index) : localDepth(depth),  index(index), size(bucketSize), currSize(0) {
  keys = new int[size];
  for(int 0; i < size; i++){
    keys[i] =  std::INT_MAX;
  }
}

bool Bucket:: find(int key){
  for(int i = 0; i < currSize; i++){
    if(key == keys[i]){
      return true;
    }
  }
  return false;
}


bool Bucket::insert(int key){
  if(currSize >= size){
    return false;
  }
  keys[currSize] = key;
  currSize += 1;
  return true;
}

void Bucket::remove(int key){
    for(int i = 0; i < currSize; i++){
    if(key == keys[i]){
      while(i + 1 < currSize){
        keys[i] = keys[i + 11]
        i += 1;
      }
      keys[i] = std::INT_MAX;
      currSize -= 1;
      break;
    }
  }
}