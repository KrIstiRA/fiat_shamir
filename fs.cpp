#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>

using namespace std;

void readKeys(largeClass &a, largeClass &b, string filename)
{
    ifstream ifst(filename.c_str());
    string a_str, b_str;
    getline(ifst, a_str);
    getline(ifst, b_str);

    a = largeClass(a_str.c_str());
    b = largeClass(b_str.c_str());
}


int main(int argc, char* argv[])
{
    // http://dic.academic.ru/dic.nsf/ruwiki/1328610
    srand(time(0));
    if (argc != 2)
    {
        cerr << "Usage: fs <key_name>" << endl;
        return 1;
    }
    string key_name = argv[1];
    
    largeClass n, s, v;
    readKeys(n, v, (key_name + string(".pub")).c_str());
    readKeys(n, s, (key_name + string(".priv")).c_str());

    int t = 5; // пусть будет 5 раундов аккредитации

    bool isOk = true;
    for (int i = 0; i < t && isOk; i++)
    {
        // Алиса - претендент выбирает случайное число r между 0, и n - 1 
        largeClass n_1 = n - 1;
        largeClass r = GenRandomByRangeC(n_1);

        // Она затем вычисляет значение
        //x = r^2 mod n
        largeClass two = 2;
        largeClass x = powModClass(r, two, n);

        // Алиса передает x Бобу.
        // Боб-верификатор передает вызов e Алисе. Значение e равно или 0, или 1.
        largeClass e = rand() % 2;

        // Алиса вычисляет свой ответ y = r * s^e.
        largeClass y = (r * powModClass(s, e, n)) % n;

        // Алиса передает ответ Бобу, чтобы показать, что она знает значение 
        // своего секретного ключа, s. Она подтверждает, что это была именно Алиса.

        // Боб вычисляет y^2 и x * v ^ e. 
        // Если эти два значения являются конгруэнтными, 
        // то для Алисы значение s означает "она честна";
        largeClass yy = powModClass(y, two, n);
        largeClass xve = (x * powModClass(v, e, n)) % n;

        if (yy != xve) 
            isOk = false;
    }
    if (isOk)
        cout << "Key accepted" << endl;
    else
        cout << "Key rejected" << endl;

    return 0;
}
