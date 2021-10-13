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
//#define ARCHIVO_AMIGOS_NINIO "amigos_del_ninio.txt"

#define AZUL "AZUL"

const int ALTURA_CHARLY = 60;
const int ALTURA_COCO = 180;
const int ALTURA_QUESO = 120;

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
    //FILE* amigos_del_ninio;

    
    //ESCRITURA:
    amigos_mansion = fopen(ARCHIVO_AMIGOS_MANSION, "w");
    if(amigos_mansion == NULL){
        printf("Error al abrir archivo 'amigos_mansion.dat'.\n");
        return -1;
    }
    /*
    amigos_del_ninio = fopen(ARCHIVO_AMIGOS_NINIO, "w");
    if(amigos_del_ninio == NULL){
        printf("Error al abrir archivo 'amigos_del_ninio.txt'.\n");
        return -1;
    }
    */


    //ASIGNACION MUY HARDCODEADA, NO SE ENTREGA ESTE PROGRAMA NI LOS ARCHIVOS CREADOS POR EL MISMO;
    amigo_t amigo;
    
    /*
    //Escritura del .txt
    fprintf(amigos_del_ninio, "AZUL;<200;CALMADO;RUIDOSO\n");
    fprintf(amigos_del_ninio, "RED\nBLUE\nGARABATO\nQUESO\n");
    */

    //Escritura del .dat
    //ESTAN ORGANIZADOS POR NOMBRE!!!(ascendente)
    strcpy(amigo.nombre, "CHARLY");
    strcpy(amigo.color, AZUL);
    amigo.altura = ALTURA_CHARLY;
    strcpy(amigo.virtudes[0].descripcion, "COMPRENSIVO");
    strcpy(amigo.virtudes[1].descripcion, "PACIENTE");
    strcpy(amigo.virtudes[2].descripcion, "CALMADO");
    amigo.tope_virtudes = 3;
    strcpy(amigo.defectos[0].descripcion, "MOLESTO");
    strcpy(amigo.defectos[1].descripcion, "DESCUIDADO");
    strcpy(amigo.defectos[2].descripcion, "PEREZOSO");
    amigo.tope_defectos = 3;
    amigo.esta_en_mansion = true;    

    fwrite(&amigo, sizeof(amigo), 1, amigos_mansion);



    strcpy(amigo.nombre, "COCO");
    strcpy(amigo.color, "VERDE");
    amigo.altura = ALTURA_COCO;
    strcpy(amigo.virtudes[0].descripcion, "AMABLE");
    strcpy(amigo.virtudes[1].descripcion, "CARINIOSO");
    strcpy(amigo.virtudes[2].descripcion, "CALMADO");
    amigo.tope_virtudes = 3;
    strcpy(amigo.defectos[0].descripcion, "ENOJON");
    strcpy(amigo.defectos[1].descripcion, "DESCUIDADO");
    strcpy(amigo.defectos[2].descripcion, "DESASEADO");
    amigo.tope_defectos = 3;
    amigo.esta_en_mansion = true;

    fwrite(&amigo, sizeof(amigo), 1, amigos_mansion);



    strcpy(amigo.nombre, "CONEJO");
    strcpy(amigo.color, AZUL);
    amigo.altura = 20;
    strcpy(amigo.virtudes[0].descripcion, "INTELIGENTE");
    strcpy(amigo.virtudes[1].descripcion, "CALMADO");
    strcpy(amigo.virtudes[2].descripcion, "SERIO");
    strcpy(amigo.virtudes[3].descripcion, "FELIZ");
    strcpy(amigo.virtudes[4].descripcion, "AMISTOSO");
    amigo.tope_virtudes = 5;
    strcpy(amigo.defectos[0].descripcion, "MOLESTO");
    strcpy(amigo.defectos[1].descripcion, "ENOJON");
    strcpy(amigo.defectos[2].descripcion, "DESORDENADO");
    strcpy(amigo.defectos[3].descripcion, "DESARREGLADO");
    amigo.tope_defectos = 4;
    amigo.esta_en_mansion = true;

    fwrite(&amigo, sizeof(amigo), 1, amigos_mansion);



    strcpy(amigo.nombre, "QUESO");
    strcpy(amigo.color, AZUL);
    amigo.altura = ALTURA_QUESO;
    strcpy(amigo.virtudes[0].descripcion, "ENERGETICO");
    strcpy(amigo.virtudes[1].descripcion, "CALMADO");
    strcpy(amigo.virtudes[2].descripcion, "ALEGRE");
    amigo.tope_virtudes = 3;
    strcpy(amigo.defectos[0].descripcion, "MOLESTO");
    strcpy(amigo.defectos[1].descripcion, "ENOJON");
    strcpy(amigo.defectos[2].descripcion, "DESORDENADO");
    amigo.tope_defectos = 3;
    amigo.esta_en_mansion = true;

    fwrite(&amigo, sizeof(amigo), 1, amigos_mansion);





    //fclose(amigos_del_ninio);
    fclose(amigos_mansion);

      
    return 0;
}