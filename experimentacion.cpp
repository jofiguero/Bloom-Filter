#include "BloomFilter.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std; 

int koptimo(int M, int N){
    int k = (M/N)*log(2);
    return k;
}

int buscar(BloomFilter bf, const string &search_term) {
    char c_search_term[search_term.length() + 1];
    strcpy(c_search_term, search_term.c_str());
    if(bf.contains(c_search_term)){
        ifstream file("Popular-Baby-Names-Final.csv");
        string line;
        while (getline(file, line)) {
            stringstream line_stream(line);
            string cell;
            if (getline(line_stream, cell, ',')) {
                if (cell.find(search_term) != string::npos) {
                    cout << line << endl;
                }
            }
        }
        file.close();
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    BloomFilter bf(100, 3, 10); // Crear un filtro de Bloom con un bit array de tamaño 100 y 3 funciones hash

    char str1[] = "hello";
    char str2[] = "world";
    char str3[] = "test";
    char str4[] = "bloom";

    bf.add(str1);
    bf.add(str2);


    int z = 0;
    z+= buscar(bf, str1);
    z+= buscar(bf, str2);
    z+= buscar(bf, str3);
    z+= buscar(bf, str4);
    cout << "Resultado': " << z << endl;
    return 0;
}