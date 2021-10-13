#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define MAX_COLOR 50
#define MAX_VIRTUDES 10
#define MAX_DEFECTOS 10
#define MAX_DESCRIPCION 200

#define ARCHIVO_AMIGOS_MANSION "amigos_mansion.dat"

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

int main(){
    FILE* amigos_mansion;

   //LECTURA del .dat:
    amigos_mansion = fopen(ARCHIVO_AMIGOS_MANSION, "r");
    if(amigos_mansion == NULL){
        printf("Error al abrir archivo 'amigos_mansion.dat'.\n");
        return -1;
    }

    amigo_t amigo;
    size_t leidos = fread(&amigo, sizeof(amigo), 1, amigos_mansion);
    while(leidos > 0){
        printf("Nombre: %s\n", amigo.nombre);
        printf("Color: %s\n", amigo.color);
        printf("Altura: %i\n", amigo.altura);
        printf("Virtudes:\n");
        for(int i = 0; i < amigo.tope_virtudes; i++){
            printf(" %s\n", amigo.virtudes[i].descripcion);
        }
        printf("Defectos:\n");
        for(int i = 0; i < amigo.tope_defectos; i++){
            printf(" %s\n", amigo.defectos[i].descripcion);
        }
        if(amigo.esta_en_mansion){
            printf("Está en mansión: true\n\n");
        }
        else if(!amigo.esta_en_mansion){
            printf("Está en mansión: false\n\n");
        }

        leidos = fread(&amigo, sizeof(amigo), 1, amigos_mansion);
    }

    fclose(amigos_mansion);

      
    return 0;
}