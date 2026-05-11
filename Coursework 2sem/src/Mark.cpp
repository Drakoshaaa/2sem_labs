#include <fstream>
#include <iomanip>

#include "defStrList.hpp"
#include "defMark.hpp"

using namespace std;

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