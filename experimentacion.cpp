#ifndef EXP_CPP
#define EXP_CPP
#include "BloomFilter.cpp"
#include <iostream>
#include <time.h>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstring>
#include <sstream>
#include <tuple>

using namespace std; 

int koptimo(int M, int N){
    int k = (M/N)*log(2);
    return k;
}

int buscar(BloomFilter *bf, const string &search_term) {
    char c_search_term[search_term.length() + 1];
    strcpy(c_search_term, search_term.c_str());
    if(bf->contains(c_search_term)){
        //printf("entré\n");
        ifstream file("Popular-Baby-Names-Final.csv");
        string line;
        while (getline(file, line)) {
            stringstream line_stream(line);
            string cell;  
        }
        file.close();
        return 1;
    }
    return 0;
}

int buscarSinFiltro(const string &search_term) {
    char c_search_term[search_term.length() + 1];
    strcpy(c_search_term, search_term.c_str());
    ifstream file("Popular-Baby-Names-Final.csv");
    string line;
    while (getline(file, line)) {
    stringstream line_stream(line);
    string cell;
    if (getline(line_stream, cell, ',')) {
        if (cell.find(search_term) != string::npos) {
            return 1;
        }
    }
    return 0;
    file.close();
    }
    return 0;
}

void EXP(){
    int sizeBN = 93890;
    int sizeFN = 3809;

    vector<tuple<int, double>> pares;
    pares.push_back(make_tuple(pow(2,10), 0));
    pares.push_back(make_tuple(pow(2,10), 0.25));
    pares.push_back(make_tuple(pow(2,10), 0.5));
    pares.push_back(make_tuple(pow(2,10), 0.75));
    pares.push_back(make_tuple(pow(2,10), 1));

    pares.push_back(make_tuple(pow(2,12), 0));
    pares.push_back(make_tuple(pow(2,12), 0.25));
    pares.push_back(make_tuple(pow(2,12), 0.5));
    pares.push_back(make_tuple(pow(2,12), 0.75));
    pares.push_back(make_tuple(pow(2,12), 1));

    pares.push_back(make_tuple(pow(2,14), 0));
    pares.push_back(make_tuple(pow(2,14), 0.25));
    pares.push_back(make_tuple(pow(2,14), 0.5));
    pares.push_back(make_tuple(pow(2,14), 0.75));
    pares.push_back(make_tuple(pow(2,14), 1));

    pares.push_back(make_tuple(pow(2,16), 0));
    pares.push_back(make_tuple(pow(2,16), 0.25));
    pares.push_back(make_tuple(pow(2,16), 0.5));
    pares.push_back(make_tuple(pow(2,16), 0.75));
    pares.push_back(make_tuple(pow(2,16), 1));

    for(tuple<int, double> tupla : pares){
        int N = get<0>(tupla);
        double p = get<1>(tupla); 
        printf("Comienza el experimento para (%d,%f)\n",N,p);
        for(int m = 100000; m <= 2200000; m += 500000){
            printf("m = %d, ",m);
            int k = koptimo(m,sizeBN);
            printf("k: %d, ",k);
            BloomFilter BF = BloomFilter(m,k,sizeBN);
            /*Añadir datos al filtro*/
            ifstream myfile("Popular-Baby-Names-Final.csv");
            string line1;
            if (myfile.is_open()) {
                while (getline(myfile, line1)) {
                    // Convertir la línea de string a char*
                    char* cstr = new char[line1.length() + 1];
                    strcpy(cstr, line1.c_str());
                    // Añadir la cadena al filtro de Bloom
                    BF.add(cstr);
                    // Liberar memoria
                    delete[] cstr;
                }
                myfile.close();
            } else {
                cerr << "No se pudo abrir el archivo" << endl;
            }
            int cantidadBM = N*p;
            int cantidadFM = (1-p)*N;
            unsigned filtro_inicio, filtro_final, filtro_diferencia, nofiltro_inicio, nofiltro_final, nofiltro_diferencia;
            int resultBF = 0;
            ifstream BabyFile("Popular-Baby-Names-Final.csv");
            string line2;
            if (BabyFile.is_open()) {
                int i = 0;
                filtro_inicio = clock();
                while (getline(BabyFile, line2)) {
                    if(i == cantidadBM){
                        break;
                    }
                    resultBF+= buscar(&BF, line2);
                    i++;
                }
                BabyFile.close();
                
            } else {
                cerr << "No se pudo abrir el archivo para buscar" << endl;
            }
            ifstream FilmFile("Film-Names.csv");
            string line3;

            if (FilmFile.is_open()) {
                int j = 0;
                while (getline(FilmFile, line3)) {
                    if(j == cantidadFM){
                        break;
                    }
                    resultBF+= buscar(&BF, line3);
                    j++;
                }
                FilmFile.close();
                filtro_final = clock();
                filtro_diferencia = filtro_final - filtro_inicio;
            } else {
                cerr << "No se pudo abrir el archivo para buscar" << endl;
            }

            int cantidad_errores = resultBF - cantidadBM;
            double prob_error = ((double)cantidad_errores)/((double)N);

            printf("probabilidad de errores con filtro de bloom:%f\n",prob_error);

            int resultNotBF = 0;
            ifstream BabyFile2("Popular-Baby-Names-Final.csv");
            string line4;
            if (BabyFile2.is_open()) {
                int i = 0;
                nofiltro_inicio = clock();
                while (getline(BabyFile2, line4)) {
                    if(i == cantidadBM){
                        break;
                    }
                    resultNotBF+= buscarSinFiltro(line4);
                    i++;
                }
                BabyFile.close();
                
            } else {
                cerr << "No se pudo abrir el archivo para buscar sin filtro" << endl;
            }
            ifstream FilmFile2("Film-Names.csv");
            string line5;

            if (FilmFile2.is_open()) {
                int j = 0;
                while (getline(FilmFile2, line5)) {
                    if(j == cantidadFM){
                        break;
                    }
                    resultNotBF+= buscarSinFiltro(line5);
                    j++;
                }
                FilmFile.close();
                nofiltro_final = clock();
                nofiltro_diferencia = nofiltro_final - nofiltro_inicio;
            } else {
                cerr << "No se pudo abrir el archivo para buscar sin filtro" << endl;
            }

            printf("Tiempo de busqueda con filtro de Bloom: %u\n",filtro_diferencia);
            printf("Tiempo de busqueda sin filtro de Bloom: %u\n",nofiltro_diferencia);
            printf("\n");

        }
        printf("------------------------------------------------------------------\n");
    }
}


#endif

#if 1
int main(){
    EXP();
    return 0;
}
#else
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
#endif