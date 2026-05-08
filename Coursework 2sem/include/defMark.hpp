#ifndef MARK
#define MARK

#include "defStrList.hpp"

struct Mark{
    StrList name;
    StrList topic;
    float value;
    unsigned amount;
    bool isCancel;
    bool isTradeable;

    Mark() : value(0), amount(0), isCancel(false), isTradeable(false) {}

    bool operator==(const Mark &mark);
};

// -----------------------------------------------------------------------------------

bool Mark::operator==(const Mark &mark){
    if (name.isEqual(mark.name) && 
        topic.isEqual(mark.topic) &&
        value == mark.value &&
        isCancel == mark.isCancel &&
        isTradeable == mark.isTradeable) 
    {
        return true;
    }
    else return false;
}

#endif