#include "Philosopher.h"
#include <chrono>   // Para std::this_thread::sleep_for

// Constructor de la clase Philosopher
// Inicializa el identificador del filósofo y los mutexes de los tenedores
Philosopher::Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork)
    : id(id), leftFork(leftFork), rightFork(rightFork) {}

// Operador de llamada que permite que el objeto Philosopher sea llamado como una función
void Philosopher::operator()() {
    while (true) {
        think();
        
        // Adquiere ambos tenedores utilizando std::lock para evitar deadlocks
        // std::lock asegura que se bloqueen ambos mutexes en un orden específico
        // y previene bloqueos circulares.
        std::lock(leftFork, rightFork); // Bloquea ambos tenedores simultáneamente
        std::lock_guard<std::mutex> leftLock(leftFork, std::adopt_lock);  // Bloquea el tenedor izquierdo
        std::lock_guard<std::mutex> rightLock(rightFork, std::adopt_lock); // Bloquea el tenedor derecho
        
        eat(); // Come después de adquirir ambos tenedores
    }
}

// Método para simular el pensamiento del filósofo
// Imprime un mensaje y simula el tiempo de pensamiento del filósofo
void Philosopher::think() {
    std::cout << "Philosopher " << id << " es \033[32mPENSANDO\033[0m." << std::endl;
    // Simula el tiempo de pensamiento del filósofo
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 10000));
}

// Método para simular la comida del filósofo
// Imprime un mensaje y simula el tiempo de comida del filósofo
void Philosopher::eat() {
    std::cout << "Philosopher " << id << " esta \033[31mCOMIENDO\033[0m." << std::endl;
    // Simula el tiempo de comida del filósofo
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 10000));
}
