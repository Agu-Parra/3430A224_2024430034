#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct NODO{
    float score;
    string funtion;
    string go;
    int fe;
    NODO* left;
    NODO* right;
    
};

NODO* creaNodo(string funtion, string go, float score ){

    NODO* nuevo_nodo = new NODO;
    nuevo_nodo -> funtion = funtion;
    nuevo_nodo -> go = go;
    nuevo_nodo -> score = score;
    nuevo_nodo -> fe = 0; // COMO NO HAY NODOS EL FACTOR DE EQUILIBRIO ES 0
    nuevo_nodo -> left = nullptr;
    nuevo_nodo -> right = nullptr;
    return nuevo_nodo;
}
int altura(NODO* nodo){
    if(nodo == nullptr){
        return 0;
    }
    int hizq  = altura(nodo -> left); //miramos la altura del subarbol izquierdo
    int hder = altura(nodo -> right); //miramos la altura del subarbol derecho
    if(hizq > hder){ // si la altura del subarbol izquierdo es mayor
        return hizq + 1; // devolvemos la altura del subarbol izquierdo + 1 (por el nodo actual)
    }
    return hder + 1; // si no, devolvemos la altura del subarbol derecho + 1 (por el nodo actual)
}
void actualizarFE(NODO* nodo){
    if(nodo != nullptr){
        nodo -> fe = altura(nodo -> right) - altura(nodo -> left); // calculamos el factor de equilibrio derecha - izquierda
    }
}
//#################################ROTACIONES GENERALES############################//
NODO* rotacionDerecha(NODO* nodo){
    NODO* aux = nodo -> left;
    nodo -> left = aux -> right;
    aux -> right = nodo;
    actualizarFE(nodo);
    actualizarFE(aux);
    return aux; 
}
NODO* rotacionIzquierda(NODO* nodo){
    NODO* aux = nodo -> right;
    nodo -> right = aux -> left;
    aux -> left = nodo;
    actualizarFE(nodo);
    actualizarFE(aux);
    return aux; 
}
//###################################################################################//

NODO* Balancear(NODO* nodo){
    actualizarFE(nodo);

    // Desbalance a la derecha
    if(nodo->fe == 2){
        if(nodo->right->fe < 0){ 
            nodo->right = rotacionDerecha(nodo->right); // DI
        }
        nodo = rotacionIzquierda(nodo); // II
    }

    // Desbalance a la izquierda
    if(nodo->fe == -2){
        if(nodo->left->fe > 0){ 
            nodo->left = rotacionIzquierda(nodo->left); // ID
        }
        nodo = rotacionDerecha(nodo); // DD
    }

    return nodo;
}

NODO* insertar(NODO* &nodo, string funtion, string go, float score){
    if(nodo == nullptr){
        nodo = creaNodo(funtion, go, score);
        return nodo;
    }
    if(go < nodo -> go){
        nodo -> left = insertar(nodo -> left, funtion, go, score);

    }else if(go > nodo -> go){
        nodo -> right = insertar(nodo -> right, funtion, go, score);
    }else{
        cout << "El nodo con go " << go << " ya existe en el arbol." << endl;
    }

    return Balancear(nodo);
}

NODO* Buscar(NODO* nodo, string go){
    if(nodo == nullptr){
        return nullptr;
    }
    if(nodo -> go == go){
        return nodo;
    }
    if(go < nodo -> go){
        return Buscar(nodo -> left, go);
    }else{
        return Buscar(nodo -> right, go);
    }
}

// Para un mayor orden imprimo el arbol en posorden
void imprimirPosOrden(NODO* nodo){
    if(nodo == nullptr) return;
    imprimirPosOrden(nodo -> left);
    imprimirPosOrden(nodo -> right);
    cout << "Funcion: " << nodo -> funtion << ", GO: " << nodo -> go << ", Score: " << nodo -> score << endl;
}

