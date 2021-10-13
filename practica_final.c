#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VECTOR 40





































//==================================================================//==================================================================//


/*
*   EJERCICIOS DE FINAL:
*/

/*
*   10/09/2020:
*   (EJERCICIO 1 VERSION 1)
*/

#define MAX_PUEBLO 5
#define MAX_NOMBRE 30
#define MAX_TIPO 30
#define MAX_NOMBRE_ARCHIVO 40

typedef struct peluqueria{
    char pueblo[MAX_PUEBLO];
    char nombre[MAX_NOMBRE];
    char tipo_corte[MAX_TIPO];
    int puntos;
} peluqueria_t;

void listar_peluquerias(char nombre_archivo[MAX_NOMBRE_ARCHIVO]){
    FILE* archivo_peluquerias = fopen(nombre_archivo, "r");
    if(!archivo_peluquerias){
        prinft("Error al abrir el archivo!\n");
        return;
    }

    peluqueria_t peluqueria_leida;
    char pueblo_actual[MAX_NOMBRE];
    int total_barberias = 0;
    int total_puntaje = 0;
    int promedio = 0;
    
    fscanf(archivo_peluquerias, "%[^;];%[^;];%[^;];%i\n", peluqueria_leida.pueblo, peluqueria_leida.nombre, peluqueria_leida.tipo_corte, peluqueria_leida.puntos);
    strcpy(pueblo_actual, peluqueria_leida.pueblo);
    while(!feof(archivo_peluquerias)){
        printf("\n %s:\n", pueblo_actual);
        while((strcmp(peluqueria_leida.pueblo, pueblo_actual)==0) && (!feof(archivo_peluquerias))){
            if(peluqueria_leida.puntos != -1){
                printf("\t %s: %i puntos.\n", peluqueria_leida.nombre, peluqueria_leida.puntos);
                total_barberias++;
                total_puntaje += peluqueria_leida.puntos;
            }
            fscanf(archivo_peluquerias, "%[^;];%[^;];%[^;];%i\n", peluqueria_leida.pueblo, peluqueria_leida.nombre, peluqueria_leida.tipo_corte, peluqueria_leida.puntos);
        }
        promedio = (total_puntaje/total_barberias);
        printf(" Promedio barberías %s: %i\n", pueblo_actual, promedio);
        printf("---------------------------------------------\n");
        strcpy(pueblo_actual, peluqueria_leida.pueblo);
    }


    fclose(archivo_peluquerias);
}













/*
*   10/09/2020:
*   (EJERCICIO 1 VERSION 2)
*/


//la estructura es dato del problema

typedef struct cerveza {
    char pueblo[MAX_PUEBLO];
    char bar[MAX_BAR];
    int id_tipo_cerveza;
} cerveza_t;

typedef struct cantidades_tipo{
    int tipo_1;
    int tipo_2;
    int tipo_3;
    int tipo_3;
    int tipo_4;
    int tipo_5;
} cantidades_t;

void inicializar_contadores(cantidad_t* contador){
    contador->tipo_1 = 0;
    contador->tipo_2 = 0;
    contador->tipo_3 = 0;
    contador->tipo_4 = 0;
    contador->tipo_5 = 0;
}

//Post: aumenta en uno al contador respectivo según el tipo de cerveza que se tiene (1,2,3,4, ó 5)
void adicionar_segun_tipo(int id_tipo_cerveza, cantidades_t* contador){
    if(id_tipo_cerveza == 1){
        contador_tipos->tipo_1++;
    }
    else if(id_tipo_cerveza == 2){
        contador_tipos->tipo_2++;
    }
    else if(id_tipo_cerveza == 3){
        contador_tipos->tipo_3++;
    }
    else if(id_tipo_cerveza == 4){
        contador_tipos->tipo_4++;
    }
    else if(id_tipo_cerveza == 5){
        contador_tipos->tipo_5++;
    }
}

//Post: imprime la cantidad de cervezas de un bar según su tipo 
void imprimir_cervezas(cantidades_t contador_tipos){
    printf("\t\tCervezas tipo 1:  %i.\n", contador_tipos.tipo_1);
    printf("\t\tCervezas tipo 2:  %i.\n", contador_tipos.tipo_2);
    printf("\t\tCervezas tipo 3:  %i.\n", contador_tipos.tipo_3);
    printf("\t\tCervezas tipo 4:  %i.\n", contador_tipos.tipo_4);
    printf("\t\tCervezas tipo 5:  %i.\n", contador_tipos.tipo_5);
}

