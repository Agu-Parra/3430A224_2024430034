#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//ARG Y ARGV, POR LO QUE ENTENDÍ CON EL ARGC Y EL ARGV DEFINO DESDE ANTES CUANTAS PILAS (defino las dimensiones m y n)
// VOY A TENER PARA PODER MOVER LOS CONTENEDORES A ESTAS PILAS TEMPORALES ESTO SE DEBE DECLARAR EN EL TERMINAL

struct PILA{

    int max;
    int tope;
    bool band;
    string contenedor[100];

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

    void Push(int &tope, bool &band, int max, string contenedor[], string dato){
        
        Pila_llena(tope, max, band);

        if(band == true){
            cout << "DESBORDAMIENTO" << endl;
        }else if(band == false){
            tope = tope +1;
            contenedor[tope] = dato;
            cout << "AGREGADO: " << dato << endl; 
        }
    }
    string Pop(string contenedor[], bool &band, int &tope){
        Pila_vacia(tope, band);

        if(band == true){
            cout << "SUBDESBORDAMIENTO" << endl;
            return "";
        }else if(band == false){
            string dato = contenedor[tope];
            tope = tope -1;
            cout << "ELIMINADO" << endl;
            return dato;
        }
        return "";
    }

    void Mostar(string contenedor[], int tope){
        if(tope == 0){
            cout << "PILA VACIA" << endl;
        }else{
            cout << "CONTENEDORES\n";
            for(int i = tope; i >= 1; i--){
                cout << "-" << contenedor[i] << endl;
            }
        }
    }
};

void Mostrar_puertos(PILA puerto[], int m){

    cout << "PUERTOS: \n";
    for(int i = 0; i < m; i++ ){
        cout << "Puerto: " << i + 1 << endl;
        puerto[i].Mostar(puerto[i].contenedor, puerto[i].tope );

    }
    cout << "+________________________________+" << endl;
}

void Retirar(PILA puerto[], int m, int num, string busca ){

    PILA &origen = puerto[num]; // ACCEDO AL ESPACIO DE MEMORIA DONDE SE ENCUENTRA DEFINIDO EL ORIGEN

    int posicion = -1; //POSICION EN LA QUE NO HEMOS ENCONTRADO ALGUN CONTENEDOR 

    for(int i = 1; i <= origen.tope; i++){
        if(origen.contenedor[i] == busca){
          posicion = i; 
          break;  
        }  // ENCONTRE UN CONTENEDOR!!! Y ESTA EN LA POSICION i, NO SIGO BUSCANDO
    }
    if(posicion == -1){
        cout << "NO SE ENCONTRO NINGUN CONTENEDOR" << endl; // NO SE ENCONTRO NINGUN CONTENEDOR :(
        return; //VUELVE A BUSCAR
    }
    int auxiliar = -1; //POSICION EN LA QUE NO HAY UNA PILA(PUERTO) DONDE GUARDAR
    for(int i = 0; i < m; i++){
        if(i != num && puerto[i].tope < puerto[i].max){
            auxiliar = i; 
            break;
        }  // SE ENCONTRO UNA PILA DONDE PODER GUARDAR EL CONTENEDOR !!!
    }
    if(auxiliar == -1){
        cout << "NO SE ENCONTRO NINGUN PUERTO DONDE GUARDAR EL CONTENEDOR" << endl;
        return;
    }
    //TENEMOS QUE SACAR DEL CONTENEDOR ORIGANL Y DEVOLVER EL CONTENEDOR AL PUERTO ORIGINAL
    while (origen.tope > posicion) {
        string dato = origen.Pop(origen.contenedor, origen.band, origen.tope);
        puerto[auxiliar].Push(puerto[auxiliar].tope, puerto[auxiliar].band, puerto[auxiliar].max, puerto[auxiliar].contenedor, dato);
    }
    string retirar = origen.Pop(origen.contenedor,origen.band, origen.tope);
    cout << "CONTENEDOR RETIRADO DEL PUERTO ORIGINAL" << endl;
    while(puerto[auxiliar].tope > 0){
        string dato = puerto[auxiliar].Pop(puerto[auxiliar].contenedor, puerto[auxiliar].band, puerto[auxiliar].tope);
        origen.Push(origen.tope, origen.band, origen.max, origen.contenedor, dato);
    }
}

void MENU(PILA puerto[], int m, int n){

    int opcion;
    string nombre;
    int destino;
    do{
        cout << "____________MENU______________\n";
        cout << "(1) Agregar Contenedor(PUSH)" << endl;
        cout << "(2) Eliminar Contenedor(POP)" << endl;
        cout << "(3) Mostrar Contenedor/es" << endl;
        cout << "(4) SALIR" << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cout << "";
        cin >> opcion; 

        switch (opcion){

            case 1:
                cout << "Ingrese el contenedor a registrar(maximo por puertos: " << n << ")" << endl;
                cin.ignore();
                getline(cin, nombre);
                cout << "Puertos disponibles:\n";
                for(int i = 1; i <= m; i++){   //ESTO ME MUESTRA NADA MAS QUE LOS PUERTOS PARA SABER QUE SELECCIONAR 
                    cout << "->" << i << " ";
                }
                cout << "Numero del puerto" << endl;
                cin >> destino;
                if(destino >= 1 && destino <= m){  //ESTO TAMBIEN ME MUESTRAN LOS VALORES PARA SABER QUE SELECCIONAR 
                    puerto[destino -1].Push(puerto[destino-1].tope, puerto[destino-1].band, puerto[destino-1].max, puerto[destino-1].contenedor,nombre);
                    
                    puerto[destino-1].Mostar(puerto[destino-1].contenedor, puerto[destino-1].tope);
                }
                else{
                    cout << "INVALIDO" << endl;
                }
                break;
            case 2:
                for(int i = 1; i <= m; i++){ //LO MISMO QUE EL CASE 1
                cout << "-> " << i << " ";
                }
                cout << "Ingrese el Puerto donde se encuentra el contenedor: ";
                cin >> destino;
                if(destino >= 1 && destino <= m){  //LO MISMO QUE EL CASE 1
                    cout << "Contenedores en el puerto " << destino << ":\n";
                    puerto[destino-1].Mostar(puerto[destino-1].contenedor, puerto[destino-1].tope);
                }
                cout << "Nombre del contenedor: ";
                cin.ignore();
                getline(cin,nombre);
                if(destino >= 1 && destino <= m) Retirar(puerto, m, destino -1, nombre);
                else{
                    cout << "INVALIDO" << endl;
                }
                break;
            case 3:
                Mostrar_puertos(puerto, m);
                break;
            case 4:
                cout << "SALIENDO............" << endl;
                break;
            default:
                cout << "OPCION INVALIDA" << endl;
        }  
    }while(opcion != 4);
}

    
int main(int argc, char* argv[]){
    
    if(argc < 3){ 
        cout << "Tiene que ingresar los puertos" << endl;
        return 1;
    } // SE TIENE QUE INGRESAR 3 ARGUMENTOS EN EL TERMINAL ./XXX M Y N 

    int m = atoi(argv[1]);
    int n = atoi(argv[2]); //OCUPAMOS UNS ATOI COMO EN EL EJEMPLO DEL PROFE
    PILA puerto[m];

    for(int i = 0; i < m; i++){
        puerto[i].tope = 0;
        puerto[i].max = n;
        puerto[i].band = true;
    }
    MENU(puerto, m,n);

    return 0;
}