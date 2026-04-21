#include "defStr.h"

Str::Str(unsigned strsize): data(nullptr), len(0) {
    if (strsize > 0){
        data = new char[strsize + 1];
        len = strsize;
        data[strsize] = '\0';
    }
    else {
        data = nullptr;
        len = 0;
    }
}

Str::~Str(){
    delete[] data;
}