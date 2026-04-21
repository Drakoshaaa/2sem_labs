#include <iostream>
#include <fstream>

using namespace std;

#include "const.h"
#include "StringList.h"
#include "MasterList.h"


int main(){
    ifstream filein(FILEIN1);
    ifstream fsearch(FILEIN2);
    ifstream fchange(FILEIN3);
    
    if (!filein.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << FILEIN1 << endl;
        return 0;
    }
    else if (!fsearch.is_open()){
        cerr << "Ошибка: Не удалось открыть файл" << FILEIN2 << endl;
        return 0;
    }
    else if (!fchange.is_open()){
        cerr << "Ошибка: Не удалось открыть файл" << FILEIN3 << endl;
        return 0;
    }

    ofstream fout(FILEOUT);
    
    fout << "Лабораторная №4 по программированию (второй семестр)\n";
    fout << "Выполнил Решетников Семён, группа 5352.\n";

    MasterList master, search, change;
    master.LoadFromFile(filein);
    search.LoadFromFile(fsearch);
    change.LoadFromFile(fchange);

    if (master.is_empty()) {
        cerr << "\nОшибка: Файл \"" << FILEIN1 << "\" пуст";
        return 0;
    }
    if (search.is_empty()) {
        cerr << "\nОшибка: Файл \"" << FILEIN2 << "\" пуст";
        return 0;
    }

    fout << "\n--------------------------------------Исходный-список----------------------------------------------\n\n";
    master.Print(fout);

    fout << "\n\n------------------------------------Требуется-найти-следующий-список-----------------------------\n\n";
    search.Print(fout);

    fout << "\n\n------------------------------------И-заменить-на-другой-список----------------------------------\n\n";
    change.Print(fout);

    fout << "\n\n-------------------------------------------------------------------------------------------------\n";
    fout << "                                          Ход работы\n";
    fout << "-------------------------------------------------------------------------------------------------\n\n";
    
    
    if (master.Change(search, change)){
        fout << "\n                      <-----Все подходящие элементы были заменены.----->\n\n";
        master.Print(fout);
    } else {
        fout << "\nНе было найдено подходящих элементов для замены";
    }

    master.clear();
    search.clear();
    change.clear();
}

