#ifndef COLLECTOR
#define COLLECTOR

#include <fstream>

#include "defStrList.hpp"
#include "defMark.hpp"
#include "defTable.hpp"

using namespace std;

struct MarkNode {
    MarkNode* next;
    Mark data;

    MarkNode() : next(nullptr) {}
};

// -----------------------------------------------------------------------------------

class Collector {
private:
    MarkNode* head;
    unsigned size;
public:
    Collector() : head(nullptr), size(0) {}
    ~Collector();
    void clear();

    MarkNode* GetHead();
    float GetTotalValue();
    unsigned GetSize();

    void PushFront();
    void AddMark(const Mark &mark, ofstream &out);
    bool DuplicateCheck(const Mark &mark);
    bool WrongMark(const Mark &mark);
    void DeleteEmpty();

    void printTable(ofstream &out);

    Mark& operator[](const unsigned i);
};

#endif