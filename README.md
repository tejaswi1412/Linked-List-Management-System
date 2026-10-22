# Linked List Management System (C++)

## What this project does
This is a menu-driven console program for practising linked lists. It keeps a singly linked list and a doubly linked list and lets the user perform common operations on either one.

## Language and concepts
- C++
- Classes, structures, pointers and dynamic memory (`new` / `delete`)
- Singly and doubly linked lists
- Searching, sorting, reversing and duplicate removal

## Features
Both lists support insertion at the beginning/end/position, insertion before or after a value, deletion from the beginning/end/position, deletion by value, search, update, count, minimum, maximum, middle element, reverse, sort and duplicate removal. The doubly linked list can also be displayed backward.

For lists with an even number of nodes, the middle operation returns the second middle element. When a value appears more than once, operations such as search, update and delete-by-value use the first matching node.

## How to compile and run

### Linux / macOS (g++)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic Main.cpp -o linked_list
./linked_list
```

### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic Main.cpp -o linked_list.exe
linked_list.exe
```

You can also open `Main.cpp` in an IDE such as Code::Blocks or Visual Studio Code with a C++ compiler configured.

## Complexity notes
- Insert at beginning: O(1)
- Insert at end: O(n) for singly list; O(1) for doubly list because it stores a tail pointer
- Search, display, count, minimum/maximum and middle: O(n)
- Reverse: O(n)
- Bubble sort: O(n²)
- Duplicate removal: O(n²)

## Suggested checks
Try an empty list, one-node list, negative and zero values, duplicate values, invalid positions, deleting a value that is not present, sorting, and reversing. `sample-output/output.txt` shows a short example session.

## Project structure
- `Main.cpp` — full program
- `sample-output/output.txt` — example session
