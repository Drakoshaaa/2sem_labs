#ifndef PARSER
#define PARSER

#include <fstream>

#include "defCollector.hpp"

using namespace std;

int WhichField(const char* buffer);
bool Parser(Collector &col, unsigned num, ofstream &out);

#endif