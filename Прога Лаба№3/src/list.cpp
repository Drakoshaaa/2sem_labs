#include <iostream>
#include <fstream>

using namespace std;

#include "defStr.h"
#include "defNode.h"
#include "defList.h"

void List::clear(){
    cur = head;
    while(cur){
        pre = cur;
        cur = cur->next;
        delete pre;
    }
    head = cur = pre = last = nullptr;
    size = 0;
}

bool List::is_empty(){
    if (!head) return true;
    else return false;
}

void List::DeleteEl(ofstream &fileout){
    fileout << "\n\nЭлемент со значением \"" << cur->string.data << "\" был удалён.\n\n";

    if (head == last){
        delete head;
        cur = head = last = nullptr;
    }
    else if (cur == head){
        cur = cur->next;
        delete head;
        head = cur;
    }
    else if (cur == last){
        pre->next = nullptr;
        delete last;
        pre = last;
    }
    else{
        pre->next = cur->next;
        delete cur;
        cur = pre->next;
    }

    size--;
}

void List::LoadFromFile(ifstream &filein){
    while (1){
        while (filein.peek() == '\n') filein.get();
        if (filein.peek() == EOF) break;

        int strsize = CalcStrSize(filein);
        if (strsize == 0 && filein.peek() == EOF) break;

        PushBack(strsize);

        for (int i = 0; i < strsize; i++){
            filein >> noskipws >> last->string.data[i];
        }
    }
}

void List::PushBack(unsigned strsize){
    Node* newNode = new Node(strsize);

    if (!head){
        head = last = newNode;
        pre = nullptr;
        cur = head;
    }
    else {
        last->next = newNode;
        pre = last;
        last = newNode;
    }

    size++;
}

bool List::Process(const Str &target){
    cur = head;
    for (int i=0; i<size; i++){
        if (cur->string.len != target.len){
            pre = cur;
            cur = cur->next;
            continue;
        }

        for (int j=0; j <= cur->string.len ; j++){
            if (j == cur->string.len && cur->string.data[j] == target.data[j]){
                return true;
            }
            if (cur->string.data[j] != target.data[j]){
                break;
            }   
        }

        pre = cur;
        cur = cur->next;
    }

    return false;
}

unsigned List::CalcStrSize(ifstream &filein){
    char ch = 0;
    int pos = filein.tellg();
    unsigned strsize = 0;

    while (filein.get(ch) && ch != '\n'){
        strsize++;
    }  

    filein.clear();
    filein.seekg(pos);

    return strsize;
}

void List::Out(ofstream &fileout){
    cur = head;
    for (int count = 0; count < size; count++){
        fileout <<  "Узел " << count << " --- " << cur->string.data;
        
        if (count < size - 1 ){
            fileout << endl << "           ↓" << endl;
        }

        pre = cur;
        cur = cur->next;
    }
}