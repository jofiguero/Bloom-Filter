#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std; 
// Función para verificar si un número es primo
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Función para encontrar el siguiente número primo mayor que n
int findNextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}

//Suma los caracteres ascii de un string
int sumAsciiValues(char* str) {
    int sum = 0;
    while (*str) { // Mientras no lleguemos al final del string
        sum += static_cast<int>(*str); // Sumar el valor ASCII del caracter actual
        ++str; // Avanzar al siguiente caracter
    }
    return sum;
}

// Clase del Filtro de Bloom
class BloomFilter {
private:
    vector<bool> bitArray;
    int m; // Tamaño del bit array
    int k; // Número de funciones de hash
    int p; // Número primo mayor que el universo de claves
    vector<pair<int, int>> hashParams;

public:
    //constructor
    BloomFilter(int size, int numHashes, int inputsize) : m(size), k(numHashes) {
        bitArray.resize(m, false); // Seteamos los m bits como falsos
        p = findNextPrime(inputsize + 1); // Selección del primo p basado en el tamaño del input posible
        srand(time(0)); //Se setea una semilla diferente para cada ejecucion

        // Generación de parámetros para las funciones de hash
        for (int i = 0; i < k; i++) {
            int a = rand() % (p - 1) + 1;
            int b = rand() % p;
            hashParams.push_back({a, b});
        }
    }

    //Usa una función de hash universal para hashear un string a un indice
    int hash(char* str, int i) const {
        int x = sumAsciiValues(str);
        int a = hashParams[i].first;
        int b = hashParams[i].second;
        return ((a * x + b) % p) % m;
    }

    //Añade un string al filtro activando todos los bits pertinentes
    void add(char* str) {
        for (int i = 0; i < k; i++) {
            int index = hash(str, i);
            bitArray[index] = true;
        }
    }

    //Verifica si un string está en el filtro
    bool contains(char* str) const {
        for (int i = 0; i < k; i++) {
            int index = hash(str, i);
            if (!bitArray[index]) {
                return false;
            }
        }
        return true;
    }
};

//int main() {
//    BloomFilter bf(100, 3, 10); // Crear un filtro de Bloom con un bit array de tamaño 100 y 3 funciones hash
//
//    char str1[] = "hello";
//    char str2[] = "world";
//    char str3[] = "test";
//    char str4[] = "bloom";
//
//    bf.add(str1);
//    bf.add(str2);
//
//    cout << "Contains 'hello': " << bf.contains(str1) << endl; // Debería imprimir 1 (true)
//    cout << "Contains 'world': " << bf.contains(str2) << endl; // Debería imprimir 1 (true)
//    cout << "Contains 'test': " << bf.contains(str3) << endl;  // Podría imprimir 0 (false)
//    cout << "Contains 'bloom': " << bf.contains(str4) << endl; // Podría imprimir 0 (false)
//
//    return 0;
//}
