#ifndef ARCHIVOH
#define ARCHIVO_H

#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>  // Para std::rand y std::srand
#include <ctime>    // Para std::time

class Archivo {
private:
    std::vector<std::string> items;

public:
    // Constructor
    Archivo();

    // Método para leer los items desde un archivo
    void leerDesdeArchivo(const std::string& nombreArchivo);

    // Método para imprimir los items
    void imprimirItems() const;

    // Método para retornar un item aleatorio
    std::string obtenerItemAleatorio() const;
};

#endif // ARCHIVO_H