//Post: Muestra:
//   -La cantidad de cervezas bebidas DE CADA tipo, agrupadas según el pueblo y luego según el bar en el que se bebieron
//   -La cantidad TOTAL de cervezas bebidas por pueblo.
void listar_cervezas(cerveza_t cervezas_bebidas[MAX_CERVEZAS], int tope_cervezas){
    int i = 0;
    int tipo_actual;
    char pueblo_actual[MAX_PUEBLO];
    char bar_actual[MAX_BAR];
    cantidades_t contador_tipos;
    int total_bebidas_pueblo = 0;
    
    while(i < tope_cervezas){
        strcpy(pueblo_actual, cervezas_bebidas[i].pueblo);
        printf(" %s\n", cervezas_bebidas[i].pueblo);
        while((i < tope_cervezas) && (strcmp(pueblo_actual, cervezas_bebidas[i].pueblo) == 0)){
            inicializar_contadores(&contador_tipos);
            strcpy(bar_actual, cervezas_bebidas[i].bar);
            printf("\t %s:\n", cervezas_bebidas[i].bar);
            while((i < tope_cervezas) && (strcmp(pueblo_actual, cervezas_bebidas[i].pueblo) == 0) && (strcmp(cerveza_actual.bar, cervezas_bebidas[i].bar) == 0)){
                tipo_actual = cervezas_bebidas[i].id_tipo_cerveza;
                adicionar_segun_tipo(tipo_actual, &contador_tipos);
                total_bebidas_pueblo++;
                i++;
            }
            imprimir_cervezas(contador_tipos);
        }
        printf(" Total cervezas en %s: %i.\n", pueblo_actual, total_bebidas_pueblo);
        printf("-----------------------------------------------\n");
    }
}













/*
*   10/09/2020:
*   (EJERCICIO 2 VERSION 1)
*/

#define ARCHIVO_GANDALF "gandalf.dat"
#define ARCHIVO_SARUMAN "saruman.dat"
//Ambos de acceso secuencial ordenados por numero de tiro, compuestos por reg de tiro_t
#define ARCHIVO_SECCIONES "secciones.dat"
//Acceso dir. ordenado por id, compuesto por reg seccion_t. Las secciones son de tipo 1,2,3... (empezando por 1).

//Asumo que se consagra presidente el que consigue más puntos. Y que la seccion -1 corresponde a cuando el tiro no le dio a nada.

typedef struct tiro {
    int tiro_numero;
    int id_seccion;
} tiro_t;

typedef struct seccion {
    int id_seccion;
    int puntaje;
} seccion_t;

void determinar_presidente(){
    FILE* f_gandalf = fopen(ARCHIVO_GANDALF, "r");
    if(f_gandalf == NULL){
        printf("\nError al abrir el archivo: %s", ARCHIVO_GANDALF);
        return;
    }
    FILE* f_saruman = fopen(ARCHIVO_SARUMAN, "r");
    if(f_saruman == NULL){
        printf("\nError al abrir el archivo: %s", ARCHIVO_SARUMAN);
        fclose(f_gandalf);
        return;
    }
    FILE* f_secciones = fopen(ARCHIVO_SECCIONES, "r");
    if(f_secciones == NULL){
        printf("\nError al abrir el archivo: %s", ARCHIVO_SECCIONES);
        fclose(f_gandalf);
        fclose(f_saruman);
        return;
    }

    tiro_t tiro_leido_gand;
    tiro_t tiro_leido_saru;
    seccion_t seccion_leida;
    int puntaje_gandalf = 0;
    int puntaje_saruman = 0;

    fread(&tiro_leido_gand, sizeof(tiro_leido_gand), 1, f_gandalf);
    fread(&tiro_leido_saru, sizeof(tiro_leido_saru), 1, f_saruman);
    while(!feof(f_gandalf)){
        if(tiro_leido_gand.id_seccion > 0){
            fseek(f_secciones, (tiro_leido_gand.id_seccion - 1)*(sizeof(seccion_leida), SEEK_SET));
            fread(&seccion_leida, sizeof(seccion_leida), 1, f_secciones);
            puntaje_gandalf += seccion_leida.puntaje;
        }
        fread(&tiro_leido_gand, sizeof(tiro_leido_gand), 1, f_gandalf);
    }
    while(!feof(f_saruman)){
        if(tiro_leido_saru.id_seccion > 0){
            fseek(f_secciones, (tiro_leido_saru.id_seccion - 1)*(sizeof(seccion_leida)), SEEK_SET);
            fread(&seccion_leida, sizeof(seccion_leida), 1, f_secciones);
            puntaje_saruman += seccion_leida.puntaje;
        }
        fread(&tiro_leido_saru, sizeof(tiro_leido_saru), 1 , f_saruman);
    }

    fclose(f_gandalf);
    fclose(f_saruman);
    fclose(f_secciones);

    mostrar_presidente(puntaje_gandalf, puntaje_saruman);
    //no lo implementé pero es solamente unos ifs de si tal es mayor que tal que lo imprima como ganador.

}
//usar el id seccion leido en los 2 primeros para ir a buscarlo con fseek(archivo_secciones, (id-1)*tamaño, SEEK_SET) en el de secciones, 




















/*
*   10/09/2020:
*   (EJERCICIO 4 VERSION 1)
*/


#define ARCHIVO_MAMA "mama_sam.dat"
#define ARCHIVO_PAPA "papa_sam.dat"
#define ARCHIVO_INTERSECCION "comunes_sam.dat"

