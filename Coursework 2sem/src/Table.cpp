#include <fstream>
#include <iomanip>

#include "defTable.hpp"

using namespace std;

void TableHeader(ofstream &out){
    // Рисуем верхнюю границу таблицы
    out << "|" << setfill('-') << setw(23) << "" << "|" << setw(23) << "" << "|" 
        << setw(9) << "" << "|" << setw(9) << "" << "|" << setw(6) << "" << "|" 
        << setw(9) << "" << "|" << setfill(' ') << endl;

    // Заголовки столбцов
    out << "|" << left << setw(23) << "Name" 
        << "|" << setw(23) << "Topic" 
        << "|" << setw(9) << "Value" 
        << "|" << setw(9) << "Cancelled" 
        << "|" << setw(6) << "Amount" 
        << "|" << setw(9) << "Tradeable" << "|" << endl;

    // Разделитель заголовка
    out << "|" << setfill('-') << setw(23) << "" << "|" << setw(23) << "" << "|" 
        << setw(9) << "" << "|" << setw(9) << "" << "|" << setw(6) << "" << "|" 
        << setw(9) << "" << "|" << setfill(' ') << endl;
}

void TableBottom(ofstream &out){
    // Нижняя граница таблицы
    out << "|" << setfill('_') << setw(23) << "" << "|" << setw(23) << "" << "|" 
        << setw(9) << "" << "|" << setw(9) << "" << "|" << setw(6) << "" << "|" 
        << setw(9) << "" << "|" << setfill(' ') << endl;
}