#ifndef STRINGLIST
#define STRINGLIST

#include "const.h"
#include <fstream>

using std::ifstream, std::ofstream;


struct Str {
    char data[N+1];
};

// ----------------------------------------------------------------------------------------

struct StringNode {
    StringNode *next;
    Str string;

    StringNode(): next(nullptr) {};
};

// ----------------------------------------------------------------------------------------

class StringList {
    StringNode *head, *cur, *pre , *last;
    unsigned size;
    unsigned lastblocklen;
public:
    StringList(): head(nullptr), cur(nullptr), pre(nullptr), last(nullptr) , size(0), lastblocklen(0) {};
    ~StringList();
    unsigned getSize();
    unsigned getLastblocklen();
    StringNode* getHead() const;

    void copyFrom(StringList& other);
    void AddString(ifstream &file);
    void PushBack();

    void Print(ofstream &fout);
    void clear();

};

#endif