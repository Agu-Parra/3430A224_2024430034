README
 Agustín  Parra
 CREACION:
 Creé una estructura llamada NODO que registra un valor y posee dos punteros: uno hacia la izquierda y otro hacia la derecha, ambos inicializados en NULL, con el propósito de construir el árbol.
 El proceso de inserción funciona como siempre: se llama a la primera función llamada crearNodo(), y el nodo creado se inserta en el árbol eligiendo si se coloca a la izquierda o a la derecha del nodo raíz.
 Para definir los recorridos (preorden, inorden y postorden) me guié por el pseudocódigo visto en clase; no tuve mayores dificultades en esa parte.
 En la función búsqueda, como su nombre indica, se busca el nodo ingresado por el usuario de forma recursiva por ambos lados del árbol (izquierdo y derecho).
La función eliminar localiza el nodo y, si lo encuentra, coloca el puntero correspondiente apuntando a NULL.
 Por último, la función que más me costó fue la de generar el archivo DOT para exportar el árbol a Graphviz en formato .png.
Tuve varios problemas, ya que en el gráfico el último nodo de cada rama aparecía apuntando hacia sí mismo en lugar de hacia un punto que representara NULL.
 					(imagen representativa)
 Finalmente logré resolverlo (probando distintas formas en la función), aunque aún no me queda del todo claro por qué ocurría ese comportamiento.
 OBSERVACIONES:
 En el archivo del menú tuve un problema: el ejecutable no corría correctamente y me indicaba que los valores creados no correspondían.
Investigando, descubrí que debía colocar llaves {} en algunos case del menú, ya que dentro de ellos declaraba variables locales.
 Cabe destacar que mi estructura se llama NODO (en mayúsculas) por costumbre, para diferenciar las estructuras del resto del código, tal como lo hacia en otras asignaturas.
 Además, en el repositorio Git voy a eliminar archivos que se subieron por herencia desde mi rama principal (main) del Laboratorio 0, con el objetivo de mantener un mayor orden dentro de la rama actual del proyecto.
(No estoy seguro si esta observación corresponde en esta sección, pero la incluyo para dejar constancia del cambio del repositorio.)