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
        if (!head) return; 

        Node* temp = head;
        
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; 

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next; 

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev; 

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
    
        if (pos == 1) {
            pop_front();
            return;
        }
    
        Node* temp = head;
    
        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }
    
        if (!temp->next) {
            pop_back();
            return;
        }
    
        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v) {
        Node* newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    
    void push_front(int v) {
        Node* newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) { 
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}