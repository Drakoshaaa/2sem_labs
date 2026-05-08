#ifndef STRLIST
#define STRLIST

#include <iostream>
#include "const.hpp"

using namespace std;

class StrList {
private: 
    struct StrNode{
        StrNode* next;
        char data[N+1];

        StrNode() : next(nullptr) {}
    };

    StrNode* head;
    unsigned fullsize;
    unsigned listsize;
    unsigned sizeoflast;
public:
    StrList() : head(nullptr), fullsize(0), listsize(0), sizeoflast(0) {}
    ~StrList();
    void clear();

    unsigned CalcStrSize(const char* str);
    void CalcListSize(unsigned size);
    void AddStr(const char* str);
    bool isEqual(const StrList& other);

    void print();

    StrList& operator=(const StrList &other);
};

// -------------------------------------------------------------------------------------

StrList::~StrList() {
    clear();
}

void StrList::clear(){
    StrNode* cur = head;

    while(cur != nullptr){
        StrNode* pre = cur;
        cur = cur->next;

        delete pre;
    }
}

unsigned StrList::CalcStrSize(const char* str){
    int size = 0;

    while (str[size] != '\0') {
        size++;
    }
    return size;
}

void StrList::CalcListSize(unsigned size){
    unsigned blocks = size / N;

    fullsize = size;
    listsize = (size % N) ? (blocks + 1) : (blocks);
    sizeoflast = size - blocks * N;
}

void StrList::AddStr(const char* str){
    unsigned size = CalcStrSize(str);
    CalcListSize(size);
    
    int k = 0;
    for (int i = 1; i <= listsize ; i++){
        StrNode* newstr = new StrNode;
        if (head == nullptr){
            head = newstr;
        }
        else{
            StrNode* cur = head;
            while(cur->next != nullptr){
                cur = cur->next;
            }
        
            cur->next = newstr;
        }

        unsigned realN = N;
        if (i == listsize){
            if (sizeoflast != 0){
                realN = sizeoflast;
            }
        }

        int j = 0;
        for (; j < realN; j++, k++){
            newstr->data[j] = str[k];
        }
        if (j == realN){
            newstr->data[j] = '\0';
        }
    }
}

bool StrList::isEqual(const StrList& other){
    if (fullsize != other.fullsize){
        return false;
    }

    StrNode* cur = head;
    StrNode* othercur = other.head;

    for (int i = 1; i <= listsize ; i++){

        unsigned realN = N;
        if (i == listsize){
            if (sizeoflast != 0){
                realN = sizeoflast;
            }
        }

        for (int j = 0; j < realN; j++){
            if (cur->data[j] != othercur->data[j]) return false;
        }

        cur = cur->next;
        othercur = othercur->next;
    }

    return true;
}

void StrList::print(){
    StrNode* cur = head;

    while(cur != nullptr){
        cout << cur->data;
        cur = cur->next;
    }
}

StrList& StrList::operator=(const StrList &other) {
    if (this == &other) return *this;

    this->clear();

    this->fullsize = other.fullsize;
    this->listsize = other.listsize;
    this->sizeoflast = other.sizeoflast;

    if (other.head == nullptr) {
        this->head = nullptr;
        return *this;
    }

    StrNode* otherCur = other.head;
    StrNode* lastNewNode = nullptr;

    while (otherCur != nullptr) {
        StrNode* newNode = new StrNode;
        
        for (int j = 0; j <= N; j++) {
            newNode->data[j] = otherCur->data[j];
        }
        newNode->next = nullptr;

        if (this->head == nullptr) {
            this->head = newNode;
        } else {
            lastNewNode->next = newNode;
        }
        
        lastNewNode = newNode;
        otherCur = otherCur->next;
    }

    return *this;
}

#endif
