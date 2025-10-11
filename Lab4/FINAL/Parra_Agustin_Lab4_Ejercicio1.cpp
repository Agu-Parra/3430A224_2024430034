#include <iostream> 
#include <string> 
#include <fstream> 
using namespace std;


//CREO MI ESTRUCTURA NODO(con mayusculas para diferenciar la estructura) CON MIS PUNTEROS Y MI DATO
struct NODO{

    int num;
    NODO* left; 
    NODO* right;
};

//LO QUE HACE ESTO ES CREAR UN "nuevo_nodo" ASIGNANDOLE VALOR Y PUNTEROS EN NULLPTR
NODO* crearNodo(int valor){

    NODO* nuevo_nodo = new NODO;
    nuevo_nodo -> num = valor;
    nuevo_nodo -> left = nullptr;
    nuevo_nodo -> right = nullptr;
    return nuevo_nodo;
}

//ESTA FUNCION CREA EL ARBOL RECURSIVAMENTE CON CREARNODO Y PIDIENDO DATOS AL USUARIO PARA CREAR MI ARBOL LOS DATOS 
//SON MI NODO RAIZ Y ADEMAS PREGUNTA SI HAY NODOS A LA IZQUIERDA Y DERECHA
void crearArbol(NODO* &apnodo){

    if(apnodo == nullptr){

        int valor;
        cout << "Ingrese un valor para el nodo: " << endl;
        cin >> valor;
        apnodo = crearNodo(valor);
    }

    char respuesta;

    cout << "Hay un nodo al lado izquierdo de " << apnodo -> num << "? (s/n): " << endl;
    cin >> respuesta;
    if(respuesta == 's' || respuesta == 'S'){
        apnodo -> left = nullptr;
        crearArbol(apnodo -> left);
    }else{
        apnodo -> left = nullptr;
    }

    cout << "Hay un nodo al lado derecho de " << apnodo -> num << "? (s/n): " << endl;
    cin >> respuesta;
    if(respuesta == 's' || respuesta == 'S'){
        apnodo -> right = nullptr;
        crearArbol(apnodo -> right);
    }else{
        apnodo -> right = nullptr;
    }
}

//ESTA FUNCION BUSCA UN NODO EN EL ARBOL, SI LO ENCUENTRA DEVUELVE LA DIRECCION DE ESE NODO
NODO* Busqueda(NODO* apnodo, int valor){

    if(apnodo == nullptr){
        cout << "El valor no esta en el arbol" << endl;
        return nullptr;
    }
    if (apnodo -> num == valor){
        return apnodo;
    }

    NODO* izq = Busqueda(apnodo -> left, valor);
    if(izq != nullptr){
        return izq;
    }

    NODO* der = Busqueda(apnodo -> right, valor);
    if(der != nullptr){
        return der;
    }
    return nullptr;
}


//ESTA FUNCION ELIMINA UN NODO BUSCADO, SI LO ENCUENTRA LO ELIMINA Y PONE EL PUNTERO EN NULLPTR
void eliminarBuscado(NODO* &apnodo, int valor){

    if(apnodo == nullptr){
        cout << "El valor no esta en el arbol" << endl;
        return;
    }
    if (apnodo -> num == valor){
        delete apnodo;
        apnodo = nullptr;
        return;
    }

    eliminarBuscado(apnodo -> left, valor);
    eliminarBuscado(apnodo -> right, valor);
}

//LAS SIGUIENTES 3 FUNCIONES SON PARA IMPRIMIR EL ARBOL EN PREORDEN, INORDEN Y POSTORDEN
void pre_Orden(NODO* nodo){
    if(nodo == nullptr){
        return;
    }
    cout << nodo -> num << "-" << endl;
    pre_Orden(nodo -> left);
    pre_Orden(nodo -> right); 
}
void in_Orden(NODO* nodo){
    if(nodo == nullptr){
        return;
    }
    in_Orden(nodo -> left);
    cout << nodo -> num << "-" << endl;
    in_Orden(nodo -> right);
}
void post_Orden(NODO* nodo){
    if(nodo == nullptr){
        return;
    }
    post_Orden(nodo -> left);
    post_Orden(nodo -> right);
    cout << nodo -> num << "-" << endl; 
}

