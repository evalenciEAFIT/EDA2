#include "Counter.h"
#include <iostream>
#include <chrono>

// Constructor que inicializa el ID del hilo
Counter::Counter(int id) : id(id) {}

// Método que será ejecutado por el hilo
void Counter::run() {
    for (int i = 1; i <= 5; ++i) {
        // Imprimir el número y el ID del hilo
        std::cout << "Hilo " << id << " cuenta: " << i << std::endl;
        
        // Esperar 1 segundo para simular trabajo
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
