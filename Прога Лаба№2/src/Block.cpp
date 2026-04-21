#include <iostream>
#include <fstream>

#include "defBlock.h"

using namespace std;

const char* Block::GetData() const {
    return &data[0][0];
}
int Block::GetRow() const{
    return blockRow;
}
int Block::GetCol() const{
    return blockCol;
}
int Block::GetRealH() const{
    return realH;
} 

void Block::LoadFromFile(ifstream& filein){
    char ch = 0;
    realH = 0;
    
    //Вычисляем позицию блока относительно других блоков
    blockCol++;
    if (blockCol == NUMOFBLOCKS || blockCol == 0){
        blockCol = 0;
        blockRow++;
    }

    index = (blockRow*NUMOFBLOCKS*W*H) + blockCol*W + blockRow*H;
    
    filein.seekg(index);
    while (realH < H) {
        // Пытаемся прочитать строку до '\n' или конца файла
        bool lineRead = false;
        while (filein.get(ch)) {
            lineRead = true;
            if (ch == '\n') break;
        }
        if (!lineRead) break; // конец файла, больше строк нет
        realH++;
    }

    // Заполняем блок символами
    filein.clear();
    filein.seekg(index);
    for (int row = 0; row < realH; row++){
        for (int col = 0; col < W; col++){
            data[row][col] = filein.get();
        }
        if (row-1 != realH) {filein.seekg(index + (MAX + 1)*(row+1)); }
    }
}

void Block::debug(ofstream& fileout){
    fileout << endl << "realH = " << realH << " ; blockRow = " << blockRow << " ; blockCol = " << blockCol << endl;
    fileout << "--------------------" << endl;
    for (int i = 0; i < realH; i++){
        for (int j = 0; j < W; j++){
            fileout << data[i][j];
        }
        fileout << endl;
    }
    fileout << "--------------------\n\n";
}
