#include <iostream>
#include <fstream>

using namespace std;

#include "const.h"
#include "BlockCounter.h"
#include "defBlock.h"
#include "defTargetString.h"
#include "defMatchTracker.h"
   

int main() {
    ifstream filein(FILEIN);
    ifstream filesearch(FILESEARCH);
    ofstream fileout(FILEOUT);
    
    cout << "Лабораторная №2 по программированию (второй семестр)\n";
    cout << "Выполнил Решетников Семён, группа 5352.\n\n";
    
    if (!filein.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << FILEIN << endl;
        return 0;
    }
    else if (!filesearch.is_open()){
        cerr << "Ошибка: Не удалось открыть файл" << FILESEARCH << endl;
        return 0;
    }

    Block block;
    TargetString target;
    MatchTracker tracker;

    target.LoadFromFile(filesearch);
    filesearch.close();

    const char* dataTarget = target.GetData();
    fileout << "Подстрока, заданная для поиска - \"";
    for (int i=0; i < target.GetLen(); i++){
        fileout << dataTarget[i];
    }
    fileout << "\"" << endl;

    int numofblocks = BlockCounter(filein);
    fileout << "Количество блоков: " << numofblocks << endl << endl;

    for (int i=0; i < numofblocks; i++){
        block.LoadFromFile(filein);
        // block.debug(fileout);
        tracker.Process(block, target, fileout);
    }

    int total = tracker.GetTotal();
    if (total == 0){
        fileout << endl << "Вхождения не были найдены";
        cout << endl << "Вхождения не были найдены";
    }
    else {
        fileout << endl << "Итого найдено вхождений: " << total;
        cout << endl << "Итого найдено вхождений: " << total;
    }
}