#include <fstream>

using namespace std;

#include "const.h"
#include "StringList.h"
#include "MasterList.h"

unsigned MasterList::getSize(){
    return size;
}

void MasterList::LoadFromFile(ifstream &file){
    while (file.peek() != EOF) {
        PushBack();
        cur->strlist.AddString(file);        
    }
}

void MasterList::PushBack(){
    ListNode* newNode = new ListNode;

    if (!head){
        head = last = cur = newNode;
        pre = nullptr;
    }
    else {
        last->next = newNode;
        pre = last;
        cur = last = newNode;
    }

    size++;
}

bool MasterList::Change(MasterList &search, MasterList &change) {
    if (!head || !search.head) return false;

    bool totalFound = false;
    ListNode* masterScan = head;
    ListNode* prevMaster = nullptr;

    while (masterScan != nullptr) {
        // ПОИСК 
        ListNode* m_temp = masterScan;
        ListNode* s_temp = search.head;
        bool match = true;

        while (s_temp != nullptr) {
            if (m_temp == nullptr) { match = false; break; }

            StringNode* m_str = m_temp->strlist.getHead();
            StringNode* s_str = s_temp->strlist.getHead();

            while (m_str != nullptr && s_str != nullptr) {
                int i = 0;
                while (i < N) {
                    if (m_str->string.data[i] != s_str->string.data[i]) { match = false; break; }
                    if (m_str->string.data[i] == '\0') break; 
                    i++;
                }
                if (!match) break;
                m_str = m_str->next;
                s_str = s_str->next;
            }
            if (match && (m_str != nullptr || s_str != nullptr)) match = false;
            if (!match) break;
            
            m_temp = m_temp->next;
            s_temp = s_temp->next;
        }

        // ЗАМЕНА
        if (match) {
            totalFound = true;
            ListNode* afterMatch = m_temp; 

            // Удаление старых узлов
            while (masterScan != afterMatch) {
                ListNode* toDelete = masterScan;
                masterScan = masterScan->next;
                if (prevMaster == nullptr) head = masterScan;
                else prevMaster->next = masterScan;
                delete toDelete;
                size--;
            }

            // ВСТАВКА НОВЫХ УЗЛОВ
            ListNode* c_scan = change.head;
            ListNode* currentInsertionPos = prevMaster;

            while (c_scan != nullptr) {
                ListNode* newNode = new ListNode();
                
                // теперь копируем с учетом lastblocklen
                newNode->strlist.copyFrom(c_scan->strlist); 

                if (currentInsertionPos == nullptr) {
                    newNode->next = head;
                    head = newNode;
                    currentInsertionPos = head;
                } else {
                    newNode->next = currentInsertionPos->next;
                    currentInsertionPos->next = newNode;
                    currentInsertionPos = newNode;
                }
                size++;
                c_scan = c_scan->next;
            }

            if (currentInsertionPos && currentInsertionPos->next == nullptr) {
                last = currentInsertionPos;
            }

            masterScan = (currentInsertionPos) ? currentInsertionPos->next : head;
            continue; 
        }

        prevMaster = masterScan;
        masterScan = masterScan->next;
    }

    cur = head;
    pre = nullptr;
    return totalFound;
}

void MasterList::clear(){
    cur = head;
    while(cur){
        pre = cur;
        cur = cur->next;
        delete pre;
    }
    head = cur = pre = last = nullptr;
    size = 0;
}

void MasterList::Print(ofstream &fout){
    cur = head;
    for (int i = 0; i < size; i++){
        fout << i << " узел:   ";
        if (cur->strlist.getSize() != 0) cur->strlist.Print(fout);
        if (i < size-1) fout << "\n  ↓\n";

        pre = cur;
        cur = cur->next;
    }
}

bool MasterList::is_empty(){
    if (!head) return true;
    else return false;
}

MasterList::~MasterList(){
    clear();
}