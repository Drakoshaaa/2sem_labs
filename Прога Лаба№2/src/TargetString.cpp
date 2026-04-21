#include <fstream>
#include "defTargetString.h"

using namespace std;

int TargetString::GetLen() const{
    return len;
}
const char* TargetString::GetData() const {
    return &data[0];
}

void TargetString::LoadFromFile(ifstream& filesearch){
    while(!filesearch.eof() && len < MAX){
        data[len] = filesearch.get();
        len++;
    }
    len--;
}
