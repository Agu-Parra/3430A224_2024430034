#include <iostream>
#include <string>
using namespace std;

struct PACIENTE{

    string nombre;
    int edad;
    float peso;
    float altura;
};
struct NODO{

    PACIENTE paciente;
    NODO* next;
};

//FUNCION DONDE ME CREA UN PACIENTE Y LO DEVUELVE
NODO* Crear(const PACIENTE& p){

    NODO* n = new NODO; 
    n -> paciente = p;
    n -> next = nullptr;
    return n;
} 

//FUNCION DONDE INSERTO UN PACIENTE AL FINAL DE LA LISTA
void Insertar(NODO*& head, const PACIENTE& p){

    NODO* n = Crear(p);
    if(head==nullptr){
        head = n;
        return;
    }
    NODO* cur = head;
    while(cur -> next) cur = cur -> next;
    cur -> next = n;
}

//FUNCION DONDE MUESTRO LOS PACIENTES ALMACENADOS EN LA LISTA
void Mostrar(const NODO* head){

    cout << "__________PACIENTES__________" << endl;
    const NODO* cur = head;
    int pos = 0;
    while(cur){
        cout << "NOMBRE: " << cur -> paciente.nombre << endl;
        cout << "EDAD: " << cur -> paciente.edad << endl;
        cout << "PESO: " << cur -> paciente.peso << endl;
        cout << "ALTURA: " << cur -> paciente.altura << endl;
        cout <<"_________________________________" << endl;
        cur = cur -> next;
        ++pos;
    }
    if(pos == 0) cout << "LA LISTA ESTA VACIA" << endl;
}

//FUNCION DONDE ELIMINO UN PACIENTE DE LA LISTA
bool Eliminar(NODO*& head, int pos){
    if(!head || pos < 0) return false;
    if(pos == 0){
        NODO* temp = head;
        head = head -> next;
        delete temp;
        return true;
    }
    NODO* cur = head;
    for(int i=0; cur && i<pos -1; ++i){
        cur = cur -> next;
    }
    if(!cur || !cur -> next ) return false;
    NODO* borrar = cur -> next;
    cur -> next = cur -> next -> next;
    delete borrar;
    return true;
}

//FUNCION DONDE LIBERO LA MEMORIA DE LA LISTA
void LiberarMemoria(NODO*& head){
    while(head){
        NODO* temp = head;
        head = head -> next;
        delete temp;
    }
}

//FUNCION PRINCIPAL
int main(){

    NODO* lista = nullptr;
    PACIENTE p1 = {"Agustin Parra", 20, 79.5, 1.82}; //CREO UN PACIENTE1
    Insertar(lista, p1); //LO INSERTO EN LA LISTA
    PACIENTE p2 = {"Juana de Arco", 19, 65.3, 1.70}; //CREO UN PACIENTE2
    Insertar(lista, p2); //LO INSERTO EN LA LISTA
    PACIENTE p3 = {"Arturo Prat", 31, 75.0, 1.75}; //CREO UN PACIENTE3
    Mostrar(lista); //MUESTRO LA LISTA CON LOS PACIENTES 1 Y 2

    Insertar(lista, p3); //INSERTO EL PACIENTE 3
    Mostrar(lista); //MUESTRO LA LISTA CON LOS 3 PACIENTES
    Eliminar(lista, 0); //ELIMINO EL PACIENTE EN LA POSICION 0 (AGUSTIN PARRA)
    Mostrar(lista); //MUESTRO LA LISTA CON LOS PACIENTES 2 Y 3
    LiberarMemoria(lista); //LIBERO LA MEMORIA DE LA LISTA
    return 0;
} 