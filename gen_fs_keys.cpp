#include <iostream>
#include "largeClass/largeClass.h"
#include "stdlib.h"
#include "time.h"
#include <string>
#include <fstream>

using namespace std;


void gen_fs_keys(int bitlen, string key_name)
{
	// 3-е лицо генерирует простые  p,q и вычисляет n
    largeClass p = GenPrime(bitlen);
    largeClass q = GenPrime(bitlen);
    largeClass n = p * q;

    // Алиса генерирует s и вычисляет v = s^2
    largeClass n_1 = n - 1;
    largeClass s = GenRandomByRangeC(n_1);
    largeClass two = 2;
    largeClass v = powModClass(s, two, n);

    ofstream pub((key_name + string(".pub")).c_str());
    ofstream priv((key_name + string(".priv")).c_str());

    pub << n.str() << endl << v.str() << endl;
    priv << n.str() << endl << s.str() << endl;
}

int main(int argc, char* argv[])
{
    srand(time(0));
    if (argc != 3)
    {
        cerr << "Generate keys for Fiat-Shamir" << endl;
        cerr << "Usage: gen_fs_keys <bitlen> <key_name>" << endl;
        return 1;
    }
    gen_fs_keys(atoi(argv[1]), argv[2]);
    return 0;
}
