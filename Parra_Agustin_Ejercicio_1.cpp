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
    cout << "-------------------------" << endl;


}

int main(){

    //FUNCIONES: MOSTRAR

    PACIENTE pacientes[3] ={

        {"Agustin Parra", 22, 78.5, 1.82},
        {"Juana De Arco", 19, 60.5, 1.61},
        {"Arturo Prat", 31, 75, 1.71}
    };

    for(int i=0; i<3; i++){
        MostrarInfo(pacientes[i]);
    }

  return 0;

}