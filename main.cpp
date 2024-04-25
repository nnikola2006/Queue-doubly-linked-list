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
    }
    ~Queue(){
        while(front != nullptr){
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }
    void enqueue(int data){
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
        // Delete the allocated memory using the temp Node
        delete temp;
        return data;
    }
    int size(){
        return count;
    }
    bool isEmpty(){
        return front == nullptr;
    }

};

int main(){


    return 0;
}