#include <iostream>
#include <string>
#include <fstream> // CON ESTA BIBLIOTCA PUEDO EXPORTAR A UN ARCHIVO TXT
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

void PromedioEdad(const NODO* head){

    int sumaEdad = 0;
    int contador = 0;
    const NODO* cur = head;
    while(cur){
        sumaEdad += cur -> paciente.edad;
        ++contador;
        cur = cur -> next;
    }
    cout << "PROMEDIO DE EDAD: " << int(sumaEdad) / contador << endl;
}

void PromedioPeso(const NODO* head){
    
    int sumaPeso = 0;
    int contador = 0;
    const NODO* cur =  head;
    while(cur){
        sumaPeso += cur -> paciente.peso;
        ++contador;
        cur = cur -> next;
    }
    cout << "PROMEDIO DE PESO: " << float(sumaPeso) / contador << endl;
}

void CalcularIMC(const NODO* head){

    float imc = 0.0;
    const NODO* cur = head;
    while(cur){
        imc = cur -> paciente.peso / (cur -> paciente.altura * cur -> paciente.altura);
        cout << "IMC de: " << cur -> paciente.nombre << " es: " << imc << endl;
        cur = cur -> next;
    }
}

void ExportarTXT(const NODO* head, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    const NODO* cur = head;
    while (cur) {
        archivo << "Nombre: " << cur->paciente.nombre << "\n";
        archivo << "Edad: " << cur->paciente.edad << "\n";
        archivo << "Peso: " << cur->paciente.peso << "\n";
        archivo << "Altura: " << cur->paciente.altura << "\n";
        archivo << "--------------------------\n";
        cur = cur->next;
    }

    archivo.close();
    cout << "Pacientes exportados a " << nombreArchivo << endl;
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

//FUNCION MENU
void MENU(){

    NODO* lista = nullptr;

    int opcion = 0;
    while(opcion != 6){
        cout << "+________________MENU_________________+" << endl;
        cout << "(1) Agregar un Paciente" << endl;
        cout << "(2) Mostar Pacientes" << endl;
        cout << "(3) Mostrar promedio de edad" << endl;
        cout << "(4) Mostar promedio de peso" << endl;
        cout << "(5) Mostar IMC de los pacientes" << endl;
        cout << "(6) Eliminar pacientes(empezando del 0)" << endl; 
        cout << "(7) Exportar archivo txt" << endl;
        cout << "(8) SALIR\n" << endl;
        cout << "ELIGE UNA OPCION: ";
        cin >> opcion;

        if(opcion == 1){
            PACIENTE p;
            cout << "NOMBRE: ";
            cin.ignore();
            getline(cin, p.nombre);
            cout << "EDAD: ";
            cin >> p.edad;
            cout << "PESO: ";
            cin >> p.peso;
            cout << "ALTURA: ";
            cin >> p.altura;
            Insertar(lista,p);  
        }else if(opcion == 2){
            Mostrar(lista);
        }else if(opcion == 3){
            PromedioEdad(lista);
        }else if(opcion == 4){
            PromedioPeso(lista);
        }else if(opcion == 5){
            CalcularIMC(lista);
        }else if(opcion == 6){
            int pos = 0;
            cout << "Ingrese un paciente a eliminar" << endl;
            cin >> pos;
            if(Eliminar(lista, pos)){
                cout << "PACIENTE ELIMINADO" << endl;
            }else{
                cout << "No se puede eliminar al paciente" << endl;
            }

        }else if(opcion == 7){
            ExportarTXT(lista, "paciente.txt");
        }else if(opcion == 8){
            LiberarMemoria(lista);
            cout << "SALIENDO...... " << endl;
            break; 
        }else{
            cout << "OPCION INVALIDA" << endl;
        }

    }
}

//FUNCION PRINCIPAL
int main(){
    MENU();
    return 0;
} 