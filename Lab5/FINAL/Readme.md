Readme 


OBSERVACIONES:

    1. Para ejecutar el codigo se tiene que colocar ./nombre del ejecutable + data.csv
    2. Ocupe el CSV del porfesor puesto por lo que entendi se podia ocupar su informacion
    3. Cree una funcion para lberar la memoria implementada en el menu (case 6) cuando el usuario salga dek programa 
    4. Trate de seguir un orden para los titulos de las funciones por ejemplo la estrucutra con el nombre en mayusculas para poder distinguirlas, las funciones generales con la primera letra de la segunda palabra en mayusculas(liberarArbol) 
    5. Agregue los arg pero aun no estoy acostumbrados a implemetarlos 
    6. Agregue sus respectivos comentarios en las funciones que corresponden con la materia 
    7. coloque en la estructura el string go por el codigo que todos comienzan con la letra GO:numeros
       
DESCRIPCION:

    • Cada nodo (NODO) guarda un GO, funtion, score, factor de equilibrio (fe) y punteros a hijos izquierdo y derecho.
    • Se construye un árbol AVL, que es un árbol binario de búsqueda autoequilibrado.
      Inserción de nodos:
    • La función insertar coloca un nodo en la posición correcta según GO.
    • Después de cada inserción, se calcula el factor de equilibrio (fe) y se realizan rotaciones para mantener el árbol equilibrado.
      Búsqueda y recorrido:
    • Buscar localiza un nodo según su GO.
    • imprimirPosOrden recorre el árbol en posorden (izquierda → derecha → nodo) y muestra los datos.(SOLO PARA MOSTAR EN UN DETERMINADO ORDEN, NADA EN ESPECIAL)
      Carga de datos desde CSV:
    • leerCSV abre un archivo, lee línea por línea y extrae GO, funcion y score para insertarlos en el árbol.

