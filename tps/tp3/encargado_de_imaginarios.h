#ifndef __ENCARGADO_DE_IMAGINARIOS_H__
#define __ENCARGADO_DE_IMAGINARIOS_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200

#define MAX_COMANDO 50  //Asumiendo que las lineas de comando, incluyendo los nombres de archivo procesados, no van a ser más extensas que esto.


typedef struct aspecto {
    char descripcion[MAX_DESCRIPCION];
} aspecto_t;

typedef struct amigo {
    char nombre[MAX_NOMBRE];
    char color[MAX_COLOR];
    int altura;
    aspecto_t virtudes[MAX_VIRTUDES];
    int tope_virtudes;
    aspecto_t defectos[MAX_DEFECTOS];
    int tope_defectos;
    bool esta_en_mansion;
} amigo_t;




/*
*   Pre: 
*    El nombre del archivo viene dado por linea de comando.
*   Post:
*    Intenta elegir un amigo imaginario nuevo para el niño.
*    Si el archivo de nombre recibido no se pudo abrir correctamente o no pudo elegir, 
*    no se modifican archivos.
*/
void elegir_amigo(char nombre_archivo[MAX_COMANDO]);



/* 
*   Post:
*    Lee el archivo que contiene a los amigos en la mansión para mostrar los que estén presentes.
*/
void listar_amigos();



/*
*   Pre: 
*    -El nombre del amigo a devolver viene dado por linea de comando.
*    -El amigo a devolver tiene que existir en el archivo de la mansión.
*   Post: 
*    Intenta devolver un amigo imaginario del niño a la mansión.
*    Si no se pudo hacer la devolución, no se modifica el archivo.
*/
void devolver_amigo(char nombre_archivo[MAX_COMANDO]);



#endif /* __ENCARGADO_DE_IMAGINARIOS_H__ */