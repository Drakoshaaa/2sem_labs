#ifndef COLLECTOR
#define COLLECTOR

#include "defStrList.hpp"

struct Mark{
    StrList name;
    StrList topic;
    float value;
    unsigned amount;
    bool isCancel;
    bool isTradeable;

    Mark() : value(0), amount(0), isCancel(false), isTradeable(false) {}

    bool operator==(const Mark &mark);
};

// -----------------------------------------------------------------------------------

bool Mark::operator==(const Mark &mark){
    if (name.isEqual(mark.name) && 
        topic.isEqual(mark.topic) &&
        value == mark.value &&
        isCancel == mark.isCancel &&
        isTradeable == mark.isTradeable) 
    {
        return true;
    }
    else return false;
}

// -----------------------------------------------------------------------------------

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

    void PushFront();
    void AddMark(const Mark &mark);
    void DeleteMark(unsigned i);
    bool DuplicateCheck(const Mark &mark);
    bool WrongMark(const Mark &mark);

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

float Collector::GetTotalValue(){
    float temp = 0;

    MarkNode* cur = head;
    while(cur != nullptr){
        temp += cur->data.value * cur->data.amount;

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

void Collector::DeleteMark(unsigned i){
    if (i >= size || i < 0) return;

    MarkNode* pre = nullptr;
    MarkNode* cur = head;

    for (int j = 0 ; j < i; j++){
        pre = cur;
        cur = cur->next;
    }
    pre->next = cur->next;

    delete cur; 
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