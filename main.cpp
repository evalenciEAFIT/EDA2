/*
Comandos para compilar: g++ -c archivo.cpp
                        g++ main.cpp archivo.o -o demo
                        
Conado para ejecutar: ./demo
*/

#include <iostream>
#include "archivo.h"

int main() {
    Archivo lista;
    lista.leerDesdeArchivo("nombres.txt");

    std::cout << "Lista de items:" << std::endl;
    lista.imprimirItems();

    std::cout << "Item aleatorio de la lista: " << lista.obtenerItemAleatorio() << std::endl;

    return 0;
}
