#include "ExtensibleHashTable.h"
#include <iostream>

void testInsert(ExtensibleHashTable& eht, int key) {
    eht.insert(key);
    std::cout << "Inserted " << key << ":\n";
    eht.print();
    std::cout << "\n";
}

void testFind(ExtensibleHashTable& eht, int key) {
    bool found = eht.find(key);
    std::cout << "Find " << key << ": " << (found ? "Found" : "Not Found") << "\n";
}

void testRemove(ExtensibleHashTable& eht, int key) {
    bool removed = eht.remove(key);
    std::cout << "Remove " << key << ": " << (removed ? "Removed" : "Not Found") << "\n";
    eht.print();
    std::cout << "\n";
}

void testEdgeCases(ExtensibleHashTable& eht) {
    std::cout << "Test Remove from Empty Table:\n";
    testRemove(eht, 1); 

    std::cout << "Test Find in Empty Table:\n";
    testFind(eht, 1); 
}

void testMultipleInsertsAndRemovals(ExtensibleHashTable& eht) {
    std::cout << "Test Multiple Inserts and Removals:\n";
    for (int i = 0; i < 20; ++i) {
        testInsert(eht, i);
    }
    for (int i = 0; i < 20; ++i) {
        testRemove(eht, i);
    }
}

void testInsertRemoveEdgeCases(ExtensibleHashTable& eht) {
    std::cout << "Test Insert and Remove Edge Cases:\n";
    testInsert(eht, 42);
    testRemove(eht, 42);
    testInsert(eht, 42);
    testRemove(eht, 42);
    testInsert(eht, 42);
    testRemove(eht, 42);

    testInsert(eht, 100);
    testInsert(eht, 100);
    testInsert(eht, 100);
    testRemove(eht, 100); 

    testRemove(eht, 999);  
}

int main() {
    ExtensibleHashTable eht;

    std::cout << "Initial Insertions:\n";
    testInsert(eht, 64);
    testInsert(eht, 200);
    testInsert(eht, 153);
    testInsert(eht, 66);
    testInsert(eht, 218);
    testInsert(eht, 67);
    testInsert(eht, 13);
    testInsert(eht, 253);
    testInsert(eht, 109);

    std::cout << "Test Find:\n";
    testFind(eht, 64);
    testFind(eht, 200);
    testFind(eht, 153);
    testFind(eht, 300); 

    std::cout << "Test Remove:\n";
    testRemove(eht, 153);
    testFind(eht, 153); 
    testRemove(eht, 300);

    std::cout << "More Insertions:\n";
    testInsert(eht, 5);
    testInsert(eht, 5); 
    testInsert(eht, 5); 
    testInsert(eht, 5); 

    std::cout << "Test Remove Duplicates:\n";
    testRemove(eht, 5); 

    std::cout << "Trigger Further Splits:\n";
    testInsert(eht, 10);
    testInsert(eht, 20);
    testInsert(eht, 30);
    testInsert(eht, 40);
    testInsert(eht, 50);
    testInsert(eht, 60);
    testInsert(eht, 70);
    testInsert(eht, 80);

    std::cout << "Test Edge Cases:\n";
    testEdgeCases(eht);

    testMultipleInsertsAndRemovals(eht);

    testInsertRemoveEdgeCases(eht);

    std::cout << "Final State:\n";
    eht.print();

    return 0;
}
