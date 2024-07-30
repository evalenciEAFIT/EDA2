#ifndef COUNTER_H
#define COUNTER_H

#include <thread>

// Clase que representa un contador en un hilo
class Counter {
public:
    // Constructor que toma el ID del hilo
    Counter(int id);

    // Método que será ejecutado por el hilo
    void run();

private:
    int id;  // ID del hilo
};

#endif // COUNTER_H
