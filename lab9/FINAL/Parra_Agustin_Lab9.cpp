#include <iostream>
using namespace std;

const int maximo = 20; // COMO SON 20 DATOS TOTALES PEDIDOS DEFINO EL MAXIMO DE LA TABLA

//OCUPO UNA ESTRUCTURA POR EL ENCADENAMIENTO QUE OCUPA LISTA ENLAZADAS
struct NODO{
    int clave; //valor de la clave
    NODO* siguiente;
};

void inicializacionTabla(int tabla[]){
    for(int i=0; i<maximo; i++){
        tabla[i] = -1; // tabla vacia
    }
}

void inicializarLista(NODO* lista[]){
    for(int i=0; i<maximo; i++){
        lista[i] = nullptr; // lista vacia 
    }
}

//____________________FUNCIONES HASH________________________

int hashing1(int k){ //HASHING MODULO
    return (k % maximo); 
}

int hashing2(int k){ //HASHING PLEGAMIENTO
    int suma = 0;
    while(k > 0){
        suma += k % 10;
        k /= 10;
    }
    return suma % maximo;
}

//_______________________TABLA DE HASHING_________________________

void imprimirTabla(int tabla[]){

    cout << "########### TABLA DE HASHING ###########" << endl;
    for(int i=0; i<maximo; i++){
        if(tabla[i] != -1){
            cout << "Indice: " << i << " -> Clave: " << tabla[i] << endl;
        } else {
            cout << "Indice: " << i << " -> Vacio" << endl;
        }
    }
}

void imprimirLista(NODO* lista[]){
    cout << "########### ENCADENAMIENTO ###########" << endl;
    for(int i=0 ; i<maximo; i++){
        if(lista[i] != nullptr){
            cout << "INDICE: " << i << " -> ";
            NODO* actual = lista[i];
            while(actual != nullptr){ 
                cout << actual->clave << " -> ";
                actual = actual->siguiente;
            }
            cout << "nulo" << endl;
        }
    }
}

//________________________SOLUCIONES DE COLISIONES_________________________

void pruebaLineal(int tabla[], int clave){ // AVANZAR 1 EN 1
    int posicion = hashing1(clave); // Calculo de la posicion inicial
    for(int i=0; i<maximo; i++){ 
        int nuevaPosicion = (posicion + i) % maximo; 
        if(tabla[nuevaPosicion] == -1){ // Si la posicion esta vacia
            tabla[nuevaPosicion] = clave; // Insertar la clave en la posicion
            if(i > 0){
                cout << "Colision ocurrida. Clave " << clave << " insertada en la posicion " << nuevaPosicion << " despues de " << i << " intentos." << endl;
            }
            return; // Salir de la funcion despues de insertar
        }
    }
    cout << "Tabla de hash llena. No se pudo insertar la clave " << clave << "." << endl;   
}

void pruebacuadratica(int tabla[], int clave){ // AVANZAR EN CUADRADOS(i*i)

    int posicion = hashing1(clave);
    for(int i=0; i<maximo; i++){
        int nuevaposi = (posicion + i*i) % maximo;
        if(tabla[nuevaposi] == -1){ // Si la posicion esta vacia
            tabla[nuevaposi] = clave; // Insertar la clave en la posicion
            if(i>0){ // Si hubo colision
                cout << "Colision ocurrida. Clave " << clave << " insertada en la posicion " << nuevaposi << " despues de " << i << " intentos." << endl;
            }
            return;
        }
    }
    cout << "Tabla de hash llena. No se pudo insertar la clave " << clave << "." << endl;   
}
    
void pruebadobleInserccion(int tabla[], int clave){
    int posicion = hashing1(clave); // Calculo de la posicion inicial
    int salto = hashing2(clave); // Calculo del salto
    for(int i=0; i<maximo; i++){
        int nuevaposi = (posicion + i*salto) % maximo;
        if(tabla[nuevaposi] == -1){ // Si la posicion esta vacia
            tabla[nuevaposi] = clave; // Insertar la clave en la posicion
            if(i>0){ // Si hubo colision
                cout << "Colision ocurrida. Clave " << clave << " insertada en la posicion " << nuevaposi << " despues de " << i << " intentos." << endl;
            }
            return;
        }
    }
    cout << "Tabla de hash llena. No se pudo insertar la clave " << clave << "." << endl;   
}

void pruebaEncadenamiento(NODO* lista[], int clave){
    int posicion = hashing1(clave);
    if(lista[posicion] != nullptr){ // Si ya hay un nodo en la posicion, hay colision
        cout << "COLICION OCURRIDA PARA LA CLAVE: " << clave << " EN LA POSICION: " << posicion << endl;
    }
    NODO* nuevonodo = new NODO(); // Crear un nuevo nodo
    nuevonodo->clave = clave; // Asignar la clave al nuevo nodo
    nuevonodo->siguiente = lista[posicion]; // Enlazar el nuevo nodo al inicio de la lista
    lista[posicion] = nuevonodo; // Actualizar la cabeza de la lista
}

