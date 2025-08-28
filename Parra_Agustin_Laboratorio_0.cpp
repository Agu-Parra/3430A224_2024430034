#include <iostream>
using namespace std;

//FUNCION PARA VERIFICAR PAR O IMPAR
int Par(){
    int numero;
    cout << "Ingrese un numero: " << endl;
    cin >> numero;
    cout << "____________________________ " << endl;
    cout << " " << endl;
    cout << "(NUMERO INGRESADO " << numero << ")" << endl;
    cout << "____________________________" << endl;

    if(numero % 2 == 0){
        cout << " " << endl;
        cout << "El numero es par" << endl;
        cout << "____________________________ " << endl;
    }else{
        cout << " " << endl;
        cout << "El numero es impar" << endl;
        cout << "____________________________ " << endl;
    }
    for(int i = 1; i <= 10; i++){
        if(i % 2 == 0){
            cout << i << " es par" << endl;
        }else{
            cout << i << " es impar" << endl;
        }
    }
    return numero;
}

//FUNCION DE CONTAR 
int cadena(string texto){
    int j = 0;
    for(int i = 0; texto[i] != '\0'; i++){ //en esta parte leo la longitud de la cadena
        j++;
    }
    return j;
}
int main() {

    //DECIDI HACER UN MENU PARA QUE LA PERSONA TENGA LA OPCION DE CONTAR UNA PALABRA 
    //O VERIFICAR SI UN NUMERO ES PAR O IMPAR

    //MENU
    int opcion = 0;
    while(opcion != 3){
        cout << "____________MENU_______________" << endl;

        cout << "1. Par o Impar" << endl;
        cout << "2. longitud de Cadena" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        if(opcion == 1) {
            Par();

        }else if(opcion == 2){
            string palabra;
            cout << "Ingrese una palabra: ";
            cin >> palabra;

            cout << "La longitud de la palabra '" << palabra << "' es: " << cadena(palabra) << endl;
            string textofijo = "esternocleidomastoideo";
            cout << "La longitud de la palabra '" << textofijo << "' es: " << cadena(textofijo) << endl;

        }else if(opcion == 3){
            cout << "SALIENDO........." << endl;
            break;

        }else{
            cout << "OPCION INVALIDA" << endl;
        }

    }

    return 0;
}