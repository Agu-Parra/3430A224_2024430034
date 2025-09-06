#include <iostream>
using namespace std;

struct PACIENTE{

    char nombre[50];
    int edad; 
    float peso;
    float estatura;

};

void MostrarInfo(PACIENTE paciente){

    cout << "NOMBRE: " << paciente.nombre << endl;
    cout << "EDAD: " << paciente.edad << " años" << endl;
    cout << "PESO: " << paciente.peso << " Kg" << endl;
    cout << "ESTATURA: " << paciente.estatura << " m" << endl;

}

int main(){

        //FUNCIONES: MOSTRAR
    PACIENTE paciente1 ={"Agustin Parra", 22, 78.5, 1.82};
    PACIENTE paciente2 ={"Juana De Arco", 19, 60.4, 1.60};
    PACIENTE paciente3 = {"Arturo Prat", 31, 75, 1.71};

    MostrarInfo(paciente1);
    MostrarInfo(paciente2);
    MostrarInfo(paciente3);
    return 0;
}