typedef struct hobbit {
    char nombre[MAX_NOMBRE];
    char fecha_nacimiento[MAX_FECHA_NACIMIENTO];
    char pareja_de[MAX_NOMBRE];
    int dni;
} hobbit_t;
//Antepasados ordenados por dni de hobbit

//Post: Devuelve -1 si el primer paramero enviado es menor que el segundo, 1 en el caso contrario, 0 si son iguales.
int dni_cmp(int dni_1, int dni_2){
    if(dni_1 < dni_2){
        return -1;
    }
    else if(dni_1 > dni_2){
        return 1;
    }
    else{//Son iguales
        return 0;
    }
}

void verificar_pareja(int* contador_diferidos, char pareja_1[MAX_NOMBRE], char pareja_2[MAX_NOMBRE]){
    if(strcmp(pareja_1, pareja_2) != 0){
        (*contador_diferidos)++;
    }
}


//Post: Devuelve la cantidad de parientes coincidentes antepasados de madre y padre que tienen distinta pareja en cada archivo; ó -1 si no pudo abrir algun archivo.
int conteo_de_diferidos(){
    FILE* f_mama = fopen(ARCHIVO_MAMA, "r");
    if(f_mama == NULL){
        printf("Error al abrir archivo: %s.\n", ARCHIVO_MAMA);
        return -1;
    }
    FILE* f_papa = fopen(ARCHIVO_PAPA, "r");
    if(f_papa == NULL){
        printf("Error al abrir archivo: %s.\n", ARCHIVO_PAPA);
        fclose(f_mama);
        return -1;
    }
    FILE* f_comunes = fopen(ARCHIVO_INTERSECCION, "w");
    if(f_comunes == NULL){
        printf("Error al abrir archivo: %s.\n", ARCHIVO_INTERSECCION);
        fclose(f_mama);
        fclose(f_papa);
        return -1;
    }

    int comparacion_dni;
    int contador_diferidos = 0;
    hobbit_t leido_mama;
    hobit_t leido_papa;

    fread(&leido_mama, sizeof(leido_mama), 1, f_mama);
    fread(&leido_papa, sizeof(leido_papa), 1, f_papa);
    while(!feof(f_mama) && !feof(f_papa)){
        comparacion_dni = dni_cmp(leido_mama.dni, leido_papa.dni);
        if(comparacion_dni > 0){
            fread(&leido_papa, sizeof(leido_papa), 1, f_papa);
        }
        else if(comparacion_dni < 0){
            fread(&leido_mama, sizeof(leido_mama), 1, f_mama);
        }
        else{ //Son iguales
            fwrite(&leido_mama, sizeof(leido_mama), 1, f_comunes);
            verificar_pareja(&contador_diferidos, leido_mama.pareja_de, leido_mama.pareja_de);
            fread(&leido_mama, sizeof(leido_mama), 1, f_mama);
            fread(&leido_papa, sizeof(leido_papa), f_papa);
        }
    }

    fclose(f_comunes);
    fclose(f_mama);
    fclose(f_papa);

    return contador_diferidos;
}

















/*
*   10/09/2020:
*   (EJERCICIO 4 VERSION 2)
*/








































//==================================================================//==================================================================//



















































void imprimir_vector(int vector[MAX_VECTOR], int tope){
    printf("\n\n");
    for(int i = 0; i<tope ; i++){
        printf("\t%i", vector[i]);
    }
    printf("\n\n");
}

//quiero de menor a mayor, por eso uso el max actual para llevarlo a lo ultimo
void seleccion(int vector[MAX_VECTOR], int tope){
    int pos_max_actual;
    for(int i = 0; i < tope; i++){
      pos_max_actual = 0;
        for(int j = 0; j < tope-i ; j++){
            if(vector[pos_max_actual] < vector[j]){
                pos_max_actual = j;
            }
        }
        int aux = vector[pos_max_actual];
        vector[pos_max_actual] = vector[tope-i-1];
        vector[tope-i-1] = aux;
    }
}

/*
void insercion(int vector[MAX_VECTOR], int tope){
    for(int tope_subvector = 0; tope_subvector < tope; tope_subvector++){
        int j = tope_subvector;
        int aux = vector[tope_subvector];
        bool inserte = false;

        while(j>0 && !inserte){
            if(vector[j-1] < aux){
                vector[j]= vector[j-1];
            }
            else{
                vector[j] = aux;
                inserte = true;
            }
            j--;
            
        }
        if(!inserte){
            vector[0] = aux;
        }
        
    }
}
*/


int main(){
    int vector_1[MAX_VECTOR] = {5,4,3,2,1};
    int tope_1 = 5;
    int vector_2[MAX_VECTOR] = {8,5,3,1,0};
    int tope_2 = 5;
    int vector_union[MAX_VECTOR];
    int tope_union = 0;
    
    //insercion(vector, tope);
    //seleccion(vector_1, tope);
    unir_vectores(vector_1, vector_2, tope_1, tope_2)
    imprimir_vector(vector_union, tope_union);

    return 0;
}
