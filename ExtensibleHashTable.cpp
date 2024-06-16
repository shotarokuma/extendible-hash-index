#include "ExtensibleHashTable.h"

ExtensibleHashTable::ExtensibleHashTable() 
    : globalDepth(1), directory(2) {
      directory[0] = Bucket(INIT_DEPTH, DEFAULT_BUCKET_SIZE, 0)
      directory[1] = Bucket(INIT_DEPTH, DEFAULT_BUCKET_SIZE, 1)
}

ExtensibleHashTable::ExtensibleHashTable(int bucketSize) : globalDepth(1), directory(2) {
  directory[0] = Bucket(INIT_DEPTH, bucketSize, 0)
  directory[1] = Bucket(INIT_DEPTH, bucketSize, 1)
}

int ExtensibleHashTable::hash(int key, int depth) const {
  int mask = ( 1 << depth ) - 1;
  return key & mask;
}


void ExtensibleHashTable::doubleDirectory() {
    int bucketSize = directory[0].size;
    int oldSize = directory.size();
    directory.resize(directory.size() * 2);
    for(int i = oldSize; i < directory.size(); i++){
      directory[i] = Bucket(globalDepth, bucketSize, i);
    }
    globalDepth += 1;
}

void ExtensibleHashTable::splitBucket(Bucket& entry) {
   for(int i = 0; i < entry -> currSize; i++){
    int target = entry.keys[i];
    entry.remove(entry.keys[i]);
    while(!insert(target)){
      Bucket overflow;
      int curr = hash(target, globalDepth);
      for(int i = 0; i < directory.size(); i++){
        if(directory[i].index == curr){
          overflow = directory[i]
        }
      }
      doubleDirectory();
      splitBucket(overflow);
    }
   }
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

bool ExtensibleHashTable::find(int key) const {
   int depth = globalDepth;
   while(depth >  0){
     int curr = hash(key, depth);
     for (const Bucket& entry : directory) {
        if(curr == entry.index){
          if(depth ==  entry.localDepth){
            return entry.find(key);
          }else{
            int mask = (1 << entry.localDepth) - 1;
            depth = depth & mask;
            continue;
          }
        }
     }
    depth -= 1;
   }
  return false;
}

void ExtensibleHashTable::insert(int key) {
   int depth = globalDepth;
   while(depth > 0){
     int curr = hash(key, depth);
     for (const Bucket& entry : directory) {
        if(curr == entry.index){
          if(depth ==  entry.localDepth){
           while(entry.insert(key)){
              doubleDirectory();
              splitBucket(entry);
           }
           break;
          }else{
            int mask = (1 << entry.localDepth) - 1;
            depth = depth & mask;
            continue;
          }
        }
     }
    depth -= 1;
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
    for (int i = 0; i < directory.size(); i++) {
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
