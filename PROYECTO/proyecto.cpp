#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> //para el system y atoi
using namespace std;

struct Nodo{

    int score;
    int direccion;
    Nodo* diagonal;
    Nodo* arriba;
    Nodo* izquierda;
};

Nodo **M; //prueba : matriz dinamica

int gap; 
int MatrizU[4][4]; //matriz de sustitucion

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

void leematrizU(string name){
    ifstream archi(name);
    if(!archi.is_open()){
        cout << "Error al abrir el archivo de matriz de sustitucion" << endl;
        return;  
    }

    char fila;
    int a1,b2,c3,d4;
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

void Reconstruccion(const string& N, const string& C, string &secuencia, double &identidad_secu, string &secuenciaA, string &secuenciaB){

    int u = N.size();
    int v = C.size();

    string A(u+v + 5, ' ');
    string B(u+v + 5, ' ');

    int posi = 0;
    int i = u;
    int j = v;

    while(i>0 || j>0){
        if(M[i][j].direccion == 1){
            A[posi] = N[i-1];
            B[posi] = C[j-1];
            i--; j--;
        }
        else if(M[i][j].direccion == 2){
            A[posi] = N[i-1];
            B[posi] = '-';
            i--;
        }
        else{
            A[posi] = '-';
            B[posi] = C[j-1];
            j--;
        }
        posi++;
    }

    secuenciaA.clear();
    secuenciaB.clear();
    secuencia.clear();
    string lineas;


    for(int k = posi-1; k >= 0; k--){
        secuenciaA += A[k];
        secuenciaB += B[k];

        if(A[k] == B[k] && A[k] != '-' && B[k] != '-') lineas += '|';
        else if(A[k] == '-' || B[k] == '-') lineas += ' ';
        else lineas += '.'; 
    }
 
    secuencia = "Alineacion\n";

    int matches = 0;
    for(int k = 0; k < posi; k++){
        if(secuenciaA[k] == secuenciaB[k] && secuenciaA[k] != '-' && secuenciaB[k] != '-')
            matches++;
    }

    int ancho = 80;
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

    double identidad = 100.0 * matches / posi;
    identidad_secu = identidad;
    secuencia += "\nIdentidad: " + to_string(identidad) + "%\n";
}

void mostrarIdentidad(double identidad){
    cout << "\nPorcentaje de identidad: " << identidad << "%\n";
}

//=======================GRAPHVIZ==============================

void generarGraphviz(const string& A, const string& B, string filename){

    ofstream dot(filename);
    if(!dot.is_open()){
        cout << "Error al crear archivo Graphviz." << endl;
        return;
    }

    dot << "digraph G {\n";
    dot << "rankdir=LR;\n";
    dot << "node [shape=box style=filled fontname=\"Courier\" fontsize=12 width=0.4 height=0.4];\n\n";

    int N = A.size();
    if(N > 100) N = 100;

    for(int i = 0; i < N; i++){
        char a = A[i];
        char b = B[i];

        int ia = indiceBase(a);
        int ib = indiceBase(b);

        int score = 0;
        if(ia >= 0 && ib >= 0)
            score = MatrizU[ia][ib];
        else
            score = gap;

        string color;
        if(score > 0)      color = "green";
        else if(score == 0) color = "yellow";
        else               color = "red";

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