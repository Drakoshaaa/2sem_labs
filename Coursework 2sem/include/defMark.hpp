#ifndef MARK
#define MARK

#include <fstream>

#include "defStrList.hpp"

using namespace std;

struct Mark{
    StrList name;
    StrList topic;
    float value;
    unsigned amount;
    bool isCancel;
    bool isTradeable;

    Mark() : value(0), amount(0), isCancel(false), isTradeable(false) {}

    void printMark(ofstream &out);

    bool operator==(const Mark &mark);
};

#endif