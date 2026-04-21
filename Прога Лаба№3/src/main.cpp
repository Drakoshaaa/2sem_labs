#include <iostream>
#include <fstream>

using namespace std;

#include "const.h"
#include "defStr.h"
#include "defNode.h"
#include "defList.h"


int main() {
    ifstream filein(FILEIN);
    ifstream filetarg(FILETARG);
    ofstream fileout(FILEOUT);
    
    if (!filein.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл " << FILEIN << endl;
        return 0;
    }
    else if (!filetarg.is_open()){
        cerr << "Ошибка: Не удалось открыть файл" << FILETARG << endl;
        return 0;
    }
    
    fileout << "Лабораторная №3 по программированию (второй семестр)\n";
    fileout << "Выполнил Решетников Семён, группа 5352.\n\n";

    // Считаем размер для строки, заданной для удаления и создаём экземпляр Str
    int targetsize = -1;
    while (!filetarg.eof()){
        filetarg.get();
        targetsize++;
    } 
    if (targetsize == 0) {
        cout << "Ошибка: Для удаления задана пустая строка";
        return 0;
    }

    filetarg.clear();
    filetarg.seekg(0);

    Str target(targetsize);
    for (int i=0; i < target.len; i++){
        filetarg.get(target.data[i]);
    }

    filetarg.close();

    fileout << "Требуется удалить первый попавшийся элемент со значением: \"" <<  target.data << "\"\n\n";

    // Создаём список
    List l1;

    // Создаём узлы и заполняем их данными из filein
    l1.LoadFromFile(filein);
    if (l1.is_empty()){
        cout << "Ошибка: Список пуст";
        return 0;
    }

    // Контрольный вывод
    l1.Out(fileout);

    // Запускаем основной алгоритм
    if (l1.Process(target)){
        l1.DeleteEl(fileout);
        l1.Out(fileout);
    }
    else {
        fileout << "\n\n\nПодходящих для удаления элементов не было найдено\n";
    }

    // Удаляем список и все его узлы
    l1.clear();
}

