#include "ExtensibleHashTable.h"

ExtensibleHashTable::ExtensibleHashTable()
    : globalDepth(1), directory(2)
{
  directory[0] = new Bucket(INIT_DEPTH, DEFAULT_BUCKET_SIZE, 1);
  directory[1] = new Bucket(INIT_DEPTH, DEFAULT_BUCKET_SIZE, 1);
}

ExtensibleHashTable::ExtensibleHashTable(int bucketSize) : globalDepth(1), directory(2)
{
  directory[0] = new Bucket(INIT_DEPTH, bucketSize, 1);
  directory[1] = new Bucket(INIT_DEPTH, bucketSize, 1);
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
  for (int i = 0; i < bucket->currSize; i++)
  {
    int removed = bucket->keys[i];
    bucket->remove(bucket->keys[i]);
    insert(removed);
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
  for (Bucket *bucket : directory)
  {
    delete bucket;
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
}

void ExtensibleHashTable::insert(int key)
{
  int target = hash(key, globalDepth);
  for (int i = 0; i < directory.size(); i++)
  {
    if (target == i)
    {
      while (!(directory[i]->insert(key)))
      {
        if (directory[i]->localDepth == globalDepth)
        {
          doubleDirectory();
          splitBucket(directory[i]);
        }
        else
        {
          directory[i]->localDepth += 1;
          directory[i + 2 * globalDepth]->insert(key);
        }
      }
      break;
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
  std::vector<bool> printed(directory.size(), false);
  for (int i = 0; i < directory.size(); ++i)
  {
    if (!printed[i])
    {
      printed[i] = true;
      std::cout << i << ": " << directory[i] << " --> [";
      for (int i = 0; i < directory[i]->currSize; i++)
      {
        std::cout << directory[i]->keys[i] << ",";
      }
      std::cout << "] (" << directory[i]->localDepth << ")" << std::endl;
    }
    else
    {
      std::cout << i << ": " << directory[i] << std::endl;
    }
  }
}