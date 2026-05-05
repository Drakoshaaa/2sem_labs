#include <iostream>
#include <fstream>

using namespace std;

#include "const.hpp"
#include "defStrList.hpp"
// #include "defCollector.hpp"
// #include "defExchangeModule.hpp"
// #include "defParser.hpp"

int main(){
    StrList str1, str2, str3, str4;

    str1.AddStr("MeowMeowMeow", 12);
    str1.print();

    str2.AddStr("MeowMeowMeow", 12);
    str2.print();

    str3.AddStr("MeowMeowMeoq", 12);
    str3.print();

    
}

