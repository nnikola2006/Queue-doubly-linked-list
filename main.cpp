#include <iostream>
#include <stdexcept>
using std::cout, std::cerr, std::cin, std::endl;

struct Node{
    int data;
    Node* next;
    Node* prev;
};

class Queue{
private:
    Node* front;
    Node* rear;
    int count;
public:
    Queue(){
        front = nullptr;
        rear = nullptr;
        count = 0;
    }
    ~Queue(){
        while(front != nullptr){
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(const int data){
        // Creates a newNodeorary new node
        Node* newNode = nullptr;
        try{
            // Tries to allocate memory for a Node
            newNode = new Node{data, nullptr, nullptr};
            // If it's empty it makes both front and rear point to the newNode
            if(isEmpty()){
                front = rear = newNode;
                count++;
            // Otherwise it updates the nodes
            }else{
                rear->next = newNode;
                newNode->prev = rear;
                rear = newNode;
                count++;
            }
        }
        catch(const std::bad_alloc ba){
            cout << "Failed to allocated memory" << endl;
            delete newNode;
        }
    }
    int dequeue(){
        // Checks if the queue is empty
        if(isEmpty()){
            cerr << "Queue is empty!" << endl;
            return -1;
        }
        
        Node* temp = front;
        int data = temp->data;
        // If both front and rear point to the same node then just update both of them to nullptr
        if(front == rear){
            front = rear = nullptr;
        }
        // Otherwise update the front so it points to the next node
        else{
            front = front->next;
            front->prev = nullptr;
        }
        // Deletes the memory allocated in the temp Node
        count--;
        delete temp;
        return data;
    }
    void print(){
        if(isEmpty()){
            cout << "The queue is empty!" << endl;
            return;
        }

        // Prints all the elements of the queue
        cout << "Queue: ";
        Node* temp = rear;
        while(temp != front){
            cout << temp->data << "->";
            temp = temp->prev;
        }
        cout << temp->data << endl;
    }
    void full_print(){
        // Prints everything about the queue
        cout << "All values for a queue:" << endl;
        cout << "Size: " << size() << endl;
        cout << std::boolalpha << "Empty: " << isEmpty() << std::noboolalpha << endl;
        print();
    }
    int peek_front() const{
        return front->data;
    }
    int peek_back() const{
        return rear->data;
    }
    bool isEmpty() const{
        return front == nullptr;
    }
    int size() const{
        return count;
    }
    void fill(const int data, const int len){
        for(int i = 0; i < len; i++){
            enqueue(data);
        }
    }
    void clear(){
        if(isEmpty()){
            return;
        }
        while(count != 0){
            dequeue();
        }
    }
};

int main(){
    Queue queue;

    // Tests
    queue.fill(10, 4);
    queue.dequeue();
    queue.enqueue(51);
    queue.full_print();
    queue.clear();
    
    for(int i = 0; i < 7; i++){
        queue.enqueue(i*i);
    }
    queue.full_print();

    return 0;
}