#include "ExtensibleHashTable.h"
#include <iostream>

int main() {
    ExtensibleHashTable eht = ExtensibleHashTable(2);

    // Inserting elements into the hash table

    eht.insert(61);
    eht.insert(43);
    eht.insert(38);
    eht.insert(218);
    eht.insert(156);
    eht.insert(151);
    eht.insert(123);
    eht.insert(89);
    eht.insert(222);
    eht.insert(4);
    eht.insert(136);
    eht.insert(0);

    eht.insert(27);
    eht.print();

    // Test cases to check if inserted elements are found
    int inserted_elements[] = {43, 0, 38, 222};
    for (int elem : inserted_elements) {
        if (!eht.find(elem)) {
            std::cout << "error: Not found " << elem << std::endl;
        } else {
            std::cout << "Found " << elem << std::endl;
        }
    }

    // Test cases to check if non-inserted elements are not found
    int non_inserted_elements[] = {999, 500, 1};
    for (int elem : non_inserted_elements) {
        if (eht.find(elem)) {
            std::cout << "error: Found " << elem << std::endl;
            exit(1);
        } else {
            std::cout << "Not found " << elem << std::endl;
        }
    }

    // Remove an element and test if it is correctly removed
    eht.remove(38);
    if (eht.find(38)) {
        std::cout << "error: Found 38 after removal" << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully removed 38" << std::endl;
    }

    // Insert the same element multiple times and check if it is found
    for (int i = 0; i < 2; i++) {
        eht.insert(99);
    }
    if (!eht.find(99)) {
        std::cout << "error: Not found 99" << std::endl;
        exit(1);
    } else {
        std::cout << "Found 99" << std::endl;
    }

    // Remove the element and check if it is correctly removed
    eht.remove(99);
    if (eht.find(99)) {
        std::cout << "error: Found 99 after removal" << std::endl;
        exit(1);
    } else {
        std::cout << "Successfully removed 99" << std::endl;
    }


    for (int i = 0; i <3; i++) {
        eht.insert(99);
    }

    return 0;
}
