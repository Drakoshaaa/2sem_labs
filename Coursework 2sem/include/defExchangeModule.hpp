#ifndef EXCHANGE
#define EXCNAHGE

#include <fstream>

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
    
    bool Process(Collector& mainCol, Collector& offerCol, ofstream &fout, ofstream &protocol);
    void MakePool(Collector& mainCol, Collector& offerCol);
    bool findExchange(int idx, float currentSum);
    void makeExchange(Collector& mainCol, Collector& offerCol, ofstream &out);

    void printFound(ofstream &fout, ofstream &protocol);
};

#endif