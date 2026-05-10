#include <fstream>

#include "defMark.hpp"
#include "defStrList.hpp"
#include "defCollector.hpp"
#include "defTable.hpp"

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

void Collector::AddMark(const Mark &mark, ofstream &out){
    if (!DuplicateCheck(mark)){
        if (!WrongMark(mark)){
            PushFront();
            out << "Марка была успешно добавлена в коллекцию.\n";
            head->data = mark;
            return;
        }
    }
    else {
        MarkNode* cur = head;

        while (cur != nullptr){
            if (cur->data == mark){
                cur->data.amount += mark.amount;
                out << "Марка была успешно добавлена в коллекцию.\n";
                return;
            }
            
            cur = cur->next;
        }
    }

    out << "Марка не была добавлена в коллекцию, т.к. марка с таким названием уже была добавлена с другими полями.\n";
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

void Collector::printTable(ofstream &out) {
    TableHeader(out);

    // Вывод данных из узлов списка
    MarkNode* temp = head;
    while (temp != nullptr) {
        temp->data.printMark(out);

        temp = temp->next;
    }

    TableBottom(out);
}


Mark& Collector::operator[](const unsigned i){
    if (i >= size || i < 0) return head->data;

    MarkNode* cur = head;

    for (int j = 0 ; j < i; j++){
        cur = cur->next;
    }

    return cur->data;
}