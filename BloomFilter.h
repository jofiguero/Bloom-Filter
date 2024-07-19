#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <vector>
#include <utility>

class BloomFilter {
private:
    std::vector<bool> bitArray;
    int m; // Tamaño del bit array
    int k; // Número de funciones de hash
    int p; // Número primo mayor que el universo de claves
    std::vector<std::pair<int, int>> hashParams;

public:
    // Constructor
    BloomFilter(int size, int numHashes, int inputsize);

    // Añade un string al filtro activando todos los bits pertinentes
    void add(char* str);

    // Verifica si un string está en el filtro
    bool contains(char* str) const;

private:
    // Usa una función de hash universal para hashear un string a un índice
    int hash(char* str, int i) const;

    // Suma los caracteres ASCII de un string
    int sumAsciiValues(char* str) const;
    
    // Función para verificar si un número es primo
    bool isPrime(int n) const;
    
    // Función para encontrar el siguiente número primo mayor que n
    int findNextPrime(int n) const;
};

#endif // BLOOMFILTER_H