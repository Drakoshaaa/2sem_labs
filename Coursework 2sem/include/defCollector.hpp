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
};


class Collector {
private:
    struct MarkNode {
        MarkNode* next;
        Mark data;

        MarkNode() : next(nullptr) {}
    };

    MarkNode* head;
    unsigned size;
public:
    Collector() : head(nullptr), size(0) {}
};

#endif