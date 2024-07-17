#include "archivo.h"
#include <iostream>

// Constructor
Archivo::Archivo() {
    // Inicializar el generador de números aleatorios con el tiempo actual
    std::srand(static_cast<unsigned int>(std::time(0)));
}

// Método para leer los textos desde un archivo
void Archivo::leerDesdeArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        std::string texto;
        while (std::getline(archivo, texto)) {
            items.push_back(texto);
        }
        archivo.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << std::endl;
    }
}

// Método para imprimir los items
void Archivo::imprimirItems() const {
    int i=1;
    for (const auto& item : items) {
        std::cout << "["<< i << "]: " <<item << std::endl;
        i=i+1;
    }
    std::cout << std::endl;
}

// Método para retornar un item aleatorio
std::string Archivo::obtenerItemAleatorio() const {
    if (items.empty()) {
        return "No hay nombres en la lista.";
    }
    int indiceAleatorio = std::rand() % items.size();
    return items[indiceAleatorio];
}
