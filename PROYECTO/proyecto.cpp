#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //para Graphviz
using namespace std;

// Lista dinamica
struct Nodo{

    int score; // Puntaje
    int direccion; // guardar la direccion
    Nodo* diagonal;
    Nodo* arriba;
    Nodo* izquierda;
};

Nodo **M; //matriz dinamica = puntero a un puntero que apunta a una matriz dinamica 

int gap; 
int MatrizU[4][4]; //matriz de sustitucion

//Obtiene el Maximo para ocuparlo en la funcion llenar matriz
int obtenerMaximo(int a, int b, int c){ 
    int maximo = a;
    if(b > maximo){
        maximo = b;
    }
    if(c > maximo){
        maximo = c;
    }
    return maximo;
}

// Para leer la matriz U le asignamos un indice numerico a la base 
int indiceBase(char base){
    if(base == 'A' || base == 'a') return 0;
    if(base == 'C' || base == 'c' ) return 1;
    if(base == 'G' || base == 'g' ) return 2;
    if(base == 'T' || base == 't' ) return 3;
    return -1; // En caso de que la base no sea válida
}

//===================MATRIZ NEDDLEMAN WUNSCH===================

void creaMatriz(int u, int v){
    M = new Nodo*[u+1];
    for(int i = 0; i <= u; i++){
        M[i] = new Nodo[v+1];
    }
}

void eliminarMatriz(int u){
    for(int i = 0; i <= u; i++){
        delete[] M[i];
    }
    delete[] M;
}
//==================LEER ARCHIVOS==================

// Abre los archivos fasta ignorando la cabecera con el >  el getline detecta un \n en linea del archivo
string leerSecuencia(string nombreArchivo){
    ifstream archivo(nombreArchivo);
    string linea, secuencia = "";
    bool saltarCabecera = true;
    if(!archivo.is_open()){
        cout << "Error al abrir el archivo" << endl;
        return "";  
    }

    while(getline(archivo, linea)){ 
        if(saltarCabecera){
            if(linea.size() > 0 && linea[0] == '>'){
                saltarCabecera = false;
                continue;
            }       
        }
        secuencia = secuencia + linea;
    }
    archivo.close();
    return secuencia;
}

// Abre la matriz U ayudad de la funcion indeceBase 
void leematrizU(string name){
    ifstream archi(name);
    if(!archi.is_open()){
        cout << "Error al abrir el archivo de matriz de sustitucion" << endl;
        return;  
    }

    char fila;
    int a1,b2,c3,d4; // Numeros de las filas 
    string linea;
    getline(archi,linea); //leer primera linea A,C,T,G
    for(int i=0; i<4;i++){
        archi >> fila >> a1 >> b2 >> c3 >> d4;
        int h = indiceBase(fila);
        if(h<0) h=i;

        MatrizU[h][0] = a1;
        MatrizU[h][1] = b2;
        MatrizU[h][2] = c3;
        MatrizU[h][3] = d4;
    }
    archi.close();
}

void mostrarMatrizU(){
    char bases[4] = {'A','C','G','T'};

    cout << "\nMatriz de Sustitucion U:\n";
    cout << "      A     C     G     T\n";

    for(int i = 0; i < 4; i++){
        cout << bases[i] << "   ";
        for(int j = 0; j < 4; j++){
            cout << MatrizU[i][j] << "    ";
        }
        cout << "\n";
    }

    cout << endl;
}

//==================INICIALIZAR=================================

// Llena la matriz con el valor de penalizacion

