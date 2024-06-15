#include "ExtensibleHashTable.h"

int main() {
    // Create an ExtensibleHashTable with default bucket size
    ExtensibleHashTable hashTable;

    // Insert some keys
    hashTable.insert(5);
    hashTable.insert(7);
    hashTable.insert(15);
    hashTable.insert(27);
    hashTable.insert(37);
    hashTable.insert(47);

    // Print the hash table
    hashTable.print();

    // Find and remove a key
    int keyToFind = 15;
    std::cout << "Find " << keyToFind << ": " << (hashTable.find(keyToFind) ? "Found" : "Not found") << std::endl;
    std::cout << "Remove " << keyToFind << ": " << (hashTable.remove(keyToFind) ? "Removed" : "Not found") << std::endl;

    // Print the hash table after removal
    hashTable.print();

    return 0;
}