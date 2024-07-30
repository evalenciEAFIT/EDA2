#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <thread>     // Para std::thread
#include <mutex>      // Para std::mutex
#include <iostream>   // Para std::cout

// Declaración de la clase Philosopher
class Philosopher {
public:
    // Constructor de la clase Philosopher
    // Inicializa el filósofo con un id y referencias a los tenedores izquierdo y derecho
    Philosopher(int id, std::mutex& leftFork, std::mutex& rightFork);

    // Operador de llamada que permite que el objeto Philosopher sea llamado como una función
    void operator()();

private:
    int id; // Identificador del filósofo
    std::mutex& leftFork; // Referencia al mutex del tenedor a la izquierda
    std::mutex& rightFork; // Referencia al mutex del tenedor a la derecha

    // Método privado para simular el pensamiento del filósofo
    void think();

    // Método privado para simular la comida del filósofo
    void eat();
};

#endif // PHILOSOPHER_H