void inicializarMatriz(const string& N, const string& C){
    int u = N.size(); // LARGO DE LA PRIMERA SECUENCIA
    int v = C.size(); // LARGO DE LA SEGUNDA SECUENCIA

    creaMatriz(u ,v);

    //primera coordenada
    M[0][0].score = 0; // EL PUNTAJE INICIAL ES CERO
    M[0][0].direccion = 0;  // NO HAY DIRECCION INICIAL
    M[0][0].diagonal = M[0][0].arriba = M[0][0].izquierda = nullptr; // PUNTEROS NULOS

    //Primera columna
    for(int i = 1; i <= u; i++){ // RECORRER FILAS
        M[i][0].score = gap *  i; // PUNTAJE DE GAP ACUMULADO
        M[i][0].direccion = 2; // DIRECCION HACIA ARRIBA
        M[i][0].arriba = &M[i-1][0]; // PUNTERO A LA CELDA DE ARRIBA
        M[i][0].izquierda = nullptr; // PUNTERO IZQUIERDO NULO
        M[i][0].diagonal = nullptr; // PUNTERO DIAGONAL NULO
    }

    //Primera fila
    for(int j = 1; j <= v; j++){ // RECORRER COLUMNAS
        M[0][j].score = gap * j; // PUNTAJE DE GAP ACUMULADO
        M[0][j].direccion = 3;   // DIRECCION HACIA LA IZQUIERDA
        M[0][j].izquierda = &M[0][j-1]; // PUNTERO A LA CELDA DE LA IZQUIERDA
        M[0][j].arriba = nullptr; // PUNTERO ARRIBA NULO
        M[0][j].diagonal = nullptr; // PUNTERO DIAGONAL NULO
    }
}

//===============================LLENAR====================================

//Ayudado de IndiceBase y obtenerMaximo llena la matriz ayudado de la funcion y las direcciones 
void llenarMatriz(const string& N, const string& C){

    int u = N.size();
    int v = C.size();

    for(int i = 1; i <= u; i++){
        for(int j=1; j<=v; j++){

            int xi = indiceBase(N[i-1]);
            int zj = indiceBase(C[j-1]);
            int diagoScore = MatrizU[xi][zj];

            int diago = M[i-1][j-1].score + diagoScore;
            int arri = M[i-1][j].score + gap;
            int izq = M[i][j-1].score + gap;

            int mejorScore = obtenerMaximo(diago,arri,izq);
            M[i][j].score = mejorScore;

            if(mejorScore == diago){
                M[i][j].direccion = 1;
                M[i][j].diagonal = &M[i-1][j-1];
                M[i][j].arriba = nullptr;
                M[i][j].izquierda = nullptr;
            }else if(mejorScore == arri){
                M[i][j].direccion = 2;
                M[i][j].arriba = &M[i-1][j];
                M[i][j].diagonal = nullptr;
                M[i][j].izquierda = nullptr;
            }else{
                M[i][j].direccion = 3;
                M[i][j].izquierda = &M[i][j-1];
                M[i][j].diagonal = nullptr;
                M[i][j].arriba = nullptr;
            }
        }
    }
}

//=========================RECONSTRUCCION======================


// Hace el backstraking desde la direccion abajo derecha guardando los scores maximos y reconstruyendo la secuencia final ademas de 
// calcular el porcentaje de identidad, las seceuncias se guardan en secuencia 
void Reconstruccion(const string& N, const string& C, string &secuencia, double &identidad_secu, string &secuenciaA, string &secuenciaB){

    int u = N.size(); // Calcula el largo de la secuencia
    int v = C.size();

    string A(u+v + 5, ' ');  //Crea donde se va a guardar al secuencia A + 5 por seguridad
    string B(u+v + 5, ' '); //Crea donde se va a guardar al secuencia B + 5 por seguridad

    //Inicializacion de la posicion e indices
    int posi = 0;
    int i = u;
    int j = v;

    while(i>0 || j>0){  //Bucle para hacer la recosntruccion filas y columnas
        if(M[i][j].direccion == 1){ //DIAGONAL
            A[posi] = N[i-1];
            B[posi] = C[j-1];
            i--; j--; // decrecion
        }
        else if(M[i][j].direccion == 2){ // arriba
            A[posi] = N[i-1];
            B[posi] = '-';
            i--; //decrecion
        }
        else{
            A[posi] = '-';
            B[posi] = C[j-1]; // izquierda
            j--; // decrecion
        }
        posi++; //proxima posicion
    }
    // Limpirar las cadenas 
    secuenciaA.clear();
    secuenciaB.clear();
    secuencia.clear();

    string lineas;

    //Reconstrucion con |= matches , . = mismatch y vacio = para gaps
    for(int k = posi-1; k >= 0; k--){
        secuenciaA += A[k];
        secuenciaB += B[k];

        if(A[k] == B[k] && A[k] != '-' && B[k] != '-') lineas += '|';
        else if(A[k] == '-' || B[k] == '-') lineas += ' ';
        else lineas += '.'; 
    }
 
    secuencia = "Alineacion\n";

    // Calculo de matches
    int matches = 0;
    for(int k = 0; k < posi; k++){
        if(secuenciaA[k] == secuenciaB[k] && secuenciaA[k] != '-' && secuenciaB[k] != '-')
            matches++;
    }

    int ancho = 80; // Imprimir por 80 columnas de bases en el txt
    int largo = secuenciaA.size();

    for (int i = 0; i < largo; i += ancho) {

        for (int k = i; k < i + ancho && k < largo; k++) {
            secuencia += secuenciaA[k];
        }
        secuencia += "\n";

        for (int k = i; k < i + ancho && k < largo; k++) {
            secuencia += lineas[k];
        }
        secuencia += "\n";


        for (int k = i; k < i + ancho && k < largo; k++) {
            secuencia += secuenciaB[k];
        }
        secuencia += "\n\n";
    }

    //Calculo de identidad
    double identidad = 100.0 * matches / posi;
    identidad_secu = identidad;
    secuencia += "\nIdentidad: " + to_string(identidad) + "%\n";
}

