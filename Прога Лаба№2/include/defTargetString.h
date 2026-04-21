#ifndef TARGETSTRING_H
#define TARGETSTRING_H

#include <fstream>
#include "const.h"

using std::ifstream;

// Хранит строку, заданную для поиска
class TargetString{
    char data[MAX];
    int len;
public:    
    TargetString(): len(0) {}
    int GetLen() const;
    const char* GetData() const;
    void LoadFromFile(ifstream& filesearch);
}; 

#endif