//_____________________BUSQUEDA DE ELEMENTOS_______________________

void busquedaLineal(int tabla[], int clave){
    int posicion = hashing1(clave);
    for(int i=0; i<maximo; i++){
        int nuevaposi = (posicion + i) % maximo; // Nueva posicion
        if(tabla[nuevaposi] == clave){ // Si encontramos la clave
            cout << "Clave " << clave << " encontrada en la posicion " << nuevaposi << "." << endl;
            return;
        }
        if(tabla[nuevaposi] == -1){
            break; // Si encontramos un espacio vacío, la clave no está en la tabla
        }
    }
    cout << "Clave " << clave << " no encontrada en la tabla." << endl;
}

void busquedaCuadratica(int tabla[], int clave){
    int posicion = hashing1(clave);
    for(int i=0; i<maximo; i++){
        int nuevaposi = (posicion + i*i) % maximo;
        if(tabla[nuevaposi] == clave){
            cout << "Clave " << clave << " encontrada en la posicion " << nuevaposi << "." << endl;
            return;
        }
        if(tabla[nuevaposi] == -1){
            break; // Si encontramos un espacio vacío, la clave no está en la tabla
        }
    }
    cout << "Clave " << clave << " no encontrada en la tabla." << endl;
}

void busquedaDobleInserccion(int tabla[], int clave){
    int posicion = hashing1(clave);
    int salto = hashing2(clave);
    for(int i=0; i<maximo;i++){
        int nuevaposi = (posicion + i*salto) % maximo;
        if(tabla[nuevaposi] == clave){
            cout << "Clave " << clave << " encontrada en la posicion " << nuevaposi << "." << endl;
            return;
        }
        if(tabla[nuevaposi] == -1){
            break; // Si encontramos un espacio vacío, la clave no está en la tabla
        }
    }
    cout << "Clave " << clave << " no encontrada en la tabla." << endl;
}

void busquedaEncadenamiento(NODO* lista[], int clave){
    int posicion = hashing1(clave);
    NODO* actual = lista[posicion]; // Apuntar al inicio de la lista enlazada
    int indice = 0;
    while(actual != nullptr){
        if(actual->clave == clave){ // Si encontramos la clave
            cout << "Clave " << clave << " encontrada en la posicion " << posicion << " en el indice " << indice << " de la lista enlazada." << endl;
            return;
        }
        actual = actual->siguiente; // Avanzar al siguiente nodo
        indice++; // Incrementar el indice dentro de la lista
    }
    cout << "Clave " << clave << " no encontrada en la lista enlazada." << endl;
}
void menu(char mod, int tabla[], NODO* lista[]){

    while(true){
        cout << "Seleccione una opcion:" << endl;
        cout << "1- Insertar clave" << endl;
        cout << "2- Buscar clave" << endl;
        cout << "3- Mostrar" << endl;
        cout << "4- Salir" << endl;
        int opcion;
        cin >> opcion;

        switch(opcion){
            case 1:{
                int clave;
                cout << "Ingrese la clave" << endl;
                cin >> clave;
                if(mod == 'L'){
                    pruebaLineal(tabla, clave);
                } else if(mod == 'C'){
                    pruebacuadratica(tabla, clave);
                } else if(mod == 'D'){
                    pruebadobleInserccion(tabla, clave);
                } else if(mod == 'E'){
                    pruebaEncadenamiento(lista, clave);
                }
                if(mod == 'E'){
                    imprimirLista(lista);
                } else {
                    imprimirTabla(tabla);
                }
                break;
            }
            case 2:{
                int clave;
                cout << "Ingrese la clave a buscar" << endl;
                cin >> clave;
                if(mod == 'L'){
                    busquedaLineal(tabla, clave);
                } else if(mod == 'C'){
                    busquedaCuadratica(tabla, clave);
                } else if(mod == 'D'){
                    busquedaDobleInserccion(tabla, clave);
                } else if(mod == 'E'){
                    busquedaEncadenamiento(lista, clave);
                }
                break;
            }
            case 3:{
                if(mod == 'E'){
                    imprimirLista(lista);
                
                }else{
                    imprimirTabla(tabla);
                }
                break;
            }
            case 4:{
                return;
                break;
            }
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    }
}

int main(int argc, char* argv[]){

    if(argc != 2){
        cout << "MODO DE USO: ./ejecutable [L|C|D|E]" << endl;
        return 1;
    }

    char mod = argv[1][0];
    int tabla[maximo];
    NODO* lista[maximo];

    inicializacionTabla(tabla);
    inicializarLista(lista);

    menu(mod, tabla, lista);

    return 0;
}