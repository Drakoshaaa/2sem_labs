#include <fstream>
#include "defMatchTracker.h"

using namespace std;

int MatchTracker::GetTotal(){
    return total;
}
int MatchTracker::GetGlobalRow(int row, int blockRow){
    return blockRow * H + row + 1;
}

void MatchTracker::Process(Block& block, TargetString& target, ofstream& fileout) {
    const char* dataBlock = block.GetData();
    const int blockCol = block.GetCol();
    const int blockRow = block.GetRow();
    const int realH = block.GetRealH();
    const char* dataTarget = target.GetData();
    const int targetLen = target.GetLen();

    // При переходе к новому ряду блоков (первый горизонтальный блок) сбрасываем состояние для строк этого блока
    if (blockCol == 0) {
        for (int i = 0; i < realH; i++) {
            founds[i].found = false;
            founds[i].numofsame = 0;
        }
    }

    for (int row = 0; row < realH; row++) {
        for (int col = 0; col < W; col++) {
            char currentChar = dataBlock[row * W + col];

            // Если есть активное частичное совпадение
            if (founds[row].found) {
                // Проверяем, ожидаем ли мы ещё символы
                if (founds[row].numofsame < targetLen) {
                    if (currentChar == dataTarget[founds[row].numofsame]) {
                        // Продолжаем совпадение
                        founds[row].numofsame++;
                        if (founds[row].numofsame == targetLen) {
                            total++;
                            fileout << "Заданная подстрока найдена в строке номер " << GetGlobalRow(row, blockRow) << endl;
                            // Сбрасываем текущее совпадение
                            founds[row].found = false;
                            founds[row].numofsame = 0;
                            // Проверяем, не начинается ли новое совпадение с этого же символа
                            if (currentChar == dataTarget[0]) {
                                founds[row].found = true;
                                founds[row].numofsame = 1;
                            }
                        }
                    } else {
                        // Совпадение прервалось
                        founds[row].found = false;
                        founds[row].numofsame = 0;
                        // Проверяем начало нового
                        if (currentChar == dataTarget[0]) {
                            founds[row].found = true;
                            founds[row].numofsame = 1;
                        }
                    }
                }
            } else {
                // Нет активного совпадения, проверяем начало
                if (currentChar == dataTarget[0]) {
                    founds[row].found = true;
                    founds[row].numofsame = 1;
                }
            }
        }
    }
}