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
};

struct MarkNode {
    MarkNode* next;
    Mark data;

    MarkNode() : next(nullptr) {}
};

class Collector {
private:

    MarkNode* head;
    unsigned size;
public:
    Collector() : head(nullptr), size(0) {}
    ~Collector();
    void clear();

    MarkNode* GetHead();

    void PushBack();
    void AddMark(const Mark &mark);
    void DeleteMark(unsigned i);
    
};



#endif