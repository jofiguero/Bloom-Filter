#include <iostream>
#include <bitset>
using namespace std; 
int main() {
    // Crear un bitset con 8 bits
    bitset<8> bits;

    // Mostrar el bitset inicial (por defecto todos los bits son 0)
    cout << "Bits iniciales: " << bits << endl;

    // Activar el bit en la posición 3
    bits.set(3);
    cout << "Después de activar el bit 3: " << bits << endl;

    // Desactivar el bit en la posición 3
    bits.reset(3);
    cout << "Después de desactivar el bit 3: " << bits << endl;

    // Acceder a un bit específico (por ejemplo, el bit en la posición 3)
    bool bitEnPosicion3 = bits.test(3);
    cout << "El bit en la posición 3 es: " << bitEnPosicion3 << endl;

    return 0;
}
