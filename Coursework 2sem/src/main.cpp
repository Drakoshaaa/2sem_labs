#include <fstream>

using namespace std;

#include "const.hpp"
#include "defCollector.hpp"
#include "defExchangeModule.hpp"
#include "defParser.hpp"

int main(){    
    ofstream fout(FILEOUT);
    ofstream protocol(PROTOCOL);
    
    Collector mainCol;

    fout << "Курсовая работа за 2 семестр, Решетников Семён, группа 5352\n";
    fout << "Количество предложений на обмен: " << TRADES << endl;
    fout << "______________________________________________________________________________________\n";
    protocol << "Курсовая работа за 2 семестр, Решетников Семён, группа 5352\n";
    protocol << "Количество предложений на обмен: " << TRADES << endl;
    protocol << "______________________________________________________________________________________\n";


    if (!Parser(mainCol, 0, protocol)) {
        fout << "\nПроизошла ошибка при чтении или октрытии файла.";
        protocol << "\nПроизошла ошибка при чтении или октрытии файла.";
        return 0;
    }

    fout << "\n\n                       Коллекция главного филателиста:\n";
    protocol << "\n\n                       Коллекция главного филателиста:\n";
    mainCol.printTable(fout);
    mainCol.printTable(protocol);
    fout << "Полная стоимость всех марок, доступных для обмена: " << mainCol.GetTotalValue() << endl;
    fout << "\n\n\n______________________________________________________________________________________\n\n\n";
    protocol << "Полная стоимость всех марок, доступных для обмена: " << mainCol.GetTotalValue() << endl;
    protocol << "\n\n\n______________________________________________________________________________________\n\n\n";

    // Процесс обмена по очереди с каждым предложением
    for (int i = 1; i <= TRADES; i++){
        Collector offerCol;
        if (!Parser(offerCol, i, protocol)){
            fout << "\nПроизошла ошибка при чтении или октрытии файла обмена №" << i;
            protocol << "\nПроизошла ошибка при чтении или октрытии файла обмена №" << i;
        } 

        fout << "\n\n                       Поступил " << i << " запрос на обмен\n";
        offerCol.printTable(fout);
        fout << "Полная стоимость всех марок, доступных для обмена: " << offerCol.GetTotalValue() << endl;
        protocol << "\n\n                       Поступил " << i << " запрос на обмен\n";
        offerCol.printTable(protocol);
        protocol << "Полная стоимость всех марок, доступных для обмена: " << offerCol.GetTotalValue() << endl;
        
        ExchangeManager exchanger;
        if (exchanger.Process(mainCol, offerCol, fout, protocol)){
            fout << "\n                       Коллекция главного филателиста после обмена:\n";
            mainCol.printTable(fout);
            fout << "Полная стоимость всех марок, доступных для обмена: " << mainCol.GetTotalValue() << endl;
            protocol << "\n                       Коллекция главного филателиста после обмена:\n";
            mainCol.printTable(protocol);
            protocol << "Полная стоимость всех марок, доступных для обмена: " << mainCol.GetTotalValue() << endl;
        }
        else {
            fout << "\nНе было найдено подходящих марок для обмена.\n";
            protocol << "\nНе было найдено подходящих марок для обмена.\n";
        }
        
        fout << "\n\n\n______________________________________________________________________________________\n\n\n";
        protocol << "\n\n\n______________________________________________________________________________________\n\n\n";
    }   
}

