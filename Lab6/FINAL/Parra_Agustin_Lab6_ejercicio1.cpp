#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

//DEFINIMOS UNA CONSTANTE QUE SEA EL INFINITO Y ADEMAS EL NUMERO MAXIMO DE NODOS QUE ACEPTAREMOS
#define INFINITO 9999 // = NO VE AL NODO

void inicializar_Matriz(int **matriz, int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            matriz[i][j] = INFINITO; // SALIDA UNA MATRIZ LLENA DE INFINITOS = 9999
        }
    }
}

void imprimir_Matriz(int **matriz, int n){
    cout << "MATRIZ INICIALIZADA" << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(matriz[i][j] == INFINITO){
                cout << "- "; // IMPRIMIMOS CADA ELEMENTO DE LA MATRIZ INICIALIZADA Y SI ES INFINITO IMPRIMIMOS UN GUION
            }else{
                cout << matriz[i][j] << " ";
            }
           
        }
        cout << endl;
    }
}

int nodo_Minimo(int *distancia, bool *visitado, int n){
    int min = INFINITO; //COMO NO SABES EL COSTO MINIMO, LO INICIALIZAS EN INFINITO
    int indice = -1; // INIDICE ES POR SI NO ENCUENTRA NINGUN NODO QUE NO HAYA SIDO VISITADO
    for(int i=0; i<n; i++){
        if(!visitado[i] && distancia[i] < min){ // SI EL NODO NO HA SIDO VISITADO Y SU DISTANCIA ES MENOR AL MINIMO ACTUAL
            min = distancia[i]; // ACTUALIZAMOS EL MINIMO
            indice = i; // ACTUALIZAMOS EL INDICE DEL NODO CON LA DISTANCIA MINIMA
        }
    }
    return indice; // RETORNAMOS EL INDICE DEL NODO CON LA DISTANCIA MINIMA
}

void generarArchivoGraphviz(int **M, int n) {
    ofstream archivo("grafo.dot");

    archivo << "digraph G {\n";
    archivo << "rankdir=LR;\n";
    archivo << "node [shape=circle style=filled fillcolor=\"#ff00f2ff\"];\n";

    // Escribir las aristas del grafo
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (M[i][j] != INFINITO && i != j) {
                archivo << i + 1 << " -> " << j + 1
                        << " [label=\"" << M[i][j] << "\"];\n";
            }
        }
    }

    archivo << "}\n";
    archivo.close();

    int resultado = system("dot -Tpng grafo.dot -o grafo.png");

    if (resultado == 0)
        cout << "grafo.png generada\n";
    else
        cout << " ERROR" << endl;
}



void Dijkstra(int **matriz, int origen, int n){
    int D[n];
    bool visitado[n];
    for(int i=0; i<n; i++){
        D[i] = INFINITO;
        visitado[i] = false;
    }

    D[origen] = 0; // LA DISTANCIA DEL NODO ORIGEN A SI MISMO ES CERO
    for(int i=0; i<n-1; i++){
        int a = nodo_Minimo(D, visitado, n); // OBTENEMOS EL NODO CON LA DISTANCIA MINIMA
        visitado[a] = true; //NODO VISITADO
        for(int x=0;x<n;x++){
            if(!visitado[x] && matriz[a][x] != INFINITO && D[a] + matriz[a][x] < D[x]){
                D[x] = D[a] + matriz[a][x];
            }
        }
    }

    cout << "Vecinos con menor costo: " << origen << endl;
    for(int i=0; i<n; i++){
        if(D[i] == INFINITO){
            cout << "NODO " << i + 1 << " NO VE A MI NODO" << endl;
        }else{
            cout << "NODO " << i+1 << " costo: " << D[i] << endl;

        }
    }

    generarArchivoGraphviz(matriz, n);

}

int main(int argc, char **argv){

    if(argc < 2){
        cout << "HABILITADO" << endl;
        return -1;
    }

    int n = atoi(argv[1]);
    if(n<=2){
        cout << "LA CANTIDAD DE NODOS DEBE SER MAYOR A 2" << endl;
        return 1;
    }

    //MATRIZ

        int **M = new int*[n];
    for (int i=0; i<n; i++)
        M[i] = new int[n];

    // leer datos
    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> M[i][j];
            if (M[i][j] == 0 && i != j)
                M[i][j] = INFINITO;
        }
    }

    imprimir_Matriz(M, n);

    int origen;
    cout << "\nIngrese el nodo origen (1-" << n << "): ";
    cin >> origen;
    Dijkstra(M, origen - 1, n);

    // liberar memoria
    for (int i=0; i<n; i++)
        delete[] M[i];
    delete[] M;

    return 0;
}





