#include <iostream>
#include <fstream>

using namespace std;

#include "const.hpp"
#include "defStrList.hpp"
#include "defCollector.hpp"
#include "defExchangeModule.hpp"
#include "defParser.hpp"

int main(){    
    Collector mainCol;

    if (!Parser(mainCol, 0)) cout << "\nПроизошла ошибка при чтении или октрытии файла.";

    mainCol.print();
    cout << endl << endl << "\nОбщая стоимость коллекции: " << mainCol.GetTotalValue();
    

    for (int i = 1; i <= TRADES; i++){
        Collector offerCol;
        if (!Parser(offerCol, i)) cout << "\nПроизошла ошибка при чтении или октрытии файла №" << i;

        offerCol.print();

        ExchangeManager exchanger;

        if (exchanger.Process(mainCol, offerCol)){
            mainCol.print();
        }
        else {
            cout << "\n Не было найдено подходящих марок для обмена.";
        }
        
    }
    
}