void Dot(NODO* nodo, ofstream &archivo) {
    if (nodo == nullptr)
        return;

   
    archivo << "\"" << nodo->go << "\" [label=\""
            << nodo->go << "\\nFE=" << nodo->fe
            << "\", shape=box];\n";

    //hijo izquierdo
    if (nodo->left != nullptr) {
        archivo << "\"" << nodo->go << "\" -> \"" << nodo->left->go << "\";\n";
        Dot(nodo->left, archivo);
    } else {
        // Si no tiene hijo izquierdo, agrega un punto 
        archivo << "\"" << nodo->go << "i\" [shape=point];\n";
        archivo << "\"" << nodo->go << "\" -> \"" << nodo->go << "i\";\n";
    }

    // hijo derecho
    if (nodo->right != nullptr) {
        archivo << "\"" << nodo->go << "\" -> \"" << nodo->right->go << "\";\n";
        Dot(nodo->right, archivo);
    } else {
        archivo << "\"" << nodo->go << "d\" [shape=point];\n";
        archivo << "\"" << nodo->go << "\" -> \"" << nodo->go << "d\";\n";
    }
}

void leerCSV(NODO* &raiz, const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string linea;
    getline(archivo, linea); 

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;


        size_t pos1 = linea.find(';'); //SEPARADOR ; POR EL CSV
        size_t pos2 = linea.find(';', pos1 + 1); //SEPARADOR ; POR EL CSV

        string go = linea.substr(0, pos1);
        string funcion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string scoreStr = linea.substr(pos2 + 1);

        if (go.empty()) continue;

        float score = stof(scoreStr);
        raiz = insertar(raiz, funcion, go, score);
    }

    cout << "Archivo cargado exitosamente." << endl;
}
void liberarArbol(NODO* &nodo) {
    if (nodo == nullptr) return;

    liberarArbol(nodo->left);
    liberarArbol(nodo->right);
    delete nodo;
    nodo = nullptr;
}


void Menu(){

    int opcion;
    NODO* raiz = nullptr;
    string go, funcion;
    float score;

    do{
        cout << "___________________MENU ___________________" << endl;
        cout << "1. Cargar CSV" << endl;
        cout << "2. Insertar nodo" << endl;
        cout << "3. Mostrar arbol" << endl;
        cout << "4. Buscar nodo" << endl;
        cout << "5. Generar archivo Graphviz" << endl;
        cout << "6. Salir" << endl;

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch(opcion){
            case 1:
                leerCSV(raiz, "data.csv");
                break;
            case 2:
                cout << "Ingrese GO: ";
                cin >> go;
                cout << "Ingrese Funcion: ";
                cin >> funcion;
                cout << "Ingrese Score: ";
                cin >> score;
                raiz = insertar(raiz, funcion, go, score);
                break;
            case 3:
                cout << "Impresion: " << endl;
                imprimirPosOrden(raiz);
                break;
            case 4:{
                cout << "Ingrese el GO a buscar: ";
                cin >> go;
                NODO* encontrado = Buscar(raiz, go);
                if(encontrado != nullptr){
                    cout << "Nodo encontrado - Funcion: " << encontrado -> funtion << ", GO: " << encontrado -> go << ", Score: " << encontrado -> score << endl;
                }else{
                    cout << "Nodo con GO " << go << " no encontrado." << endl;
                }
                break;
            }
            case 5:
               {
                ofstream archivo("grafo.txt");
                archivo << "digraph G {\nnode [style=filled fillcolor=tomato shape=box];\n"; //lightskyblue 
                Dot(raiz, archivo);
                archivo << "}\n";
                archivo.close();
                system("dot -Tpng -ografo.png grafo.txt");
                cout << "Grafo generado en 'grafo.png'\n";
                break;
            }
            case 6:
                cout << "SALIENDO DEL PROGRAMA..." << endl;
                liberarArbol(raiz);
                break;
            default:
                cout << "OPCION INVALIDA" << endl;
        }
    }while(opcion != 6);
}

int main(int argc, char** argv) {
    NODO* raiz = nullptr;

    if (argc > 1) {
        string archivo = argv[1];
        leerCSV(raiz, archivo);
    }

    Menu();
    return 0;
}