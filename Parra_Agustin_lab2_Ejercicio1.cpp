#include <iostream>
#include <string>  
using namespace std;


struct PILA{
    int max;
    int tope;
    bool band;
    string remedios[100];
    
};
bool Pila_vacia(int tope, bool &band){
    if(tope == 0) band = true;
    else band = false;
    return band;
}
bool Pila_llena(int tope, int max, bool &band){
    if(tope == max) band = true;
    else band = false;
    return band;
}
void Push(bool &band, int &tope, int max, string remedios[], string dato){
    Pila_llena(tope, max, band);
    if(band == true){
        cout << "DESBORDAMIENTO" << endl; 
    }else if(band == false){
        tope = tope +1;
        remedios[tope] = dato;
        cout << "AGREGADO: " <<  dato << endl;
    }
}
string Pop(string remedios[], int &tope, bool &band){
    Pila_vacia(tope, band);

    if(band == true ){
        cout << "subdesbordamiento" << endl;
        return "";
    }else if( band == false){
        string dato = remedios[tope];
        tope = tope - 1;
        cout << "REMEDIO RETIRADO" << endl;
        return dato;
    }
    return "";
}
void Mostrar(string remedios[], int tope){

    if(tope == 0){
        cout << "No hay remedios registrados" << endl;
    }else{
        cout << "REMEDIOS:\n";
        for(int i = tope; i >= 1; i--) {
            cout << "-" << remedios[i] << endl;
        }
    }
}
void MENU(){
    PILA pila;
    pila.max = 100;
    pila.tope = 0;
    pila.band = false;

    int opcion;
    string nombre;
    do{
        cout << "____________MENU______________\n";
        cout << "(1) Agregar Remedio(PUSH)" << endl;
        cout << "(2) Eliminar Remedio(POP)" << endl;
        cout << "(3) Mostrar remedio/s" << endl;
        cout << "(4) SALIR" << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion; 

        switch (opcion){

            case 1:
                cout << "Ingrese el remedio a registrar" << endl;
                cin.ignore();
                getline(cin, nombre);
                Push(pila.band,pila.tope,pila.max,pila.remedios, nombre);
                break;
            case 2:
                Pop(pila.remedios, pila.tope, pila.band);
                break;
            case 3:
                Mostrar(pila.remedios, pila.tope);
                break;
            case 4:
                cout << "SALIENDO............" << endl;
                break;
            default:
                cout << "OPCION INVALIDA" << endl;

        }  

    }while(opcion != 4);
}
int main(){

    MENU();
    return 0;
}