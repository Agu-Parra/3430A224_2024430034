#include <iostream>
using namespace std;



double exponente(double x){
    return x*x;
}

void mostrar_exponente(double x){
    cout << "El exponente al cuadrado de " << x << " es " << exponente(x) << endl;
}

int main(){
    double numero;
    cout << "Ingrese un numero: ";
    cin >> numero;
    mostrar_exponente(numero);
    return 0;
}
    