#include <fstream>
#include <cmath>

#include "defMark.hpp"
#include "defCollector.hpp"
#include "defExchangeModule.hpp"
#include "defTable.hpp"

using namespace std;

ExchangeManager::~ExchangeManager(){
    clearPools();
}

void ExchangeManager::clearPools(){
    delete[] mainPool;
    mainPool = nullptr;

    delete[] offerPool;
    offerPool = nullptr;

    delete[] MatchCounts;
    MatchCounts = nullptr;

    mainPoolSize = 0;
    offerPoolSize = 0;
    targetSum = 0;
}

void ExchangeManager::MakePool(Collector& mainCol, Collector& offerCol){
    // Заполняем основную коллекцию
    for (int i = 0; i < mainCol.GetSize(); i++) {
        if (mainCol[i].isTradeable) mainPoolSize++;
    }

    mainPool = new Mark*[mainPoolSize];

    int idx = 0;
    for (int i = 0; i < mainCol.GetSize(); i++) {
        if (mainCol[i].isTradeable) {
            mainPool[idx++] = &mainCol[i];
        }
    }

    // Заполняем коллекцию для обмена
    for (int i = 0; i < offerCol.GetSize(); i++) {
        if (offerCol[i].isTradeable) offerPoolSize++;
    }

    offerPool = new Mark*[offerPoolSize];

    idx = 0;
    for (int i = 0; i < offerCol.GetSize(); i++) {
        if (offerCol[i].isTradeable) {
            offerPool[idx++] = &offerCol[i];
        }
    }

    MatchCounts = new int[mainPoolSize];
    for (int i = 0; i < mainPoolSize; i++) {
        MatchCounts[i] = 0;
    }

    targetSum = offerCol.GetTotalValue();
}

bool ExchangeManager::Process(Collector& mainCol, Collector& offerCol, ofstream &fout, ofstream &protocol){
    MakePool(mainCol, offerCol);

    if (mainCol.GetTotalValue() < targetSum) return false;

    if (findExchange(0, 0)){
        printFound(fout, protocol);
        makeExchange(mainCol, offerCol, protocol);

        fout << "Обмен марок произошёл успешно.\n";
        protocol << "Обмен марок произошёл успешно.\n";

        return true;
    } else return false;
}

bool ExchangeManager::findExchange(int idx, float currentSum){
    if (abs(targetSum - currentSum) < EPS) return true;

    if (currentSum > targetSum + EPS || idx >= mainPoolSize) return false;

    for (int num = mainPool[idx]->amount ; num >= 0 ; num--){
        MatchCounts[idx] = num;

        float nextSum = currentSum + (mainPool[idx]->value * float(num));

        if (findExchange(idx + 1, nextSum)) return true;
    }

    MatchCounts[idx] = 0;
    return false;
}

void ExchangeManager::makeExchange(Collector& mainCol, Collector& offerCol, ofstream &out){
    for (int i = 0; i < mainPoolSize; i++){
        if (MatchCounts[i] > 0){
            mainPool[i]->amount -= MatchCounts[i];
        }
    }

    mainCol.DeleteEmpty();

    for (int i = 0; i < offerPoolSize; i++){
        out << "\nСледующая марка была отправлена в коллекцию в ходе обмена:\n";
        TableHeader(out);
        offerPool[i]->printMark(out);
        TableBottom(out);
        mainCol.AddMark(*offerPool[i], out);
    }
}

void ExchangeManager::printFound(ofstream &fout, ofstream &protocol){
    fout << "\n\n        В коллекции главного филателиста найдены следующие марки для обмена:\n";
    protocol << "\n\n        В коллекции главного филателиста найдены следующие марки для обмена:\n";
    TableHeader(fout);
    TableHeader(protocol);
    
    for (int i = 0; i < mainPoolSize; i++){
        if (MatchCounts[i] > 0){
            Mark temp;
            temp = *mainPool[i];
            temp.amount = MatchCounts[i];

            temp.printMark(fout);
            temp.printMark(protocol);
        }
    }

    TableBottom(fout);
    TableBottom(protocol);

    fout << endl << endl;
    protocol << endl << endl;
}