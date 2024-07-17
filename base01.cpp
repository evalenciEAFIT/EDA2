/*
Comando para compilar: g++ base01.cpp -o demo

Comando para ejecutar: ./demo
*/

#include <iostream>

int main() {
    int var = 10; // Una variable entera
    int* ptr; // Un apuntador a un entero

    ptr = &var; // ptr apunta a la dirección de var

    // Imprimir el valor de var usando el apuntador
    std::cout << "El valor de var es: " << var << std::endl;
    std::cout << "El valor de var usando el apuntador es: " << *ptr << std::endl;

    // Imprimir la dirección de var
    std::cout << "La direccion de var es: " << &var << std::endl;
    std::cout << "El valor del apuntador (direccion de var) es: " << ptr << std::endl;

    // Cambiar el valor de var usando el apuntador
    *ptr = 20;
    std::cout << "El nuevo valor de var es: " << var << std::endl;

    return 0;
}
