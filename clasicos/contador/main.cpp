#include "Counter.h"
#include <vector>
#include <thread>

int main() {
    // Número de hilos a crear
    const int numThreads = 3;

    // Crear un vector para almacenar los hilos
    std::vector<std::thread> threads;

    // Crear y lanzar los hilos
    for (int i = 0; i < numThreads; ++i) {
        // Crear un objeto Counter para cada hilo
        Counter counter(i + 1);
        // Emplace_back crea un nuevo hilo y lo inicia
        threads.emplace_back(&Counter::run, counter);
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        // Unir cada hilo al hilo principal
        thread.join();
    }

    return 0;
}
