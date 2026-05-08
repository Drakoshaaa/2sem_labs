#ifndef COLLECTOR
#define COLLECTOR

#include "defStrList.hpp"
#include "defMark.hpp"


struct MarkNode {
    MarkNode* next;
    Mark data;

    MarkNode() : next(nullptr) {}
};

// -----------------------------------------------------------------------------------

class Collector {
private:
    MarkNode* head;
    unsigned size;
public:
    Collector() : head(nullptr), size(0) {}
    ~Collector();
    void clear();

    MarkNode* GetHead();
    float GetTotalValue();
    unsigned GetSize();

    void PushFront();
    void AddMark(const Mark &mark);
    bool DuplicateCheck(const Mark &mark);
    bool WrongMark(const Mark &mark);
    void DeleteEmpty();

    void print();

    Mark& operator[](const unsigned i);
};

// -----------------------------------------------------------------------------------

Collector::~Collector() {
    clear();
}

void Collector::clear(){
    MarkNode* cur = head;

    while(cur != nullptr){
        MarkNode* pre = cur;

        cur = cur->next;

        delete pre;
    }
}

MarkNode* Collector::GetHead(){
    return head;
}

unsigned Collector::GetSize(){
    return size;
}

float Collector::GetTotalValue(){
    float temp = 0;

    MarkNode* cur = head;
    while(cur != nullptr){
        if (cur->data.isTradeable){
            temp += cur->data.value * cur->data.amount;
        }

        cur = cur->next;
    }

    return temp;
}

void Collector::PushFront(){
    MarkNode* newNode = new MarkNode;
    newNode->next = head;
    head = newNode;
    size++;
}

void Collector::AddMark(const Mark &mark){
    if (!DuplicateCheck(mark)){
        if (!WrongMark(mark)){
            PushFront();
            head->data = mark;
        }
    }
    else {
        MarkNode* cur = head;

        while (cur != nullptr){
            if (cur->data == mark){
                cur->data.amount += mark.amount;
                return;
            }
            
            cur = cur->next;
        }
    }
}

bool Collector::DuplicateCheck(const Mark &mark){
    MarkNode* cur = head;

    while(cur != nullptr){
        if (cur->data == mark) {
            return true;
        } 

        cur = cur->next;
    }

    return false;
}

bool Collector::WrongMark(const Mark &mark){
    MarkNode* cur = head;

    while(cur != nullptr){
        if (cur->data.name.isEqual(mark.name)){
            return true;
        } 

        cur = cur->next;
    }

    return false;
}

void Collector::DeleteEmpty(){
    MarkNode* cur = head;
    MarkNode* prev = nullptr;

    while (cur != nullptr) {
        if (cur->data.amount == 0) {
            MarkNode* toDelete = cur;
            if (prev == nullptr) {
                head = cur->next;
                cur = head;
            } else {
                prev->next = cur->next;
                cur = cur->next;
            }
            delete toDelete;
            size--;
        } else {
            prev = cur;
            cur = cur->next;
        }
    }
}

void Collector::print() {
    MarkNode* cur = head;

    for (int i = 0; cur != nullptr ; i++) {
        cout << "\n\n mark №" << i; 
        cout << "\n---------------------------------";
        cout << "\nname: "; cur->data.name.print();
        cout << "\ntopic: "; cur->data.topic.print();
        cout << "\nvalue: " << cur->data.value
             << "\namount: " << cur->data.amount
             << "\nisCancel: " << cur->data.isCancel
             << "\nisTradeable: " << cur->data.isTradeable;

             cur = cur->next;
    }
}

Mark& Collector::operator[](const unsigned i){
    if (i >= size || i < 0) return head->data;

    MarkNode* cur = head;

    for (int j = 0 ; j < i; j++){
        cur = cur->next;
    }

    return cur->data;
}

#endif