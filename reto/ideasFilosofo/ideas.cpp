#include <iostream>      // Para operaciones de entrada y salida
#include <thread>        // Para el uso de hilos
#include <mutex>         // Para el uso de mutex (aunque no se usa en este ejemplo, puede ser útil)
#include <vector>        // Para el uso de vectores
#include <random>        // Para generar números aleatorios
#include <chrono>        // Para manejar tiempos
#include <semaphore.h>   // Para el uso de semáforos

using namespace std;

// Secuencias de escape ANSI para colores
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

int limiteIteraciones = 4; //cantidad
int tiempoxIdea = 3;  //segunos
int limitePensar = 20; //segundos
int limiteComer = 10; //segundos


// Clase que representa a un Filósofo
class Filosofo {
private:
    int id;                  // Identificador del filósofo
    int ideasGeneradas;      // Número de ideas generadas
    int vecesComidas;        // Número de veces que ha comido
    sem_t *tenedorIzquierdo; // Semáforo para el tenedor izquierdo
    sem_t *tenedorDerecho;   // Semáforo para el tenedor derecho

public:
    // Constructor que inicializa al filósofo con su ID y tenedores
    Filosofo(int id, sem_t *tenedorIzquierdo, sem_t *tenedorDerecho) :
        id(id), ideasGeneradas(0), vecesComidas(0), tenedorIzquierdo(tenedorIzquierdo), tenedorDerecho(tenedorDerecho) {}

    // Método que simula el pensamiento del filósofo
    void pensar() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(limitePensar/4, limitePensar); // Tiempo de pensar entre 10 y 20 segundos
        int tiempoPensar = dis(gen);
        this_thread::sleep_for(chrono::seconds(tiempoPensar)); // Simula el tiempo de pensar
        //int tiempoxIdea = 10;
        ideasGeneradas += tiempoPensar / tiempoxIdea; // Genera una idea por cada 10 segundos de pensamiento

    }

    // Método que simula que el filósofo está comiendo
    void comer() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(limiteComer/4, limiteComer); // Tiempo de comer entre 30 y 120 segundos
        int tiempoComer = dis(gen);
        this_thread::sleep_for(chrono::seconds(tiempoComer)); // Simula el tiempo de comer
        vecesComidas++;
        cout << "Filósofo " << id << " está "<<RED<<"comiendo"<<RESET<<" por " << tiempoComer << " segundos.\n";
    }

    // Método principal donde el filósofo alterna entre comer y pensar
    void cenar() {
        //int limiteIteraciones = 10;
        while (vecesComidas < limiteIteraciones) { // Come hasta 10 veces
            cout << "Filósofo " << id << " itera: "<< vecesComidas << "/"<< limiteIteraciones <<" turnos, y tiene ideas acumuladas: "<< ideasGeneradas << ".\n";
            sem_wait(tenedorIzquierdo); // Toma el tenedor izquierdo
            sem_wait(tenedorDerecho); // Toma el tenedor derecho

            comer(); // Come

            sem_post(tenedorDerecho); // Suelta el tenedor derecho
            sem_post(tenedorIzquierdo); // Suelta el tenedor izquierdo

            pensar(); // Piensa
            cout << "Filósofo " << id << " está "<<GREEN<<"pensando."<<RESET<<"\n";
        }
        cout << "\t\t\tFilósofo " << id << " generó " << ideasGeneradas << " ideas y ahora se retira.\n";
    }

    // Método que retorna el número de ideas generadas por el filósofo
    int obtenerIdeasGeneradas() const {
        return ideasGeneradas;
    }
};

int main() {

    std::cout << "Inicia el proceso" << std::endl;
    const int numFilosofos = 5; // Número de filósofos
    vector<thread> hilosFilosofos; // Vector para almacenar los hilos de los filósofos
    vector<sem_t> tenedores(numFilosofos); // Vector para almacenar los semáforos (tenedores)
    vector<Filosofo> filosofos; // Vector para almacenar los objetos filósofos

    std::cout << "Iniciar los semaforos" << std::endl;
    // Inicializa los semáforos
    for (int i = 0; i < numFilosofos; ++i) {
        sem_init(&tenedores[i], 0, 1);
    }

    std::cout << "Crea los filosofos" << std::endl;
    // Crea a los filósofos
    for (int i = 0; i < numFilosofos; ++i) {
        filosofos.emplace_back(i + 1, &tenedores[i], &tenedores[(i + 1) % numFilosofos]);
    }

    std::cout << "Inicia los hilos de los filosofos" << std::endl;
    // Inicia los hilos de los filósofos
    for (int i = 0; i < numFilosofos; ++i) {
        hilosFilosofos.emplace_back(&Filosofo::cenar, &filosofos[i]);
    }

    std::cout << "Espera que todos los hilos termine" << std::endl;
    // Espera a que todos los hilos terminen
    for (auto &hilo : hilosFilosofos) {
        hilo.join();
    }

    std::cout << "calcula el total de ideas generadas" << std::endl;
    // Calcula el total de ideas generadas
    int totalIdeas = 0;
    for (const auto &filosofo : filosofos) {
        totalIdeas += filosofo.obtenerIdeasGeneradas();
    }

    // Muestra el total de ideas generadas en la mesa
    cout << "\t\t\tTotal de ideas generadas en la mesa: " << totalIdeas << endl;

    // Destruye los semáforos
    for (int i = 0; i < numFilosofos; ++i) {
        sem_destroy(&tenedores[i]);
    }

    return 0;
}
