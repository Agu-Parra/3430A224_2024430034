#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

#define INFINITO 9999 // = NO VE AL NODO es el infinito en la tabla

void imprimir_Matriz(int **matriz, int n){
    cout << "MATRIZ INICIALIZADA" << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(matriz[i][j] == INFINITO){
                cout << "- ";
            }else{
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int camino_Minimo(int *distancia, bool *visitado, int n){

    int min = INFINITO;
    int indice = -1;
    for(int i=0; i<n; i++){
        if(!visitado[i] && distancia[i] < min){
            min = distancia[i];
            indice = i;
        }
    }
    return indice;
}

void generarArchivoGraphviz(int **M, int n) {
    ofstream archivo("grafo.dot");

    archivo << "graph G {\n";         
    archivo << "rankdir=LR;\n";
    archivo << "node [shape=circle style=filled fillcolor=\"#5ef873ff\"];\n";

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {  
            if (M[i][j] != INFINITO && i != j) {
                archivo << i + 1 << " -- " << j + 1
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


void Prim(int **matriz, int n){

    int costo_min[n];
    bool nodo_incluido[n];
    int guardado[n];

    for(int i=0; i<n; i++){
        costo_min[i] = INFINITO;
        nodo_incluido[i] = false;
        guardado[i] = -1;
    }

    //NODO INICIAL
    costo_min[0] = 0;   
    for(int i=0; i<n-1; i++){
        int a = camino_Minimo(costo_min, nodo_incluido, n);
        nodo_incluido[a] = true;
        for(int x=0; x<n; x++){
            if(!nodo_incluido[x] && matriz[a][x] != INFINITO && matriz[a][x] < costo_min[x]){
                costo_min[x] = matriz[a][x];
                guardado[x] = a;
            }
        }
    }

    cout << "Nodos del grafo de costo minimo: " << endl;
    for(int i=1; i<n; i++){
        cout << "Nodo " << guardado[i] + 1 << " - Nodo " << i + 1 << " Costo: " << costo_min[i] << endl;
    }
    generarArchivoGraphviz(matriz, n);
}

int main(int argc, char** argv){

    if(argc != 2){
        cout << "ERROR numero de nodos no especificado" << endl;
        return -1;
    }

    int n = atoi(argv[1]);

    int **matriz = new int*[n];
    for(int i=0; i<n; i++){
        matriz[i] = new int[n];
    }
    cout << "Ingrese la matriz de adyacencia: " << n << "x" << n << endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> matriz[i][j];
            if(matriz[i][j] == 0 && i != j){
                matriz[i][j] = INFINITO;
            }
        }
    }
    
    imprimir_Matriz(matriz, n);

    Prim(matriz, n);

    for(int i=0; i<n; i++){
        delete[] matriz[i];
    }
    delete[] matriz;

    return 0;
}
