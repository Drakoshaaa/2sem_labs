#include <iostream>
#include <fstream>

using namespace std;

const char FILEIN_V3[] = "v34_assets/v3_string3.txt";
const char FILEIN_V4[] = "v34_assets/v4_string3.txt";
const char FILEOUT[] = "out.txt";

void skip(ifstream *filein);
unsigned char getmark(ifstream *filein);
void stopmark_analyse(ifstream *filein, unsigned char stop);
int calcsize(ifstream *filein, unsigned char stop);

enum VERSION {
    VERSION3 = 3,
    VERSION4 = 4
};    

class String{
private:    
    char* data;
    int len; 
public:    
    String(int size);
    ~String();
    const char GetData(int i);
    const int GetLen();
    void SetLen(int size);

    void printstr(ofstream *fileout);
    void str_in(ifstream *filein);
    void Process();
};    


String::String(int size){
    len = size;
    data = new char[size];
}
String::~String(){
    delete[] data;
}
const char String::GetData(int i){
    return data[i];
}
const int String::GetLen(){
    return len;
}
void String::SetLen(int size){
    len = size;
}


int main() {
    ifstream filein;
    ofstream fileout(FILEOUT);
    
    cout << "Лабораторная №1, Версия №1 по программированию (второй семестр)\n";
    cout << "Выполнил Решетников Семён, группа 5352.\n\n";
    
    int version, pos;
    cout << "Выберите версию (3 или 4): ";
    cin >> version;
    
    unsigned char stop;
    int size = 0, fsize;
    if (version == VERSION3){
        filein.open(FILEIN_V3);
        if (!filein.is_open()) {
            cerr << "Ошибка: Не удалось открыть входной файл.\n";
            return 0;
        }
        
        stop = getmark(&filein);
        if (stop == 0) return 0;

        stopmark_analyse(&filein, stop);
        size = calcsize(&filein, stop);
        filein.clear();
        filein.seekg(0, ios::beg);
        stop = getmark(&filein);
    }
    else if (version == VERSION4){
        filein.open(FILEIN_V4);
        if (!filein.is_open()) {
            cerr << "Ошибка: Не удалось открыть входной файл.\n";
            return 0;
        }

        filein >> fsize;   // читаем количество символов
        skip(&filein); 

        if (fsize <= 0) {
            cerr << "Ошибка: Некорректный размер строки.\n";
            return 0;
        }

        pos = filein.tellg();

        // Считаем реальное количество символов
        unsigned char ch;
        while (filein >> noskipws >> ch && size < fsize) size++;
    }
    else{
        cerr << "Ошибка: Такой версии не существует";
        return 0;
    }

    String Text(size);

    if (version == VERSION3){
        stopmark_analyse(&filein, stop);
    }
    else{
        filein.clear();
        filein.seekg(pos, ios::beg);
    }

    Text.str_in(&filein);

    // Контрольный вывод в консоль и в текстовый файл
    cout << "Версия " << version << endl;
        if (version == VERSION3) cout << "Стоп-символ: " << stop << endl;
        else cout << "Данный размер: " << fsize << endl; 
    cout << "Реальный размер строки: " << Text.GetLen() << endl
         << "Исходная строка: " << endl;
    fileout << "Версия " << version << endl;
        if (version == VERSION3) fileout << "Стоп-символ: " << stop << endl;
        else fileout << "Данный размер: " << fsize << endl; 
    fileout << "Реальный размер строки: " << Text.GetLen() << endl
         << "Исходная строка: " << endl;
    for (int i = 0; i < Text.GetLen(); i++){
        cout << Text.GetData(i);
        fileout << Text.GetData(i);
    }
    cout << "\n";
    fileout << endl << endl;

    // Основная часть программы
    // Слияние и перебор всех слов
    Text.Process();

    Text.printstr(&fileout);
    cout << "\n\nПреобразованная строка была занесена в файл " << FILEOUT;

    return 0;
}

