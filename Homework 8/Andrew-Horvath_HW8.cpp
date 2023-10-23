#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
    }

    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    bool deleteValue(int value) {
        if (!head) return false;
        
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            if (!head) tail = nullptr;
            delete temp;
            return true;
        }

        Node* curr = head;
        while (curr->next && curr->next->data != value) {
            curr = curr->next;
        }

        if (curr->next) {
            Node* temp = curr->next;
            curr->next = curr->next->next;
            if (!curr->next) tail = curr;
            delete temp;
            return true;
        }
        return false;
    }

    int search(int value) {
        Node* curr = head;
        int count = 0;
        while (curr) {
            if (curr->data == value) {
                count++;
            }
            curr = curr->next;
        }
        return count;
    }

    void sort() {
        if (!head) return;

        Node* i = head;
        while (i) {
            Node* j = i->next;
            while (j) {
                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
                j = j->next;
            }
            i = i->next;
        }
    }

    void print() {
        Node* curr = head;
        while (curr) {
            cout << curr->data;
            curr = curr->next;
            if (curr == nullptr) break;
            cout << " -> ";
        }
    }
};

int main() {
    LinkedList list;
    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert at beginning\n";
        cout << "2. Insert at end\n";
        cout << "3. Delete value\n";
        cout << "4. Print list\n";
        cout << "5. Search for a value\n";
        cout << "6. Sort the list\n";
        cout << "7. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert at beginning: ";
                cin >> value;
                list.insertAtBeginning(value);
                break;
            case 2:
                cout << "Enter value to insert at end: ";
                cin >> value;
                list.insertAtEnd(value);
                break;
            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                if (!list.deleteValue(value)) {
                    cout << "Value not found in the list.\n";
                }
                break;
            case 4:
                list.print();
                break;
            case 5:
                cout << "Enter value to search for: ";
                cin >> value;
                cout << "Occurrences: " << list.search(value) << endl;
                break;
            case 6:
                list.sort();
                cout << "List sorted.\n";
                break;
            case 7:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
                break;
        }

    } while (choice != 7);

    return 0;
}