#include <iostream>   // Para std::cout
#include <thread>     // Para std::thread
#include <vector>     // Para std::vector
#include <mutex>      // Para std::mutex
#include "Philosopher.h" // Incluye la definición de Philosopher

// Número de filósofos en la mesa
const int NUM_PHILOSOPHERS = 5;

int main() {
    // Crear un vector de mutexes para representar los tenedores
    // Cada mutex actúa como un tenedor que protege el acceso concurrente
    std::vector<std::mutex> forks(NUM_PHILOSOPHERS);

    // Crear un vector de hilos para los filósofos
    std::vector<std::thread> philosophers;

    // Inicializar los filósofos
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        // Obtener el mutex para el tenedor izquierdo del filósofo actual
        std::mutex& leftFork = forks[i];
        // Obtener el mutex para el tenedor derecho del filósofo actual (circular)
        std::mutex& rightFork = forks[(i + 1) % NUM_PHILOSOPHERS];

        // Crear un hilo para el filósofo y pasarle los tenedores correspondientes
        // El filósofo será ejecutado en el hilo y se comportará como una función callable
        philosophers.emplace_back(Philosopher(i, leftFork, rightFork));
    }

    // Esperar a que todos los hilos terminen
    // En este caso, los hilos corren indefinidamente, por lo que esta llamada a join() nunca termina
    for (auto& philosopher : philosophers) {
        philosopher.join();
    }

    return 0;
}
