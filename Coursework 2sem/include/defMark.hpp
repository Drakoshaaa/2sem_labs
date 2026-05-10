#ifndef MARK
#define MARK

#include <fstream>

#include "defStrList.hpp"

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

// -----------------------------------------------------------------------------------

void Mark::printMark(ofstream &out){
    char* namestr = name.GetFullStr();
    char* topicstr = topic.GetFullStr();

    out << "|" << left << setw(23) << namestr
        << "|" << setw(23) << topicstr
        << "|" << setw(9) << fixed << setprecision(2) << value
        << "|" << setw(9) << isCancel
        << "|" << setw(6) << amount
        << "|" << setw(9) << isTradeable << "|" << endl;
    
    delete[] namestr; delete[] topicstr;
}

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