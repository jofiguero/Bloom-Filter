#include "BloomFilter.cpp"
#include "experimentacion.cpp"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <cstring>
#include <sstream>
#include <tuple>

int mainfalso(){
    ifstream file("Popular-Baby-Names-Final.csv");
    string line;
    int z = 0;
    int i = 0;
    while (getline(file, line)){
        BloomFilter bf = BloomFilter(10000,456,93000);
        char str1[] = "hello";
        char str2[] = "world";
        char str3[] = "test";
        char str4[] = "bloom";

        bf.add(str1);
        bf.add(str2);
        
        z += buscar(&bf,line);
        i++;
        if (i > 1000){
            break;
        }
    }
    cout << z << endl;
    return 0;
}
int main(){
    printf("%d\n",koptimo(20000,96000));
    return 0;

}