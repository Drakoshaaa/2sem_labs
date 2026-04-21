#ifndef MASTERLIST
#define MASTERLIST

#include <fstream>
#include "StringList.h"

using std::ifstream, std::ofstream;

struct ListNode {
    ListNode *next;
    StringList strlist;

    ListNode(): next(nullptr) {};
};

// ----------------------------------------------------------------------------------------

class MasterList {
    ListNode *head, *cur, *pre , *last;
    unsigned size;
public:
    MasterList(): head(nullptr), cur(nullptr), pre(nullptr), last(nullptr) , size(0) {};
    ~MasterList();
    unsigned getSize();
    void clear();
    bool is_empty();
    void LoadFromFile(ifstream &file);

    void PushBack();

    bool Change(MasterList &search, MasterList &change);
    void Print(ofstream &fout);
};

#endif