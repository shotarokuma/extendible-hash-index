#include "ExtensibleHashTable.h"

ExtensibleHashTable::ExtensibleHashTable()
    : globalDepth(1), directory(2)
{
  directory[0] = new Bucket(DEFAULT_BUCKET_SIZE, INIT_DEPTH);
  directory[1] = new Bucket(DEFAULT_BUCKET_SIZE, INIT_DEPTH);
}

ExtensibleHashTable::ExtensibleHashTable(int bucketSize) : globalDepth(1), directory(2)
{
  directory[0] = new Bucket(bucketSize, INIT_DEPTH);
  directory[1] = new Bucket(bucketSize, INIT_DEPTH);
}

int ExtensibleHashTable::hash(int key, int depth) const
{
  int mask = (1 << depth) - 1;
  return key & mask;
}

void ExtensibleHashTable::doubleDirectory()
{
  int bucketSize = directory[0]->size;
  int oldSize = directory.size();
  directory.resize(directory.size() * 2);
  for (int i = 0; i < oldSize; i++)
  {
    directory[i + oldSize] = directory[i];
  }
  globalDepth += 1;
}

void ExtensibleHashTable::splitBucket(Bucket *bucket)
{
  int removeSize = bucket->currSize;
  int *remove = new int[removeSize];
  for (int i = 0; i < removeSize; ++i)
  {
    remove[i] = bucket->keys[i];
  }

  for (int i = 0; i < removeSize; i++)
  {
    bucket->remove(remove[i]);
    insert(remove[i]);
  }
}

ExtensibleHashTable::ExtensibleHashTable(const ExtensibleHashTable &other)
    : globalDepth(other.globalDepth), directory(other.directory.size())
{
  for (int i = 0; i < directory.size(); i++)
  {
    directory[i] = new Bucket(*(other.directory[i]));
  }
}

ExtensibleHashTable &ExtensibleHashTable::operator=(const ExtensibleHashTable &other)
{
  if (this == &other)
  {
    return *this;
  }

  for (Bucket *bucket : directory)
  {
    delete bucket;
  }

  globalDepth = other.globalDepth;
  directory.resize(other.directory.size());
  for (int i = 0; i < other.directory.size(); ++i)
  {
    directory[i] = new Bucket(*(other.directory[i]));
  }

  return *this;
}

ExtensibleHashTable::~ExtensibleHashTable()
{
  for (int i = 0; i < directory.size(); i++)
  {
    if (i < (1 << directory[i]->localDepth))
    {
      delete directory[i];
    }
  }
}

bool ExtensibleHashTable::find(int key) const
{
  int target = hash(key, globalDepth);
  for (int i = 0; i < directory.size(); i++)
  {
    if (target == i)
    {
      return directory[i]->find(key);
    }
  }

  return false;
}

void ExtensibleHashTable::insert(int key)
{
  int target = hash(key, globalDepth);

  while (!(directory[target]->insert(key)))
  {
    if (directory[target]->localDepth == globalDepth)
    {
      doubleDirectory();
      splitBucket(directory[target]);
      target = hash(key, globalDepth);
    }
    else
    {
      Bucket *prev = directory[target];
      directory[target]->localDepth += 1;
      directory[target] = new Bucket(directory[target]->size, directory[target]->localDepth);
      splitBucket(prev);
    }
  }
}

bool ExtensibleHashTable::remove(int key)
{
  int target = hash(key, globalDepth);
  for (int i = 0; i < directory.size(); i++)
  {
    if (target == i)
    {
      directory[i]->remove(key);
      break;
    }
  }
  return false;
}

void ExtensibleHashTable::print() const
{
  std::cout << "Global Depth: " << globalDepth << std::endl;
  for (int i = 0; i < directory.size(); ++i)
  {
    if (directory[i]->currSize == 0)
    {
      std::cout << i << ": " << directory[i] << " --> " << std::endl;
      continue;
    }
    if (i >= 1 << directory[i]->localDepth)
    {
      std::cout << i << ": " << directory[i] << " --> " << std::endl;
      continue;
    }
    std::cout << i << ": " << directory[i] << " --> [";
    for (int j = 0; j < directory[i]->size; j++)
    {
      if (j < directory[i]->currSize)
      {
        std::cout << directory[i]->keys[j];
      }
      else
      {
        std::cout << "-";
      }
      if (j != directory[i]->size - 1)
      {
        std::cout << ",";
      }
    }
    std::cout << "] (" << directory[i]->localDepth << ")" << std::endl;
  }
}