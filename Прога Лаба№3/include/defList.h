#ifndef LIST
#define LIST

using std::ifstream, std::ofstream;

#include "defNode.h"
#include "defStr.h"

class List {
    Node *head, *cur, *pre , *last;
    unsigned size;
public:
    List(): head(nullptr), cur(nullptr), pre(nullptr), last(nullptr) , size(0) {};
    void clear();
    bool is_empty();
    void LoadFromFile(ifstream &filein);
    void Out(ofstream &fileout);
    unsigned CalcStrSize(ifstream &filein);
    void PushBack(unsigned strsize);
    void DeleteEl(ofstream &fileout);
    bool Process(const Str &target);

};

#endif