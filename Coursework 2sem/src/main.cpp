#include <iostream>
#include <fstream>

using namespace std;

#include "const.hpp"
#include "defStrList.hpp"
#include "defCollector.hpp"
// #include "defExchangeModule.hpp"
// #include "defParser.hpp"

int main(){

    
    Mark m1;
    m1.name.AddStr("Penny Black", 11);
    m1.topic.AddStr("Queen Victoria", 14);
    m1.value = 250.5;
    m1.amount = 2;
    m1.isCancel = false;
    m1.isTradeable = true;
    
    Mark m2;
    m2.name.AddStr("Penny Blac", 11);
    m2.topic.AddStr("Queen Victoria", 14);
    m2.value = 230.5;
    m2.amount = 1;
    m2.isCancel = false;
    m2.isTradeable = true;

    Mark m3;
    m3.name.AddStr("Penny Black", 11);
    m3.topic.AddStr("Queen Victoria", 14);
    m3.value = 210.5;
    m3.amount = 1;
    m3.isCancel = false;
    m3.isTradeable = true;

    // ----------------------------------------

    Collector Col1;

    Col1.AddMark(m1);
    Col1.AddMark(m2);
    Col1.AddMark(m3);

    Col1.print();

    cout << endl << endl << "Общая стоимость коллекции: " << Col1.GetTotalValue();
    
}

