#ifndef STRLIST
#define STRLIST

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

    char* GetFullStr();

    StrList& operator=(const StrList &other);
};

#endif
