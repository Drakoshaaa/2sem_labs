#ifndef MATCHTRACKER_H
#define MATCHTRACKER_H

#include <fstream>
#include "const.h"
#include "defBlock.h"
#include "defTargetString.h"

using std::ofstream;

// Хранит индекс начала подстроки относительно файла и количество похожих букв
struct PartionMatch{
    bool found;
    int globalRow;
    int numofsame;
};

// Производит поиск по объекту класса Block и хранит индексы схожих для поиска слов и количество схожих символов
class MatchTracker {
    PartionMatch founds[H];
    int total;
public:
    MatchTracker() : total(0) {}
    int GetTotal();
    int GetGlobalRow(int row, int blockRow);
    void Process(Block& block, TargetString& target, ofstream& fileout);
};

#endif