//ESTA FUNCION GENERA EL ARCHIVO DOT PARA LUEGO GRAFICARLO CON GRAPHVIZ Y EXPORTAR EN UN PNG(esta en el menu)
void Dot(NODO* nodo, ofstream &archivo){

    if(nodo == nullptr){
        return;
    }

    if(nodo -> left != nullptr){
        archivo << nodo->num << " ->" << nodo->left->num << ";" << endl;
        Dot(nodo->left, archivo);
    }else{
        archivo << "\"" << nodo->num << "i\" [shape=point];\n";
        archivo << nodo->num << "->\"" << nodo->num << "i\";\n";
    }
    if(nodo -> right != nullptr){
        archivo << nodo -> num << " ->" << nodo->right->num << ";" << endl;
        Dot(nodo->right, archivo);
    }else{
        archivo << "\"" << nodo->num << "d\" [shape=point];\n";
        archivo << nodo->num << "->\"" << nodo->num << "d\";\n";
    }
}

//ME LIBERO TODO EL ARBOL RECURSIVAMENTE
void liberarArbol(NODO* &nodo){
    if (nodo == nullptr)
        return;

    liberarArbol(nodo->left);   
    liberarArbol(nodo->right);  

    delete nodo;                
    nodo = nullptr;            
}







void Menu(){

    NODO* raiz = nullptr;
    int opcion;
    int number, valorBuscar, valorEliminar;
    char lado;


    do{

        cout << "__________________MENU__________________" << endl;
        cout << "1. Crear arbol" << endl;
        cout << "2. Insertar nodo" << endl;
        cout << "3. Mostrar arbol (Pre-Orden, In-Orden, Post-Orden)" << endl;
        cout << "4. Buscar nodo" << endl;
        cout << "5. Eliminar nodo" << endl;
        cout << "6. Generar archivo Graphviz" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion){
            case 1:
                crearArbol(raiz);
                break;
                
            case 2:{
                
                cout << "Ingrese el valor del nodo a insertar: " << endl;
                cin >> number;
                NODO* nuevo = crearNodo(number);
               
                cout << "Desea insertarlo a la izquierda (i) o derecha (d) del nodo raiz " << raiz -> num << "?: " << endl;
                cin >> lado;
                if(lado == 'i' || lado == 'I'){
                    raiz -> left = nuevo;
             
                }else {
                    raiz -> right = nuevo;
                }
                break;
            }
            case 3:
                cout << "Pre-Orden: " << endl;
                pre_Orden(raiz);
                cout << "\nIn-Orden: " << endl;
                in_Orden(raiz);
                cout << "\nPost-Orden: " << endl;
                post_Orden(raiz);
                break;
            case 4:{
                
                cout << "Ingrese el valor a buscar: " << endl;
                cin  >> valorBuscar;
                NODO* encontrado = Busqueda(raiz, valorBuscar);
                if(encontrado != nullptr){
                    cout << valorBuscar << "<- nodo encontrado" << endl;
                }
                break;
            }
                
            case 5:
                
                cout << "Ingrese el valor a eliminar: " << endl;
                cin >> valorEliminar;
                eliminarBuscado(raiz, valorEliminar);
                cout << "Nodo " << valorEliminar << " eliminado" << endl;
                break;
            case 6: {
                ofstream archivo("arbol.dot");
                archivo << "digraph G {\n";
                archivo << "node [style=filled fillcolor=\"#ffd6cc\"];\n"; //BUSQUE UN COLOR PARA DIFERENCIAR 
                Dot(raiz, archivo);
                archivo << "}\n";
                archivo.close();
                
                system("dot -Tpng arbol.dot -o arbol.png");
                cout << "Archivo 'arbol.dot' y 'arbol.png' generados exitosamente." << endl;
                break;
            }
            case 7:
                liberarArbol(raiz);
                cout << "SALIENDO DEL PROGRAMA..." << endl;
                break;
            default:
                cout << "OPCION INVALIDA" << endl;
        }

    } while(opcion != 7);


}




int main(){

    Menu();


    return 0;
}