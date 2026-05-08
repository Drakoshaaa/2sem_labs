#ifndef PARSER
#define PARSER

#include <fstream>

#include "const.hpp"
#include "defMark.hpp"
#include "defCollector.hpp"

using namespace std;

int WhichField(const char* buffer);
bool Parser(Collector &col, unsigned num);

// --------------------------------------------------------------------------------

int WhichField(const char* buffer){
    char f_name[] = "Name";             // 1
    char f_topic[] = "Topic";           // 2
    char f_value[] = "Value";           // 3
    char f_amount[] = "Amount";         // 4
    char f_cancel[] = "IsCancelled";    // 5
    char f_tradeable[] = "IsTradeable"; // 6

    if (buffer[0] == f_name[0]){
        for (int i = 0; i < 4; i++){
            if (buffer[i] != f_name[i]) return -1;
        }
        return 1;
    }
    else if (buffer[0] == f_topic[0]){
        for (int i = 0; i < 5; i++){
            if (buffer[i] != f_topic[i]) return -1;
        }
        return 2;
    }
    else if (buffer[0] == f_value[0]){
        for (int i = 0; i < 5; i++){
            if (buffer[i] != f_value[i]) return -1;
        }
        return 3;
    }
    else if (buffer[0] == f_amount[0]){
        for (int i = 0; i < 6; i++){
            if (buffer[i] != f_amount[i]) return -1;
        }
        return 4;
    }
    else if (buffer[0] == f_cancel[0] &&
             buffer[1] == f_cancel[1] &&
             buffer[2] == f_cancel[2]) {
        for (int i = 0; i < 11; i++){
            if (buffer[i] != f_cancel[i]) return -1;
        }
        return 5;
    }
    else if (buffer[0] == f_tradeable[0] &&
             buffer[1] == f_tradeable[1] &&
             buffer[2] == f_tradeable[2]) {
        for (int i = 0; i < 11; i++){
            if (buffer[i] != f_tradeable[i]) return -1;
        }
        return 6;
    }
    else return -1;
}

bool Parser(Collector &col, unsigned num){
    char FileinTemplate[] = "assets/col_00.txt";

    FileinTemplate[11] = (char)((num / 10) + '0'); // Десятки
    FileinTemplate[12] = (char)((num % 10) + '0'); // Единицы

    ifstream filein(FileinTemplate);

    if (!filein.is_open()) return false;
    
    int field, fieldsAmount;
    char ch;
    char buffer[256];
    
    while (filein.get(ch)){
        if (ch == '['){
            while (filein.get(ch) && ch != ']');
            
            Mark mark;
            fieldsAmount = 0;
            // Читаем внутри блока
            while (filein.peek() != '[' && filein.peek() != EOF){
                while (filein.peek() == '\n' || filein.peek() == ' ') {
                    filein.get(ch);                
                }   

                int i = 0;
                while (filein.get(ch) && ch != '=') buffer[i++] = ch;
                buffer[i] = '\0';

                field = WhichField(buffer); 

                if (field == -1) continue;

                i = 0;
                switch (field) {
                case 1:
                    while (filein.get(ch) && ch != '\n') buffer[i++] = ch;
                    buffer[i] = '\0';
                    mark.name.AddStr(buffer);

                    fieldsAmount++;
                    break;
                case 2:
                    while (filein.get(ch) && ch != '\n') buffer[i++] = ch;
                    buffer[i] = '\0';
                    mark.topic.AddStr(buffer);

                    fieldsAmount++;
                    break;
                case 3:
                    float val;
                    filein >> val;
                    mark.value = val;

                    fieldsAmount++;
                    break;
                case 4:
                    unsigned amount;
                    filein >> amount;
                    mark.amount = amount;

                    fieldsAmount++;
                    break;
                case 5:
                    bool isCancel;
                    filein >> isCancel;
                    mark.isCancel = isCancel;

                    fieldsAmount++;
                    break;
                case 6:
                    bool isTrade;
                    filein >> isTrade;
                    mark.isTradeable = isTrade;

                    fieldsAmount++;
                    break;
                default:
                    break;
                }

                if (fieldsAmount == 6) break;
            }

            if (fieldsAmount < 6) continue;
            else col.AddMark(mark);
        }
    }

    return true;
}

#endif