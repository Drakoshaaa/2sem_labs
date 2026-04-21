#include <fstream>
#include "const.h"

using namespace std;

int BlockCounter(ifstream& filein){
    char ch;
    int len = 0;
    while(filein >> noskipws >> ch){
        if (ch == '\n'){
            len++;
        }
    }

    int blocks = (len/H)*NUMOFBLOCKS;
    if (len % H != 0) blocks+=NUMOFBLOCKS;

    filein.clear();
    filein.seekg(0);
    return blocks;
}