void mostrarIdentidad(double identidad){
    cout << "\nPorcentaje de identidad: " << identidad << "%\n";
}

//=======================GRAPHVIZ==============================

void generarGraphviz(const string& A, const string& B, string filename){

    // Creacion del dot
    ofstream dot(filename);
    if(!dot.is_open()){
        cout << "Error al crear archivo Graphviz." << endl;
        return;
    }

    dot << "digraph G {\n";
    dot << "rankdir=LR;\n";
    dot << "node [shape=box style=filled fontname=\"Courier\" fontsize=12 width=0.4 height=0.4];\n\n";

    int N = A.size();
    if(N > 100) N = 100;  // Hasta 100 bases 

    for(int i = 0; i < N; i++){
        char a = A[i];
        char b = B[i];

        // Obtiene los scores de la matriz 
        int ia = indiceBase(a);
        int ib = indiceBase(b);

        int score = 0;
        if(ia >= 0 && ib >= 0)
            score = MatrizU[ia][ib];
        else
            score = gap;

        string color;
        if(score > 0)      color = "green"; // match
        else if(score == 0) color = "yellow"; // score 0
        else               color = "red"; // mismatch

        //Creacion de la caja 
        string label = "";
        label += a;
        label += "|";
        label += b;

        dot << "n" << i << " [label=\"" << label 
            << "\" fillcolor=\"" << color << "\"];\n";
    }

    for(int i = 0; i < N - 1; i++){
        dot << "n" << i << " -> n" << (i+1) << ";\n";
    }

    dot << "}\n";
    dot.close();
}

//========================MAIN============================

int main(int argc, char* argv[]){
    if(argc != 9){
        cout << "Uso:\n./programa -C1 cad1.txt -C2 cad2.txt -U funcionU.txt -V -2" << endl;
        return 1;
    }

    string arch1="", arch2="", archU="";

    for(int i=1; i<argc; i++){
        string a = argv[i];

        if(a == "-C1") arch1 = argv[++i];
        else if(a == "-C2") arch2 = argv[++i];
        else if(a == "-U")  archU = argv[++i];
        else if(a == "-V")  gap   = atoi(argv[++i]);  
    }

    string C1 = leerSecuencia(arch1);
    string C2 = leerSecuencia(arch2);

    cout << "\nSecuencia 1: " << C1 << endl;
    cout << "Secuencia 2: " << C2 << endl;

    leematrizU(archU);
    mostrarMatrizU();

    inicializarMatriz(C1, C2);
    llenarMatriz(C1, C2);

    double identidad = 0.0;
    string Aline1 = "", Aline2 = "";
    string resultado="";

    Reconstruccion(C1, C2, resultado, identidad, Aline1, Aline2);
    mostrarIdentidad(identidad);

    generarGraphviz(Aline1, Aline2, "alineamiento.dot");

    system("dot -Tpng alineamiento.dot -o alineamiento.png");

    ofstream out("Alineamiento_Final.txt");
    out << resultado;
    out.close();

    eliminarMatriz(C1.size());

    cout << "Alineamiento guardado en Alineamiento_Final.txt\n";
    return 0;
}