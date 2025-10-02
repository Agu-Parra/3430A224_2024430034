#include <iostream> 
#include <string>
using namespace std;



struct NODO{

    string nombre;
    string carrera;
    float promedio;
    NODO* siguiente;
  
};
bool Vacia(NODO* frente){
    return (frente == nullptr);
}

void insertar(NODO*& frente, NODO*& final, string nombre, string carrera, float promedio){
    NODO* nuevo_nodo = new NODO();
    nuevo_nodo -> nombre = nombre;
    nuevo_nodo -> carrera = carrera;
    nuevo_nodo -> promedio = promedio;
    nuevo_nodo -> siguiente = nullptr;
    if(Vacia(frente)){
        frente = nuevo_nodo;
        final = nuevo_nodo; 
    }else{
        final -> siguiente = nuevo_nodo;
        final = nuevo_nodo;
    }
    cout << "Estudiante " << nombre << " se ha agregado" << endl;
}

void eliminar(NODO*& frente, NODO*& final, string &nombre, string &carrera, float &promedio){
    if(Vacia(frente)){
        cout << "La cola esta vacia" << endl;
    }else{
        NODO* auxiliar = frente;
        nombre = auxiliar -> nombre;
        carrera = auxiliar -> carrera;
        promedio = auxiliar -> promedio;
        frente = frente -> siguiente;
        delete auxiliar;
        if(frente == nullptr){      
            final = nullptr;
        }
        cout << "El estudiante " << nombre << " ha sido eliminado" << endl;
    }
}

void mostrar(NODO* frente){
    if(Vacia(frente)){
        cout << "La cola esta vacia" << endl;
    }else{
        NODO* actual = frente;
        int pos = 1;
        cout << "Contenido\n";
        while(actual != nullptr){
            cout << pos << "-" << actual -> nombre << " | " << actual -> carrera << " | PROMEDIO: " << actual -> promedio << endl;
            actual = actual -> siguiente;
            pos++;  
        }
    }
}

void liberar(NODO*& frente, NODO*& final){
    while(frente != nullptr){
        NODO* auxiliar = frente;
        frente = frente -> siguiente;
        delete auxiliar;
    }
    final = nullptr;
}



void menu(){

    NODO* frente = nullptr;
    NODO* final = nullptr;
    int opcion;
    string nombre, carrera;
    float promedio;

    do{
        cout << "\n___________MENU__________\n";
        cout << "1. Ingresar estudiante\n";
        cout << "2. Eliminar estudiante\n";
        cout << "3. Mostrar estudiantes\n";
        cout << "4. Salir\n";
        cout << "INGRESE UNA OPCION: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                cout << "Ingrese el nombre del estudiante" << endl;
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la carrera del estudiante" << endl;
                getline(cin, carrera);
                cout << "Ingrese el promedio del estudiante" << endl;
                cin >> promedio;
                insertar(frente, final, nombre, carrera, promedio);
                break;
            case 2:
                eliminar(frente, final, nombre, carrera, promedio);
                break;
            case 3:
                mostrar(frente);
                break;
            case 4:
                cout << "Saliendo..." << endl;
                liberar(frente, final);
                break;
            default:
                cout << "Opcion invalida" << endl;
        }
    }while(opcion != 4);
}



int main(){

    menu();
    return 0;
}