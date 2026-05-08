#ifndef EXCHANGE
#define EXCNAHGE

#include <iostream>
#include <cmath>

#include "defMark.hpp"
#include "defCollector.hpp"

using namespace std;

class ExchangeManager {
private:
    Mark** mainPool;
    int mainPoolSize;

    Mark** offerPool;
    int offerPoolSize;

    int* MatchCounts;

    float targetSum;
public:
    ExchangeManager() : mainPool(nullptr), offerPool(nullptr), MatchCounts(nullptr), mainPoolSize(0), offerPoolSize(0), targetSum(0) {}
    ~ExchangeManager();
    void clearPools();
    
    bool Process(Collector& mainCol, Collector& offerCol);
    void MakePool(Collector& mainCol, Collector& offerCol);
    bool findExchange(int idx, float currentSum);
    void makeExchange(Collector& mainCol, Collector& offerCol);
};

// ---------------------------------------------------------------------------

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

    cout << "\nРазмер OfferPool: " << offerPoolSize;
    offerPool = new Mark*[offerPoolSize];

    idx = 0;
    for (int i = 0; i < offerCol.GetSize(); i++) {
        if (offerCol[i].isTradeable) {
            offerPool[idx++] = &offerCol[i];
        }
    }

    MatchCounts = new int[mainPoolSize];

    targetSum = offerCol.GetTotalValue();
}

bool ExchangeManager::Process(Collector& mainCol, Collector& offerCol){
    MakePool(mainCol, offerCol);

    if (mainCol.GetTotalValue() < targetSum) return false;
    
    if (findExchange(0, 0)){
        makeExchange(mainCol, offerCol);
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

void ExchangeManager::makeExchange(Collector& mainCol, Collector& offerCol){
    for (int i = 0; i < mainPoolSize; i++){
        if (MatchCounts[i] > 0){
            mainPool[i]->amount -= MatchCounts[i];
        }
    }
    mainCol.DeleteEmpty();

    for (int i = 0; i < offerPoolSize; i++){
        mainCol.AddMark(*offerPool[i]);
    }
}

#endif