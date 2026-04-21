#ifndef BLOCK_H
#define BLOCK_H

#include <fstream>
#include "const.h"

using std::ifstream;
using std::ofstream;

// Хранит текущий блок данных, а также хранит индекс начала блока относительно исходного файла,
// также хранит позицию данного блока относительно других блоков
class Block{
    char data[H][W];
    int index;
    int blockRow;
    int blockCol;
    int realH;
public:    
    Block() : index(0), blockRow(-1), blockCol(-1), realH(0){}
    const char* GetData() const;
    int GetRow() const;
    int GetCol() const;
    int GetRealH() const;
    void LoadFromFile(ifstream& filein);
    void debug(ofstream& fileout);
}; 

#endif