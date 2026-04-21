#include <fstream>

using namespace std;

#include "const.h"
#include "StringList.h"

StringNode* StringList::getHead() const { 
    return head;
}

unsigned StringList::getSize(){
    return size;
}

unsigned StringList::getLastblocklen(){
    return lastblocklen;
}

void StringList::copyFrom(StringList& other) {
    clear(); 
    StringNode* temp = other.getHead();
    while (temp != nullptr) {
        PushBack(); 
        
        // Копируем все N+1 байт (включая возможный \0)
        for (int i = 0; i <= N; i++) {
            cur->string.data[i] = temp->string.data[i];
        }
        
        temp = temp->next;
    }
    // Устанавливаем корректную длину последнего блока из оригинала
    this->lastblocklen = other.getLastblocklen(); 
}

void StringList::PushBack(){
    StringNode* newNode = new StringNode;

    if (!head){
        head = last = newNode;
        pre = nullptr;
        cur = head;
    }
    else {
        last->next = newNode;
        pre = last;
        cur = last = newNode;
    }

    size++;
}

void StringList::AddString(ifstream &file){
    if (file.peek() == '\n'){
        PushBack();
        
        cur->string.data[0] = '\0';
    }       

    while (file.peek() != EOF && file.peek() != '\n'){
        PushBack();

        while (lastblocklen < N && file.peek() != '\n' && file.peek() != EOF){
            file.get(cur->string.data[lastblocklen]);
            lastblocklen++;
        }

        cur->string.data[lastblocklen] = '\0';

        if (lastblocklen == N){
            lastblocklen = 0;
        }
    }

    file.get();
}

void StringList::clear(){
    cur = head;
    while(cur){
        pre = cur;
        cur = cur->next;
        delete pre;
    }
    head = cur = pre = last = nullptr;
    size = 0;
}

void StringList::Print(ofstream &fout){
    cur = head;
    for (int i = 0; i < size; i++){
        fout << cur->string.data;
        if (i < size-1) fout << " -> ";

        pre = cur;
        cur = cur->next;
    }
}

StringList::~StringList(){
    clear();
}