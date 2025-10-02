#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct NODO{

    string resn;
    string resid;
    bool agregado;  //SOLO PARA EXPORTAR UN PNG CON AMINOACIDOS AGREGADOS POR EL USUARIO   
    NODO* siguiente;
};
bool Vacia(NODO* frente){
    return (frente == nullptr);
}  

void Insertar(NODO*& frente, NODO*& final, string resn, string resid, bool agregado = true){
    NODO* nuevo_nodo = new NODO();
    nuevo_nodo -> resn = resn;
    nuevo_nodo -> resid = resid;
    nuevo_nodo -> agregado = agregado;
    nuevo_nodo -> siguiente = nullptr;
    if(Vacia(frente)){
        frente = nuevo_nodo;
        final = nuevo_nodo;
    }else{
        final -> siguiente = nuevo_nodo;
        final = nuevo_nodo;
    }
    cout << "Aminoacido " << resn << " agregado" << endl;
}

void Eliminar(NODO*& frente, NODO*& final, string &resn, string &resid){
    if(Vacia(frente)){
        cout << "No hay aminoacidos agregados" <<endl;
    }else{
        NODO* auxiliar = frente;
        resn = auxiliar -> resn;
        resid = auxiliar -> resid;
        frente = frente -> siguiente;
        delete auxiliar;
        if(frente == nullptr){
            final = nullptr;
        }
        cout << "Aminoacido " << resn << " eliminado" << endl;
    }
}
void Mostrar(NODO* frente){
    if(Vacia(frente)){
        cout << "No hay aminoacidos agregados" << endl;
    }else{
        NODO* actual = frente;
        int pos = 1;
        cout << "Contenido\n";
        while(actual != nullptr){
            cout << pos << "-" << actual -> resn << " | " << actual -> resid << endl;
            actual = actual -> siguiente;
            pos++;
        }
    }
}

void leerArchivo(const string& nombreArchivo, NODO*& frente, NODO*& final) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "No se pudo abrir el archivo " << nombreArchivo << endl;
        return;
    }

    string resn, resid;

    while (archivo >> resn >> resid) {
        Insertar(frente, final, resn, resid, false); //SE VALIDA AQUI EL BOOL AGREGADO
    }

    archivo.close();
    cout << "Cola cargada.\n";
}
void EliminarResid(NODO*& frente, NODO*& final, int posicion){
    if(Vacia(frente) || posicion < 1){
        cout << "No hay aminoacidos agregados o posicion invalida" << endl;
        return;
    }
    NODO* actual = frente; 
    if(posicion == 1){
        frente = actual -> siguiente;
        delete actual;
        cout << "Aminoacido en posicion " << posicion << " eliminado" << endl;
        return;
    }
    NODO* anterior = nullptr;
    int contador = 1;
    while(actual != nullptr && contador < posicion){
        anterior = actual;
        actual = actual -> siguiente;
        contador++;
    }
    if(actual == nullptr){
        cout << "Posicion fuera de rango" << endl;
        return;
    }
    anterior -> siguiente = actual -> siguiente;
    if(anterior -> siguiente == nullptr){
        final = anterior;
    }
    delete actual;
    cout << "Aminoacido en posicion " << posicion << " eliminado" << endl;
    return; 
}
void liberar(NODO*& frente, NODO*& final){
    while(frente != nullptr){
        NODO* auxiliar = frente;
        frente = frente -> siguiente;
        delete auxiliar;
    }
    final = nullptr;
}
void Graphviz(NODO* frente) {
    bool hayAgregados = false;
    ofstream archivo("cola.dot");
    archivo << "digraph G {\n";
    archivo << "rankdir=LR;\n";  
    archivo << "node [style=filled, fillcolor=yellow];\n";

    NODO* actual = frente;
    NODO* anteriorAgregado = nullptr;

    while (actual != nullptr) {
        if (actual->agregado) {
            string nodoActual = actual->resn + actual->resid;
            hayAgregados = true;
            if (anteriorAgregado != nullptr) {
                string nodoAnterior = anteriorAgregado->resn + anteriorAgregado->resid;
                archivo << nodoAnterior << " -> " << nodoActual << ";\n";
            } else {
                archivo << nodoActual << ";\n"; // primer agregado
            }
            anteriorAgregado = actual;
        }
        actual = actual->siguiente;
    }

    archivo << "}\n";
    archivo.close();

    if (hayAgregados) {
        system("dot -Tpng cola.dot -o cola.png");
        cout << "Archivo cola.png generado SOLO con aminoácidos agregados.\n";
    } else {
        cout << "No hay aminoácidos agregados por el usuario.\n";
    }
}


void Modificar(NODO* frente, int posicion, const string& newresid, const string& newrsn){
    if(Vacia(frente) || posicion < 1){
        cout << "No hay aminoacidos agregados o posicion invalida" << endl;
        return;
    }
    NODO* actual = frente;
    int contador = 1;
    while(actual != nullptr && contador < posicion){
        actual = actual -> siguiente;
        contador ++;
    }
    if(actual == nullptr){
        cout << "Posicion fuera de rango" << endl;
        return;
    }
    actual -> resid = newresid;
    actual -> resn = newrsn;
    cout << "Aminoacido en posicion " << posicion << " modificado" << endl;
    
}

void MENU(){

    NODO* frente = nullptr;
    NODO* final = nullptr;
    int opcion;
    string resn, resid;
    int pos;
    string newresn, newresid;
    leerArchivo("1TAU.RESIDS.A.UNIQ.txt", frente, final);
    
    do{

        cout << "\n___________MENU__________\n";
        cout << "1. Insertar aminoacido\n";
        cout << "2. Eliminar aminoacido\n";
        cout << "3. Mostrar aminoacidos\n";
        cout << "4. Eliminar aminoacido en posicion especifica\n";
        cout << "5. Modificar aminoacido en posicion especifica\n";
        cout << "6. Generar archivo Graphviz\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                cout << "Ingrese el nombre del aminoacido: ";
                cin >> resn;
                cout << "Ingrese el ID del aminoacido: ";
                cin >> resid;
                Insertar(frente, final, resn, resid);
                break;
            case 2:
                Eliminar(frente, final, resn, resid);
                break;
            case 3:
                Mostrar(frente);
                break;

            case 4:
                cout << "Ingrese la posicion del aminoacido a eliminar: ";
                cin >> pos;
                EliminarResid(frente, final, pos);
                break;
            case 5:
                cout << "Ingrese la posicion del aminoacido a modificar: ";
                cin >> pos;
                cout << "Ingrese el nuevo nombre del aminoacido: ";
                cin >> newresn;
                cout << "Ingrese el nuevo ID del aminoacido: ";
                cin >> newresid;
                Modificar(frente, pos, newresid, newresn);
                break;
            case 6:
                Graphviz(frente);
                break;
            case 7:
                liberar(frente, final);
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    }while(opcion != 7);
}
int main(){
    MENU();
    return 0;
}