void skip(ifstream *filein){
    while(filein->peek() == ' ' || filein->peek() == '\n') filein->get();
}

void String::printstr(ofstream *fileout){
    int space = 0;
    *fileout << "Результат работы программы:\n";
    for (int i = 0; i < len; i++){
        if (data[i] == ' ' || data[i] == '\n'){
            space++;
        } else{
            if (space > 0){
                *fileout << " ";
            }
            space = 0;
            *fileout << data[i];   
        }
        
    }
}

unsigned char getmark(ifstream *filein){
    unsigned char ch;

    if (!filein->eof()){
        skip(filein);

        *filein >> ch;

        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)){
            cerr << "Ошибко: Вы не задали стоп-символ или символ-маркер.\n";
            return 0;
        }
        else{
            return ch;
        }
    } 
    else{
        cerr << "Ошибко: Входной файл пуст.";
        return 0;
    }
}

void stopmark_analyse(ifstream *filein, unsigned char stop){
    unsigned char ch = 0;
    int numofstopchar = 0;

    // Считаем сколько раз в строке встретился стоп-символ
    while (!filein->eof()){
        *filein >> noskipws >> ch;
        if (ch == stop) numofstopchar++;
    }
    filein->clear();
    filein->seekg(0, ios::beg);
    stop = getmark(filein);
    skip(filein);

    ch = 0;

    // Если стоп символов один или более - значит необходимо начинать чтение с первого такого символа
    if (numofstopchar >= 1){
        while (ch != stop) *filein >> noskipws >> ch;
    }

}

int calcsize(ifstream *filein, unsigned char stop){
    int size = 0;
    unsigned char ch = 0;
    
    // Если же стоп символов нет - читаем с самого начала
    while (*filein >> noskipws >> ch && ch != stop){
        size++;
    }

    return size;
}

void String::str_in(ifstream *filein){
    unsigned char ch = 0;
    int i = 0;

    // Заполняем массив
    while (i < len){
        *filein >> noskipws >> ch;

        data[i] = ch;

        i++;
    }
}

void String::Process(){

    // Основная часть программы
    // Слияние строк и перебор всех слов

    bool changed = true;

    while (changed) {
        changed = false;

        int pos = 0;

        while (pos < len) {

            // пропускаем пробелы и переводы строки
            while (pos < len && 
                (data[pos] == ' ' || data[pos] == '\n'))
                pos++;

            if (pos == len) break;

            // определяем первое слово
            int idx1 = pos;
            int end1 = idx1;

            while (end1 < len &&
                data[end1] != ' ' &&
                data[end1] != '\n')
                end1++;

            char target = data[end1 - 1];   // последняя буква

            // ищем подходящее слово справа
            int search = end1;
            int idx2 = -1;
            int end2 = -1;

            while (search < len) {

                while (search < len &&
                    (data[search] == ' ' ||
                    data[search] == '\n'))
                    search++;

                if (search == len) break;

                if (data[search] == target) {
                    idx2 = search;
                    end2 = idx2;

                    while (end2 < len &&
                        data[end2] != ' ' &&
                        data[end2] != '\n')
                        end2++; 

                    break;
                }

                while (search < len &&
                    data[search] != ' ' &&
                    data[search] != '\n')
                    search++;
            }

            if (idx2 == -1) {
                pos = end1;
                continue;
            }

            // 1. Одновременный сдвиг текста между end1 и idx2 влево
            // и  посимвольное копирование первого слова перед вторым

            for (int i = end1-1; i >= idx1 ; i--, idx2--){

                data[idx2] = data[i];

                for (int k = i; k < idx2-1 ; k++){
                    data[k] = data[k+1];
                }
            }
            
            // 2. Свдигаем на один индекс всё, что правее idx2
            for (int i = idx2 ; i < len; i++){
                data[i-1] = data[i]; 
            }
            
            len--;  // уменьшаем на 1
            
            changed = true;
            
            break;  // начинаем проход заново
        }
    }
}