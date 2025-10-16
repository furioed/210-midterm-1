#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20; // Constants are given here

class DoublyLinkedList { // This is where the linked list starts with the class
private: // The node structure used inside this list
    struct Node {
        int data; // Holds the data
        Node* prev; // The pointer to the previous node
        Node* next; // The pointer to the next node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; // Assigns a vertain value to a node
            prev = p; // Prior pointer
            next = n; // Next pointer
        }
    };

    Node* head; // The pointer for the first node in the list
    Node* tail; // The pointer for the last node in the list

public: // Default constructor 
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(int value, int position) { // Inserts a new node after a specific position
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value); // New node is created
        if (!head) {
            head = tail = newNode; // If the list is empty this node will become both the head and the tail
            return;
        }

        Node* temp = head; // A traversal starts at the head
        for (int i = 0; i < position && temp; ++i) // Moves the temp pointer forward a certain amount of times according to the postition
            temp = temp->next;

        if (!temp) { // Message and error for if the position goes further than the list's length
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        // Pointers become reconnected to insert newNode after the temp
        newNode->next = temp->next; // newNode is linked to the node after temp
        newNode->prev = temp; // newNode is then linked back to temp
        if (temp->next) // If temp is not the last node, the previous link should be fixed for the next code
            temp->next->prev = newNode;
        else
            tail = newNode; // Tail should be updated if inserted at the end
        temp->next = newNode; // Temp should now linked to newNode
    }

    void delete_val(int value) { // First node that has a specific value is deleted
        if (!head) return; // If the list is empty it's here

        Node* temp = head; // Starts at the head
        
        while (temp && temp->data != value) // Goes through the list until the end or a value is found
            temp = temp->next;

        if (!temp) return; // If value isn't found, it exits

        if (temp->prev) // Fixes the pointer of the previous node
            temp->prev->next = temp->next;
        else
            head = temp->next; // This deletes the head node

        if (temp->next) // Fixes the pointer of the next node
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; // Deletes the tail node

        delete temp; // Clears unnecessary memory of the deleted node
    }

    void delete_pos(int pos) { // Deletes node by it's position in the list
        if (!head) { // Here if there are no nodes to delete
            cout << "List is empty." << endl; // Error message that the list is empty
            return;
        }
    
        if (pos == 1) { // Deletes the first node
            pop_front();
            return;
        }
    
        Node* temp = head; // Starts from the head
    
        for (int i = 1; i < pos; i++){ // Moves the pointer to the node at a given position
            if (!temp) {
                cout << "Position doesn't exist." << endl; // Error message that the position does not exist
                return;
            }
            else
                temp = temp->next;
        } 
        if (!temp) { // If null, the position is invalud
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) { // If the last node is being deleted, pop_back() should be used
            pop_back();
            return;
        }
        // Re-link certain nodes
        Node* tempPrev = temp->prev; // This is node before the one being deleted
        tempPrev->next = temp->next; // Links the previous node to the next node
        temp->next->prev = tempPrev; // Links the next node back to the previous node
        delete temp; // Then it deletes the target node
    }

    void push_back(int v) {  // New node is added at the end of the list
        Node* newNode = new Node(v); // New node is created with a value of 'v'
        if (!tail) // If the list is empty
            head = tail = newNode; // The new node becomes both the head and the tail
        else {
            tail->next = newNode; // The old tail points forward to the new node
            newNode->prev = tail; // New node points back to the old tail
            tail = newNode; // Tail pointer becomes updated
        }
    }
    
    void push_front(int v) { // Node at the front of the list gets removed
        Node* newNode = new Node(v);
        if (!head) // There is nothing to remove
            head = tail = newNode; // New node is the head and the tail 
        else {
            newNode->next = head; // Connects new node to the old head
            head->prev = newNode; // Connects old head back to the new node
            head = newNode; // Head pointer is updated
        }
    }
    
    void pop_front() { // Node at the front of the list is removed

        if (!head) { // There is nothing to remove
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head; // This stores the node being deleted

        if (head->next) { // If there is more than one node in the list
            head = head->next; // Moves the head forward
            head->prev = nullptr; // New head now has no prior node
        }
        else
            head = tail = nullptr; // List becomes empty
        delete temp; // Deletes the prior head node
    }

    void pop_back() { // At the end of the list node is removed
        if (!tail) { // Nothing to remove here
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail; // Stores the node being deleted

        if (tail->prev) { // If there is more than one node in the list
            tail = tail->prev; // Moves the tail backward
            tail->next = nullptr; // New tail does not have a future node
        }
        else
            head = tail = nullptr; // List becomes empty
        delete temp; // Deletes the prior tail node
    }

    ~DoublyLinkedList() { // The destructor that is called when the list object is destroyed
        while (head) { // Goes through all of the nodes
            Node* temp = head; // It stores the current node
            head = head->next; // It moves the head forward
            delete temp; // Deletes the prior node
        }
    }
    void print() { // Prints all node values from the head to the tail
        Node* current = head;
        if (!current) { // Starts from the head
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Loops until the end of the list
            cout << current->data << " "; // This prints the current node's value
            current = current->next; // Allows it to move forward
        }
        cout << endl;
    }

    void print_reverse() { // Prints all nodes from the tail to the head
        Node* current = tail; // Starts from the tail
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) { // Loops backwards
            cout << current->data << " "; // This prints the current node's value
            current = current->prev; // Allows it to move backward
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}