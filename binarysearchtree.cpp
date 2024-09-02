#include <iostream>
#include <vector>
#include <cstdlib>

const int MAX_SIZE = 40; // Maximum size of the tree array

// Function prototypes
void insert(int, int);
void deleteNode(int);
void display(int);
int search(int);
int searchPosition(int, int);

// Global variables
std::vector<int> tree(MAX_SIZE, -1); // Tree representation using a vector initialized to -1
int elementCount = 1; // Track number of elements in the tree
int searchValue; // Value to search or delete

int main() {
    int choice;
    int value;

    while (true) {
        std::cout << "1. INSERT\n2. DELETE\n3. DISPLAY\n4. SEARCH\n5. EXIT\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the element to insert: ";
            std::cin >> value;
            insert(1, value);
            break;
        case 2:
            std::cout << "Enter the element to delete: ";
            std::cin >> searchValue;
            int deletePosition = search(1);
            if (deletePosition != -1) {
                deleteNode(deletePosition);
            } else {
                std::cout << "No such element in the tree" << std::endl;
            }
            break;
        case 3:
            display(1);
            break;
        case 4:
            std::cout << "Enter the element to search: ";
            std::cin >> searchValue;
            int searchPosition = search(1);
            if (searchPosition == -1) {
                std::cout << "No such element in the tree" << std::endl;
            } else {
                std::cout << searchValue << " is in position " << searchPosition << std::endl;
            }
            break;
        case 5:
            exit(0);
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }

    return 0;
}

// Insert a new element into the tree
void insert(int currentIndex, int value) {
    if (elementCount == 1) {
        tree[elementCount++] = value;
        return;
    }

    int position = searchPosition(currentIndex, value);
    if (tree[position] > value) {
        tree[2 * position] = value;
    } else {
        tree[2 * position + 1] = value;
    }
    elementCount++;
}

// Delete an element from the tree
void deleteNode(int position) {
    if (tree[2 * position] == -1 && tree[2 * position + 1] == -1) {
        tree[position] = -1; // Case 1: Node is a leaf
    } else if (tree[2 * position] == -1) {
        tree[position] = tree[2 * position + 1]; // Case 2: Node has only right child
        tree[2 * position + 1] = -1;
    } else if (tree[2 * position + 1] == -1) {
        tree[position] = tree[2 * position]; // Case 2: Node has only left child
        tree[2 * position] = -1;
    } else {
        tree[position] = tree[2 * position]; // Case 3: Node has two children
        deleteNode(2 * position);
    }
    elementCount--;
}

// Search for an element in the tree
int search(int currentIndex) {
    if (elementCount == 1) {
        std::cout << "No elements in the tree" << std::endl;
        return -1;
    }

    if (tree[currentIndex] == -1) {
        return -1;
    }
    if (tree[currentIndex] > searchValue) {
        return search(2 * currentIndex);
    } else if (tree[currentIndex] < searchValue) {
        return search(2 * currentIndex + 1);
    } else {
        return currentIndex;
    }
}

// Display the tree
void display(int currentIndex) {
    if (elementCount == 1) {
        std::cout << "No elements in the tree" << std::endl;
        return;
    }

    for (int i = 1; i < MAX_SIZE; i++) {
        if (tree[i] == -1) {
            std::cout << " ";
        } else {
            std::cout << tree[i] << " ";
        }
    }
    std::cout << std::endl;
}

// Find the position to insert a new element
int searchPosition(int currentIndex, int value) {
    if (elementCount == 1) {
        std::cout << "No elements in the tree" << std::endl;
        return -1;
    }

    if (tree[currentIndex] == -1) {
        return currentIndex / 2;
    }
    if (tree[currentIndex] > value) {
        return searchPosition(2 * currentIndex, value);
    } else {
        return searchPosition(2 * currentIndex + 1, value);
    }
}
