#include <iostream>
#include <limits>
using namespace std;

// Each node stores one value and the address of the next node.
struct SNode {
    int data;
    SNode* next;

    SNode(int value) : data(value), next(nullptr) {}
};

class SinglyLinkedList {
private:
    SNode* head;

    SNode* nodeAt(int position) const {
        if (position < 1) return nullptr;
        SNode* current = head;
        for (int i = 1; current != nullptr && i < position; ++i)
            current = current->next;
        return current;
    }

public:
    SinglyLinkedList() : head(nullptr) {}
    ~SinglyLinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            SNode* oldHead = head;
            head = head->next;
            delete oldHead;
        }
    }

    bool isEmpty() const { return head == nullptr; }

    void insertBeginning(int value) {
        SNode* node = new SNode(value);
        node->next = head;
        head = node;
        cout << "Inserted " << value << " at the beginning.\n";
    }

    void insertEnd(int value) {
        SNode* node = new SNode(value);
        if (head == nullptr) {
            head = node;
        } else {
            SNode* current = head;
            while (current->next != nullptr) current = current->next;
            current->next = node;
        }
        cout << "Inserted " << value << " at the end.\n";
    }

    void insertPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position. Use a position starting from 1.\n";
            return;
        }
        if (position == 1) {
            insertBeginning(value);
            return;
        }
        SNode* previous = nodeAt(position - 1);
        if (previous == nullptr) {
            cout << "Position is out of range.\n";
            return;
        }
        SNode* node = new SNode(value);
        node->next = previous->next;
        previous->next = node;
        cout << "Inserted " << value << " at position " << position << ".\n";
    }

    void insertAfter(int target, int value) {
        SNode* current = head;
        while (current != nullptr && current->data != target)
            current = current->next;
        if (current == nullptr) {
            cout << target << " was not found.\n";
            return;
        }
        SNode* node = new SNode(value);
        node->next = current->next;
        current->next = node;
        cout << "Inserted " << value << " after " << target << ".\n";
    }

    void insertBefore(int target, int value) {
        if (head == nullptr) {
            cout << "The list is empty.\n";
            return;
        }
        if (head->data == target) {
            insertBeginning(value);
            return;
        }
        SNode* previous = head;
        SNode* current = head->next;
        while (current != nullptr && current->data != target) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << target << " was not found.\n";
            return;
        }
        SNode* node = new SNode(value);
        node->next = current;
        previous->next = node;
        cout << "Inserted " << value << " before " << target << ".\n";
    }

    void deleteBeginning() {
        if (head == nullptr) {
            cout << "The list is empty; nothing to delete.\n";
            return;
        }
        SNode* oldHead = head;
        head = head->next;
        cout << "Deleted " << oldHead->data << " from the beginning.\n";
        delete oldHead;
    }

    void deleteEnd() {
        if (head == nullptr) {
            cout << "The list is empty; nothing to delete.\n";
            return;
        }
        if (head->next == nullptr) {
            deleteBeginning();
            return;
        }
        SNode* current = head;
        while (current->next->next != nullptr) current = current->next;
        cout << "Deleted " << current->next->data << " from the end.\n";
        delete current->next;
        current->next = nullptr;
    }

    void deletePosition(int position) {
        if (position < 1 || head == nullptr) {
            cout << "Invalid position or empty list.\n";
            return;
        }
        if (position == 1) {
            deleteBeginning();
            return;
        }
        SNode* previous = nodeAt(position - 1);
        if (previous == nullptr || previous->next == nullptr) {
            cout << "Position is out of range.\n";
            return;
        }
        SNode* victim = previous->next;
        previous->next = victim->next;
        cout << "Deleted " << victim->data << " from position " << position << ".\n";
        delete victim;
    }

    void deleteValue(int value) {
        if (head == nullptr) {
            cout << "The list is empty; nothing to delete.\n";
            return;
        }
        if (head->data == value) {
            deleteBeginning();
            return;
        }
        SNode* previous = head;
        SNode* current = head->next;
        while (current != nullptr && current->data != value) {
            previous = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << value << " was not found.\n";
            return;
        }
        previous->next = current->next;
        delete current;
        cout << "Deleted the first occurrence of " << value << ".\n";
    }

    int search(int value) const {
        SNode* current = head;
        int position = 1;
        while (current != nullptr) {
            if (current->data == value) return position;
            current = current->next;
            ++position;
        }
        return -1;
    }

    void update(int oldValue, int newValue) {
        SNode* current = head;
        while (current != nullptr && current->data != oldValue)
            current = current->next;
        if (current == nullptr) {
            cout << oldValue << " was not found.\n";
            return;
        }
        current->data = newValue;
        cout << "Updated " << oldValue << " to " << newValue << ".\n";
    }

    void display() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        SNode* current = head;
        while (current != nullptr) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL\n";
    }

    int count() const {
        int total = 0;
        for (SNode* current = head; current != nullptr; current = current->next)
            ++total;
        return total;
    }

    void showMinimumMaximum(bool findMaximum) const {
        if (head == nullptr) {
            cout << "The list is empty.\n";
            return;
        }
        int answer = head->data;
        for (SNode* current = head->next; current != nullptr; current = current->next) {
            if ((findMaximum && current->data > answer) ||
                (!findMaximum && current->data < answer))
                answer = current->data;
        }
        cout << (findMaximum ? "Maximum: " : "Minimum: ") << answer << "\n";
    }

    void showMiddle() const {
        if (head == nullptr) {
            cout << "The list is empty.\n";
            return;
        }
        SNode* slow = head;
        SNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Middle element: " << slow->data << "\n";
        // For an even number of nodes, this displays the second middle element.
    }

    void reverse() {
        SNode* previous = nullptr;
        SNode* current = head;
        while (current != nullptr) {
            SNode* nextNode = current->next;
            current->next = previous;
            previous = current;
            current = nextNode;
        }
        head = previous;
        cout << "List reversed.\n";
    }

    void sortAscending() {
        if (head == nullptr || head->next == nullptr) {
            cout << "List sorted.\n";
            return;
        }
        bool swapped;
        do {
            swapped = false;
            SNode* current = head;
            while (current->next != nullptr) {
                if (current->data > current->next->data) {
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "List sorted in ascending order.\n";
    }

    void removeDuplicates() {
        for (SNode* current = head; current != nullptr; current = current->next) {
            SNode* previous = current;
            SNode* runner = current->next;
            while (runner != nullptr) {
                if (runner->data == current->data) {
                    previous->next = runner->next;
                    delete runner;
                    runner = previous->next;
                } else {
                    previous = runner;
                    runner = runner->next;
                }
            }
        }
        cout << "Duplicate values removed.\n";
    }
};

struct DNode {
    int data;
    DNode* prev;
    DNode* next;

    DNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    DNode* head;
    DNode* tail;

    DNode* nodeAt(int position) const {
        if (position < 1) return nullptr;
        DNode* current = head;
        for (int i = 1; current != nullptr && i < position; ++i)
            current = current->next;
        return current;
    }

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList() { clear(); }

    void clear() {
        while (head != nullptr) {
            DNode* oldHead = head;
            head = head->next;
            delete oldHead;
        }
        tail = nullptr;
    }

    void insertBeginning(int value) {
        DNode* node = new DNode(value);
        if (head == nullptr) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        cout << "Inserted " << value << " at the beginning.\n";
    }

    void insertEnd(int value) {
        DNode* node = new DNode(value);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        cout << "Inserted " << value << " at the end.\n";
    }

    void insertPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position. Use a position starting from 1.\n";
            return;
        }
        if (position == 1) {
            insertBeginning(value);
            return;
        }
        DNode* current = nodeAt(position);
        if (current == nullptr) {
            if (position == count() + 1) insertEnd(value);
            else cout << "Position is out of range.\n";
            return;
        }
        DNode* node = new DNode(value);
        DNode* previous = current->prev;
        node->prev = previous;
        node->next = current;
        previous->next = node;
        current->prev = node;
        cout << "Inserted " << value << " at position " << position << ".\n";
    }

    void insertAfter(int target, int value) {
        DNode* current = head;
        while (current != nullptr && current->data != target)
            current = current->next;
        if (current == nullptr) {
            cout << target << " was not found.\n";
            return;
        }
        if (current == tail) {
            insertEnd(value);
            return;
        }
        DNode* node = new DNode(value);
        node->next = current->next;
        node->prev = current;
        current->next->prev = node;
        current->next = node;
        cout << "Inserted " << value << " after " << target << ".\n";
    }

    void insertBefore(int target, int value) {
        DNode* current = head;
        while (current != nullptr && current->data != target)
            current = current->next;
        if (current == nullptr) {
            cout << target << " was not found.\n";
            return;
        }
        if (current == head) {
            insertBeginning(value);
            return;
        }
        DNode* node = new DNode(value);
        node->prev = current->prev;
        node->next = current;
        current->prev->next = node;
        current->prev = node;
        cout << "Inserted " << value << " before " << target << ".\n";
    }

    void deleteBeginning() {
        if (head == nullptr) {
            cout << "The list is empty; nothing to delete.\n";
            return;
        }
        DNode* victim = head;
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
        else tail = nullptr;
        cout << "Deleted " << victim->data << " from the beginning.\n";
        delete victim;
    }

    void deleteEnd() {
        if (tail == nullptr) {
            cout << "The list is empty; nothing to delete.\n";
            return;
        }
        DNode* victim = tail;
        tail = tail->prev;
        if (tail != nullptr) tail->next = nullptr;
        else head = nullptr;
        cout << "Deleted " << victim->data << " from the end.\n";
        delete victim;
    }

    void deletePosition(int position) {
        DNode* victim = nodeAt(position);
        if (victim == nullptr) {
            cout << "Invalid position or empty list.\n";
            return;
        }
        if (victim == head) {
            deleteBeginning();
            return;
        }
        if (victim == tail) {
            deleteEnd();
            return;
        }
        victim->prev->next = victim->next;
        victim->next->prev = victim->prev;
        cout << "Deleted " << victim->data << " from position " << position << ".\n";
        delete victim;
    }

    void deleteValue(int value) {
        DNode* current = head;
        while (current != nullptr && current->data != value)
            current = current->next;
        if (current == nullptr) {
            cout << value << " was not found.\n";
            return;
        }
        if (current == head) {
            deleteBeginning();
            return;
        }
        if (current == tail) {
            deleteEnd();
            return;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        cout << "Deleted the first occurrence of " << value << ".\n";
    }

    int search(int value) const {
        DNode* current = head;
        int position = 1;
        while (current != nullptr) {
            if (current->data == value) return position;
            current = current->next;
            ++position;
        }
        return -1;
    }

    void update(int oldValue, int newValue) {
        DNode* current = head;
        while (current != nullptr && current->data != oldValue)
            current = current->next;
        if (current == nullptr) {
            cout << oldValue << " was not found.\n";
            return;
        }
        current->data = newValue;
        cout << "Updated " << oldValue << " to " << newValue << ".\n";
    }

    void displayForward() const {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        for (DNode* current = head; current != nullptr; current = current->next)
            cout << current->data << " <-> ";
        cout << "NULL\n";
    }

    void displayBackward() const {
        if (tail == nullptr) {
            cout << "List is empty.\n";
            return;
        }
        cout << "NULL";
        for (DNode* current = tail; current != nullptr; current = current->prev)
            cout << " <-> " << current->data;
        cout << "\n";
    }

    int count() const {
        int total = 0;
        for (DNode* current = head; current != nullptr; current = current->next)
            ++total;
        return total;
    }

    void showMinimumMaximum(bool findMaximum) const {
        if (head == nullptr) {
            cout << "The list is empty.\n";
            return;
        }
        int answer = head->data;
        for (DNode* current = head->next; current != nullptr; current = current->next) {
            if ((findMaximum && current->data > answer) ||
                (!findMaximum && current->data < answer))
                answer = current->data;
        }
        cout << (findMaximum ? "Maximum: " : "Minimum: ") << answer << "\n";
    }

    void showMiddle() const {
        if (head == nullptr) {
            cout << "The list is empty.\n";
            return;
        }
        DNode* slow = head;
        DNode* fast = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        cout << "Middle element: " << slow->data << "\n";
        // For an even number of nodes, this displays the second middle element.
    }

    void reverse() {
        DNode* current = head;
        while (current != nullptr) {
            DNode* oldNext = current->next;
            current->next = current->prev;
            current->prev = oldNext;
            current = oldNext;
        }
        DNode* oldHead = head;
        head = tail;
        tail = oldHead;
        cout << "List reversed.\n";
    }

    void sortAscending() {
        if (head == nullptr || head->next == nullptr) {
            cout << "List sorted.\n";
            return;
        }
        bool swapped;
        do {
            swapped = false;
            DNode* current = head;
            while (current->next != nullptr) {
                if (current->data > current->next->data) {
                    int temp = current->data;
                    current->data = current->next->data;
                    current->next->data = temp;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
        cout << "List sorted in ascending order.\n";
    }

    void removeDuplicates() {
        for (DNode* current = head; current != nullptr; current = current->next) {
            DNode* runner = current->next;
            while (runner != nullptr) {
                if (runner->data == current->data) {
                    DNode* duplicate = runner;
                    runner = runner->next;
                    if (duplicate->prev != nullptr)
                        duplicate->prev->next = duplicate->next;
                    if (duplicate->next != nullptr)
                        duplicate->next->prev = duplicate->prev;
                    if (duplicate == tail) tail = duplicate->prev;
                    delete duplicate;
                } else {
                    runner = runner->next;
                }
            }
        }
        cout << "Duplicate values removed.\n";
    }
};

int readInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) return value;
        cout << "Please enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void singlyMenu(SinglyLinkedList& list) {
    int choice;
    do {
        cout << "\n--- Singly Linked List ---\n"
             << "1. Insert at beginning\n2. Insert at end\n3. Insert at position\n"
             << "4. Insert after a value\n5. Insert before a value\n"
             << "6. Delete from beginning\n7. Delete from end\n8. Delete from position\n"
             << "9. Delete by value\n10. Search\n11. Update\n12. Display\n"
             << "13. Count nodes\n14. Find maximum\n15. Find minimum\n"
             << "16. Find middle element\n17. Reverse\n18. Sort\n19. Remove duplicates\n20. Back to main menu\n";
        choice = readInt("Enter choice: ");
        int value, target, position, newValue;
        switch (choice) {
            case 1: value = readInt("Value: "); list.insertBeginning(value); break;
            case 2: value = readInt("Value: "); list.insertEnd(value); break;
            case 3:
                value = readInt("Value: "); position = readInt("Position (starting at 1): ");
                list.insertPosition(value, position); break;
            case 4:
                target = readInt("Insert after which value? "); value = readInt("New value: ");
                list.insertAfter(target, value); break;
            case 5:
                target = readInt("Insert before which value? "); value = readInt("New value: ");
                list.insertBefore(target, value); break;
            case 6: list.deleteBeginning(); break;
            case 7: list.deleteEnd(); break;
            case 8: position = readInt("Position to delete: "); list.deletePosition(position); break;
            case 9: value = readInt("Value to delete: "); list.deleteValue(value); break;
            case 10:
                value = readInt("Value to search: "); position = list.search(value);
                if (position == -1) cout << "Value not found.\n";
                else cout << "Value found at position " << position << ".\n";
                break;
            case 11:
                target = readInt("Existing value: "); newValue = readInt("New value: ");
                list.update(target, newValue); break;
            case 12: list.display(); break;
            case 13: cout << "Number of nodes: " << list.count() << "\n"; break;
            case 14: list.showMinimumMaximum(true); break;
            case 15: list.showMinimumMaximum(false); break;
            case 16: list.showMiddle(); break;
            case 17: list.reverse(); break;
            case 18: list.sortAscending(); break;
            case 19: list.removeDuplicates(); break;
            case 20: break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 20);
}

void doublyMenu(DoublyLinkedList& list) {
    int choice;
    do {
        cout << "\n--- Doubly Linked List ---\n"
             << "1. Insert at beginning\n2. Insert at end\n3. Insert at position\n"
             << "4. Insert after a value\n5. Insert before a value\n"
             << "6. Delete from beginning\n7. Delete from end\n8. Delete from position\n"
             << "9. Delete by value\n10. Search\n11. Update\n12. Display forward\n"
             << "13. Display backward\n14. Count nodes\n15. Find maximum\n"
             << "16. Find minimum\n17. Find middle element\n18. Reverse\n19. Sort\n"
             << "20. Remove duplicates\n21. Back to main menu\n";
        choice = readInt("Enter choice: ");
        int value, target, position, newValue;
        switch (choice) {
            case 1: value = readInt("Value: "); list.insertBeginning(value); break;
            case 2: value = readInt("Value: "); list.insertEnd(value); break;
            case 3:
                value = readInt("Value: "); position = readInt("Position (starting at 1): ");
                list.insertPosition(value, position); break;
            case 4:
                target = readInt("Insert after which value? "); value = readInt("New value: ");
                list.insertAfter(target, value); break;
            case 5:
                target = readInt("Insert before which value? "); value = readInt("New value: ");
                list.insertBefore(target, value); break;
            case 6: list.deleteBeginning(); break;
            case 7: list.deleteEnd(); break;
            case 8: position = readInt("Position to delete: "); list.deletePosition(position); break;
            case 9: value = readInt("Value to delete: "); list.deleteValue(value); break;
            case 10:
                value = readInt("Value to search: "); position = list.search(value);
                if (position == -1) cout << "Value not found.\n";
                else cout << "Value found at position " << position << ".\n";
                break;
            case 11:
                target = readInt("Existing value: "); newValue = readInt("New value: ");
                list.update(target, newValue); break;
            case 12: list.displayForward(); break;
            case 13: list.displayBackward(); break;
            case 14: cout << "Number of nodes: " << list.count() << "\n"; break;
            case 15: list.showMinimumMaximum(true); break;
            case 16: list.showMinimumMaximum(false); break;
            case 17: list.showMiddle(); break;
            case 18: list.reverse(); break;
            case 19: list.sortAscending(); break;
            case 20: list.removeDuplicates(); break;
            case 21: break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 21);
}

void compareLists() {
    cout << "\n--- Singly vs Doubly Linked List ---\n"
         << "Singly linked list: each node stores data and a next pointer.\n"
         << "Doubly linked list: each node stores data, a previous pointer, and a next pointer.\n"
         << "Singly lists use less memory per node and only move forward.\n"
         << "Doubly lists use more memory but support backward traversal.\n"
         << "Searching is O(n) in both. Insertion at the beginning is O(1) in both.\n";
}

int main() {
    SinglyLinkedList singly;
    DoublyLinkedList doubly;
    int choice;

    do {
        cout << "\n====================================\n"
             << "      LINKED LIST MANAGEMENT SYSTEM\n"
             << "====================================\n"
             << "1. Singly linked list\n2. Doubly linked list\n"
             << "3. Compare the two lists\n4. Exit\n";
        choice = readInt("Enter choice: ");

        switch (choice) {
            case 1: singlyMenu(singly); break;
            case 2: doublyMenu(doubly); break;
            case 3: compareLists(); break;
            case 4: cout << "Program closed. Thank you!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
