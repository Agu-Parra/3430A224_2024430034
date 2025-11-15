#include <iostream>
#include <chrono> // Biblioteca para medir el tiempo
#include <cstdlib> // Biblioteca para funciones generales como atoi y rand
using namespace std;

//Copia los valores del arreglo inicio al arreglo final
void copyArreglo(int inicio[], int final[], int n){
    for(int i = 0; i<n; i++){ // recorre los indices del arreglo
        final[i] = inicio[i]; // copia el valor del arreglo inicio al final
    }
}

//Muestra los valores del arreglo
void mostrarArreglo(int arreglo[], int n){
    for(int i=0; i<n; i++){ // recorrer los indices del arreglo
        cout << "a[" << i << "] = " << arreglo[i] << " "; // muestra el valor del arreglo en el indice i
    }
    cout << "\n"; // salto de linea
}

//___________________________________METODOS_SEGUN_LAS_DIAPOSITIVAS____________________________________________________

// Compara pares de elementos consecutivos e intercambia si están desordenados
void bubbleSort(int arreglo[], int n){
    for(int i=1; i < n; i++){ // ciclo para n-1 pasadas
        for(int j = n-1; j >= i; j--){ // recorrer el arreglo desde el final hasta i
            if(arreglo[j-1] > arreglo[j]){ // intercambiar si el elemento actual es mayor que el siguiente
                int aux  = arreglo[j-1];
                arreglo[j-1] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }
}

// Ordena el arreglo desplazando hacia la derecha los elementos mayores al actual
void Insercion(int arreglo[], int n){
    for(int i=1; i<n; i++){ // recorrer desde el segundo elemento 
        int aux = arreglo[i]; // Guardar el valor actual
        int k  = i-1; // indice del elemento anterior
        while(k >=0 && aux < arreglo[k]){  // Desplaza elementos hacia la derecha mientras sean mayores que aux
            arreglo[k+1] = arreglo[k];
            k = k-1;
        }
        arreglo[k+1] = aux; // Insertar el valor actual en su posición correcta
    }
}

// Selecciona el elemento menor y lo intercambia con el elemento en la posición actual
void Seleccion(int arreglo[], int n){
    for(int i=0; i< n-1; i++){
        int k = i;
        int menor = arreglo[i];

        for(int j = i+1; j < n; j++){
            if(arreglo[j] < menor){
                menor = arreglo[j];
                k = j;
            }
        }
        int aux = arreglo[i];
        arreglo[i] = arreglo[k];
        arreglo[k] = aux;
    }
}

// Divide el arreglo en subarreglos y los ordena usando incrementos decrecientes
void shellSort(int arreglo[], int n){
    int x = n; // Tamaño inicial del intervalo
    while(x > 1){ // Mientras el intervalo sea mayor que 1
        x = x/2; // Reducir el intervalo a la mitad
        bool band = true;
        while(band == true){ // Repetir hasta que no haya intercambios
            band = false;

            int i = 0;
            while(i + x < n){ // comparar elementos separados por el intervalo x
                if(arreglo[i] > arreglo[i+x]){ // intercambiar si están desordenados
                    int aux = arreglo[i];
                    arreglo[i] = arreglo[i+x];
                    arreglo[i+x] = aux;
                    band = true; // se realizó un intercambio
                }
                i++; // avanzar al siguiente par de elementos
            }
        } 
    }
}

// Particiona el arreglo y retorna la posición del pivote
int Reduce(int arreglo[], int ini, int fin){
    int izq = ini; // límites del subarreglo
    int der = fin; // límites del subarreglo
    int pos = ini; // posición del pivote
    bool band = true;

    while(band == true){

        while(arreglo[pos] <= arreglo[der] && pos < der){ // mover der hacia la izquierda buscando un elemento menor que el pivote
            der = der - 1;
        }

        if(pos == der){
            band = false;
        } else { // intercambiar el pivote con el elemento en der
            int aux = arreglo[pos];
            arreglo[pos] = arreglo[der];
            arreglo[der] = aux;
            pos = der;

            while(arreglo[pos] >= arreglo[izq] && pos > izq){ // mover izq hacia la derecha buscando un elemento mayor que el pivote
                izq = izq + 1;
            }

            if(pos == izq){ // verificar si izq y pos se han encontrado
                band = false;
            } else { // intercambiar el pivote con el elemento en izq
                aux = arreglo[pos];
                arreglo[pos] = arreglo[izq];
                arreglo[izq] = aux;
                pos = izq; // actualizar la posición del pivote
            }
        }
    }
    return pos; // retornar la posición final del pivote

}

// Implementación iterativa de Quicksort usando dos pilas.
void quickSort(int arreglo[], int n){

    int pilamenor[100000]; //limites inferiores 
    int pilamayor[100000]; //limites superiores
    int tope = 1; // tope de las pilas
    pilamenor[tope] = 1; // límite inferior inicial
    pilamayor[tope] = n; // límite superior inicial

    while(tope > 0){ // mientras haya subarreglos por ordenar
        int ini = pilamenor[tope]; // obtener los límites del subarreglo
        int fin = pilamayor[tope]; // obtener los límites del subarreglo
        tope = tope -1; // reducir el tope de las pilas
        int pos = Reduce(arreglo, ini -1, fin-1); // particionar el subarreglo y obtener la posición del pivote
        pos = pos + 1; // ajustar la posición del pivote

        if(ini < pos -1){ // si hay elementos a la izquierda del pivote, agregar ese subarreglo a las pilas
            tope = tope +1;
            pilamenor[tope] = ini;
            pilamayor[tope] = pos - 1;
        }
        if(fin > pos +1){ // si hay elementos a la derecha del pivote, agregar ese subarreglo a las pilas
            tope = tope +1;
            pilamenor[tope] = pos +1;
            pilamayor[tope] = fin;
        }
    }
}

int main(int argc, char* argv[]){

    if(argc != 3){
        cout << "Uso: ./ejecutable N s(si) o n(no)" << endl;
        return 1;
    }

    int N = atoi(argv[1]);
    char ver = argv[2][0];

    if(N <= 0){
        cout << "N DEBE SER POSITIVO" << endl;
        return 1;
    }
// Reserva de memoria para los arreglos
    int* original = new int[N];
    int* copia = new int[N];
// Generar una semilla basada en el tiempo actual segun la guia del laboratorio
    std::chrono::high_resolution_clock::time_point seed = 
        std::chrono::high_resolution_clock::now();

    srand( seed.time_since_epoch().count() );

    // Generar datos aleatorios
    for (int i = 0; i < N; i++) {
        original[i] = rand() % 5000;
    }

    if (ver == 's') {
        mostrarArreglo(original, N);
        cout << "-----------------------------------------\n";
    }

    cout << "Metodo      | Tiempo\n";
    cout << "-----------------------------------------\n";

    // ---------------------------------- BURBUJA
    copyArreglo(original, copia, N);

    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    bubbleSort(copia, N);

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds tiempo_burbuja =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    cout << "Burbuja | " << tiempo_burbuja.count() << " milisegundos\n";
    if (ver == 's') mostrarArreglo(copia, N);


    // ---------------------------------- INSERCION
    copyArreglo(original, copia, N);

    t1 = std::chrono::high_resolution_clock::now();
    Insercion(copia, N);
    t2 = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds tiempo_ins =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    cout << "Insercion | " << tiempo_ins.count() << " milisegundos\n";
    if (ver == 's') mostrarArreglo(copia, N);


    // ---------------------------------- SELECCION
    copyArreglo(original, copia, N);

    t1 = std::chrono::high_resolution_clock::now();
    Seleccion(copia, N);
    t2 = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds tiempo_sel =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    cout << "Seleccion | " << tiempo_sel.count() << " milisegundos\n";
    if (ver == 's') mostrarArreglo(copia, N);


    // ---------------------------------- SHELLSORT
    copyArreglo(original, copia, N);

    t1 = std::chrono::high_resolution_clock::now();
    shellSort(copia, N);
    t2 = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds tiempo_shell =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    cout << "Shellsort | " << tiempo_shell.count() << " milisegundos\n";
    if (ver == 's') mostrarArreglo(copia, N);


    // ---------------------------------- QUICKSORT
    copyArreglo(original, copia, N);

    t1 = std::chrono::high_resolution_clock::now();
    quickSort(copia, N);
    t2 = std::chrono::high_resolution_clock::now();

    std::chrono::milliseconds tiempo_quick =
        std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    cout << "Quicksort | " << tiempo_quick.count() << " milisegundos\n";
    if (ver == 's') mostrarArreglo(copia, N);

// Liberar memoria
    delete[] original;
    delete[] copia;

    return 0;
}