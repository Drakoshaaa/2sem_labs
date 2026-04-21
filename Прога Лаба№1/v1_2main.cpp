#include <iostream>
#include <fstream>

using namespace std;

const char FILEIN_V1[] = "v12_assets/v1_string5.txt";
const char FILEIN_V2[] = "v12_assets/v2_string5.txt";
const char FILEOUT[] = "out.txt";

enum VERSION {
    VERSION1 = 1,
    VERSION2 = 2
};

struct String{
    char* data;
    char mark;  
};

void skip(ifstream *filein);
void printstr(ofstream *fileout, String *Text);
unsigned char getmark(ifstream *filein);
void stopmark_analyse(ifstream *filein, unsigned char mark, unsigned char stop);
int calcsize(ifstream *filein, unsigned char mark, unsigned char stop);
void str_in(ifstream *filein, String *Text, int size);
void Process(String *Text, int *size);

int main() {
    ifstream filein;
    ofstream fileout(FILEOUT);
    
    cout << "Лабораторная №1, Версия №1 по программированию (второй семестр)\n";
    cout << "Выполнил Решетников Семён, группа 5352.\n\n";
    
    int version, pos;
    cout << "Выберите версию (1 ил 2): ";
    cin >> version;
    
    unsigned char mark, stop;
    int size = 0, fsize;
    if (version == VERSION1){
        filein.open(FILEIN_V1);
        if (!filein.is_open()) {
            cerr << "Ошибка: Не удалось открыть входной файл.\n";
            return 0;
        }
        
        mark = getmark(&filein);
        stop = getmark(&filein);
        if (mark == 0 || stop == 0) return 0;
        else if (mark == stop) {
            cerr << "Ошибко: Стоп-символ и символ-маркер не могут быть равны.\n";
            return 0;
        }
        stopmark_analyse(&filein, mark, stop);
        size = calcsize(&filein, mark, stop);
        filein.clear();
        filein.seekg(0, ios::beg);
        mark = getmark(&filein);
        stop = getmark(&filein);
    }
    else if (version == VERSION2){
        filein.open(FILEIN_V2);
        if (!filein.is_open()) {
            cerr << "Ошибка: Не удалось открыть входной файл.\n";
            return 0;
        }

        mark = getmark(&filein);
        if (mark == 0) return 0;

        filein >> fsize;   // читаем количество символов
        filein.get(); 

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


    String Text;
    Text.data = new char[size + 1];
    Text.mark = mark;

    if (version == VERSION1){
        stopmark_analyse(&filein, mark, stop);
    }
    else{
        filein.clear();
        filein.seekg(pos, ios::beg);
    }

    str_in(&filein, &Text, size);

    // Контрольный вывод в консоль и в текстовый файл
    cout << "Версия " << version << endl;
    cout << "Маркер: " << mark << endl;
        if (version == VERSION1) cout << "Стоп-символ: " << stop << endl;
        else cout << "Данный размер: " << fsize << endl; 
    cout << "Реальный размер строки: " << size << endl
         << "Исходная строка: " << endl;
    fileout << "Версия " << version << endl;
    fileout << "Маркер: " << mark << endl;
        if (version == VERSION1) fileout << "Стоп-символ: " << stop << endl;
        else fileout << "Данный размер: " << fsize << endl; 
    fileout << "Реальный размер строки: " << size << endl
         << "Исходная строка: " << endl;
    for (int i = 0; Text.data[i] != Text.mark ; i++){
        cout << Text.data[i];
        fileout << Text.data[i];
    }
    fileout << endl << endl;

    // Основная часть программы
    // Слияние и перебор всех слов
    Process(&Text, &size);

    printstr(&fileout, &Text);
    cout << "\n\nПреобразованная строка была занесена в файл " << FILEOUT;

    delete[] Text.data;
    return 0;
}

void skip(ifstream *filein){
    while(filein->peek() == ' ' || filein->peek() == '\n') filein->get();
}

void printstr(ofstream *fileout, String *Text){
    int space = 0;
    *fileout << "Результат работы программы:\n";
    for (int i = 0; Text->data[i] != Text->mark; i++){
        if (Text->data[i] == ' ' || Text->data[i] == '\n'){
            space++;
        } else{
            if (space > 0){
                *fileout << " ";
            }
            space = 0;
            *fileout << Text->data[i];   
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

void stopmark_analyse(ifstream *filein, unsigned char mark, unsigned char stop){
    unsigned char ch = 0;
    int numofstopchar = 0;

    // Считаем сколько раз в строке встретился стоп-символ
    while (ch != mark && !filein->eof()){
        *filein >> noskipws >> ch;
        if (ch == stop) numofstopchar++;
    }
    filein->clear();
    filein->seekg(0, ios::beg);
    mark = getmark(filein);
    stop = getmark(filein);

    ch = 0;

    // Если стоп символов один или более - значит необходимо начинать чтение с первого такого символа
    if (numofstopchar >= 1){
        while (ch != stop) *filein >> noskipws >> ch;
    }

}

int calcsize(ifstream *filein, unsigned char mark, unsigned char stop){
    int size = 0;
    unsigned char ch = 0;
    
    // Если же стоп символов нет - читаем с самого начала
    while (*filein >> noskipws >> ch && ch != stop && ch != mark){
        size++;
    }

    return size;
}

void str_in(ifstream *filein, String *Text, int size){
    unsigned char ch = 0;
    int i = 0;

    // Заполняем массив
    while (i < size){
        *filein >> noskipws >> ch;

        Text->data[i] = ch;

        i++;
    }
    
    // Добавляем символ-маркер в конец строки
    Text->data[size] = Text->mark;
}

void Process(String *Text, int *size){

    // Основная часть программы
    // Слияние строк и перебор всех слов
    bool changed = true;

    while (changed) {
        changed = false;

        int pos = 0;

        while (Text->data[pos] != Text->mark) {

            // пропускаем пробелы и переводы строки
            while (Text->data[pos] != Text->mark && 
                (Text->data[pos] == ' ' || Text->data[pos] == '\n'))
                pos++;

            if (Text->data[pos] == Text->mark) break;

            // определяем первое слово
            int idx1 = pos;
            int end1 = idx1;

            while (Text->data[end1] != Text->mark &&
                Text->data[end1] != ' ' &&
                Text->data[end1] != '\n')
                end1++;

            char target = Text->data[end1 - 1];   // последняя буква

            // ищем подходящее слово справа
            int search = end1;
            int idx2 = -1;
            int end2 = -1;

            while (Text->data[search] != Text->mark) {

                while (Text->data[search] != Text->mark &&
                    (Text->data[search] == ' ' ||
                    Text->data[search] == '\n'))
                    search++;

                if (Text->data[search] == Text->mark) break;

                if (Text->data[search] == target) {
                    idx2 = search;
                    end2 = idx2;

                    while (Text->data[end2] != Text->mark &&
                        Text->data[end2] != ' ' &&
                        Text->data[end2] != '\n')
                        end2++; 

                    break;
                }

                while (Text->data[search] != Text->mark &&
                    Text->data[search] != ' ' &&
                    Text->data[search] != '\n')
                    search++;
            }

            if (idx2 == -1) {
                pos = end1;
                continue;
            }

            // 1. Одновременный сдвиг текста между end1 и idx2 влево
            // и  посимвольное копирование первого слова перед вторым

            for (int i = end1-1; i >= idx1 ; i--, idx2--){

                Text->data[idx2] = Text->data[i];

                for (int k = i; k < idx2-1 ; k++){
                    Text->data[k] = Text->data[k+1];
                }
                
            }
            
            // 2. Свдигаем на один индекс всё, что правее idx2
            for (int i = idx2 ; Text->data[i] != Text->mark ; i++){
                Text->data[i-1] = Text->data[i]; 
            }
            
            (*size)--;  // уменьшаем на 1
            Text->data[*size] = Text->mark;
            

            changed = true;
            
            break;  // начинаем проход заново
        }
    }
}