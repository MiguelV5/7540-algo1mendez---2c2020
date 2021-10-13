#include "encargado_de_imaginarios.h"

#define ARCHIVO_AMIGOS_MANSION "amigos_mansion.dat"

#define MAX_POSIBLES 100 //Asumiendo, que un niño no puede haber adoptado más de 100 amigos imaginarios previos.

#define FORMATO_REQUISITOS "%[^;];%c%i;%[^;];%[^\n]\n"
#define FORMATO_AMIGOS_PREVIOS "%[^\n]\n"
#define FORMATO_AMIGO_NUEVO "\n%s"

#define FUENTE_ROJO_CLARO "\e[1;31m"
#define FUENTE_VERDE "\e[1;32m"
#define FUENTE_AZUL_CLARO "\e[1;34m"
#define FUENTE_NORMAL "\e[0m"

const int TOTAL_LEIDOS_PREVIOS = 1;
const int TOTAL_LEIDOS_REQUISITOS = 5;

const char MENOR = '<';
const char MAYOR = '>';
const char IGUAL = '=';

const int SIN_VERIFICADOS = -1;
const int SIN_LEIDOS = 0;


typedef struct requisitos {
    char color_requerido[MAX_COLOR];
    char virtud_requerida[MAX_DESCRIPCION];
    char defecto_a_evitar[MAX_DESCRIPCION];
    char operador;
    int altura_requerida;
} requisitos_t;

typedef struct elegido_posible {
    char nombre[MAX_NOMBRE];
    bool fue_amigo;
} posible_t;



//Post: Imprime los campos que caracterizan a un amigo imaginario.
void mostrar_caracteristicas(amigo_t amigo){
    printf(FUENTE_AZUL_CLARO"\n\tNombre:"FUENTE_NORMAL" %s\n", amigo.nombre);
    printf(FUENTE_AZUL_CLARO"\tColor:"FUENTE_NORMAL" %s\n", amigo.color);
    printf(FUENTE_AZUL_CLARO"\tAltura:"FUENTE_NORMAL" %i\n", amigo.altura);
    printf(FUENTE_AZUL_CLARO"\tVirtudes:\n"FUENTE_NORMAL);
    for(int i = 0; i < amigo.tope_virtudes; i++){
        printf("\t - %s\n", amigo.virtudes[i].descripcion);
    }
    printf(FUENTE_AZUL_CLARO"\tDefectos:\n"FUENTE_NORMAL);
    for(int i = 0; i < amigo.tope_defectos; i++){
        printf("\t - %s\n", amigo.defectos[i].descripcion);
    }
}


//Post: Devuelve true si al menos alguna de las virtudes coincide con la requerida, o false si ninguna lo hace.
bool comprobacion_virtudes(aspecto_t virtudes[MAX_VIRTUDES], int tope_virtudes, char virtud_requerida[MAX_DESCRIPCION]){
    bool cumple = false;
    int i = 0;
    while((i < tope_virtudes) && (!cumple)){
        if(strcmp(virtud_requerida, virtudes[i].descripcion) == 0){
            cumple = true;
        }
        i++;
    }
    return cumple;
}

//Post: Devuelve true si NINGÚN defecto coincide con el defecto a evitar, o false si al menos uno lo hace.
bool comprobacion_defectos(aspecto_t defectos[MAX_DEFECTOS], int tope_defectos, char defecto_a_evitar[MAX_DESCRIPCION]){
    bool coincide = false;
    int i = 0;
    while((i < tope_defectos) && (!coincide)){
        if(strcmp(defecto_a_evitar, defectos[i].descripcion) == 0){
            coincide = true;
        }
        i++;
    }
    return !coincide;
}


//Post: Devuelve true si el amigo cumple todos los requerimientos del niño y está en la mansión, o false en caso contrario.
bool requisitos_cumplidos(amigo_t amigo, requisitos_t requisitos){
    bool cumple = false;
    bool virtud_coincide = comprobacion_virtudes(amigo.virtudes, amigo.tope_virtudes, requisitos.virtud_requerida);
    bool defecto_evitado = comprobacion_defectos(amigo.defectos, amigo.tope_defectos, requisitos.defecto_a_evitar);

    if(requisitos.operador == MENOR){
        if((amigo.esta_en_mansion) && (strcmp(amigo.color, requisitos.color_requerido) == 0) && (amigo.altura <    requisitos.altura_requerida) && (virtud_coincide) && (defecto_evitado)){
            cumple = true;
        }
    }
    else if(requisitos.operador == MAYOR){
        if((amigo.esta_en_mansion) && (strcmp(amigo.color, requisitos.color_requerido) == 0) && (amigo.altura >    requisitos.altura_requerida) && (virtud_coincide) && (defecto_evitado)){
            cumple = true;
        }
    }
    else if(requisitos.operador == IGUAL){
        if((amigo.esta_en_mansion) && (strcmp(amigo.color, requisitos.color_requerido) == 0) && (amigo.altura ==    requisitos.altura_requerida) && (virtud_coincide) && (defecto_evitado)){
            cumple = true;
        }
    }

    return cumple;
}


//Post: Revisa si un amigo imaginario ya había sido adoptado por el niño anteriormente o no.
void validar_posesion_previa(posible_t* amigo_posible, char amigos_previos[MAX_POSIBLES][MAX_NOMBRE], int tope_previos){
    int i = 0;
    amigo_posible->fue_amigo = false;
    while((i < tope_previos) && (!(amigo_posible->fue_amigo))){
        if(strcmp(amigo_posible->nombre, amigos_previos[i]) == 0){
            amigo_posible->fue_amigo = true;
        }
        i++;
    }
}



/*==============================================================//==============================================================*/


/*
*   Pre: 
*    El nombre del archivo viene dado por linea de comando.
*   Post:
*    Intenta elegir un amigo imaginario nuevo para el niño.
*    Si el archivo de nombre recibido no se pudo abrir correctamente o no pudo elegir, 
*    no se modifican archivos.
*/
void elegir_amigo(char nombre_archivo_txt[MAX_COMANDO]){
    FILE* amigos_ninio;
    FILE* amigos_mansion;
    amigos_ninio = fopen(nombre_archivo_txt, "r+");
    amigos_mansion = fopen(ARCHIVO_AMIGOS_MANSION, "r+");
    if(amigos_ninio == NULL){
        printf("No se pudo abrir el archivo %s brindado o no existe en el directorio\n", nombre_archivo_txt);
        return;
    }
    if(amigos_mansion == NULL){
        printf("Error al abrir archivo: %s\n", ARCHIVO_AMIGOS_MANSION);
        return;
    }

    requisitos_t requisitos;
    amigo_t amigo_leido;
    posible_t amigos_posibles[MAX_POSIBLES];
    int tope_posibles = 0;
    int ultimo_verificado = SIN_VERIFICADOS; // Uso: Como el archivo binario está ordenado por nombre de amigo (de forma ascendente), el último amigo que se verifique como adecuado buscando en el archivo de manera secuencial va a ser el de mayor nombre. Se inicializa en -1 en caso de que ningun elegible posible cumpla condiciones de verificación.

    char amigos_previos[MAX_POSIBLES][MAX_NOMBRE]; //Nombres de todos los amigos anteriormente adoptados del niño (tener en cuenta la nota en la definición de MAX_POSIBLES).
    int tope_previos = 0;

    int previos_leidos;
    int requisitos_leidos;

    requisitos_leidos = fscanf(amigos_ninio, FORMATO_REQUISITOS, requisitos.color_requerido, &requisitos.operador, &(requisitos.altura_requerida), requisitos.virtud_requerida, requisitos.defecto_a_evitar);
    
    //Se guarda toda la info de los amigos previos del niño:
    previos_leidos = fscanf(amigos_ninio, FORMATO_AMIGOS_PREVIOS, amigos_previos[tope_previos]);
    tope_previos++;
    while(previos_leidos == TOTAL_LEIDOS_PREVIOS){
        previos_leidos = fscanf(amigos_ninio, FORMATO_AMIGOS_PREVIOS, amigos_previos[tope_previos]);
        tope_previos++;    
    }
    
    //Se filtran los nuevos amigos posibles para el niño:
    fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
    while( (!feof(amigos_mansion)) && (requisitos_leidos == TOTAL_LEIDOS_REQUISITOS) ){
        if(requisitos_cumplidos(amigo_leido, requisitos) == true){
            strcpy(amigos_posibles[tope_posibles].nombre, amigo_leido.nombre);
            validar_posesion_previa(&(amigos_posibles[tope_posibles]), amigos_previos, tope_previos);
            if(amigos_posibles[tope_posibles].fue_amigo == false){
                ultimo_verificado = tope_posibles;
            }
            tope_posibles++;
        }
        fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
    }

    //Sabiendo cual es ese ultimo amigo verificado (en caso de haberlo);[ver uso de la variable 'ultimo_verificado' en su definición], se busca en la mansión y se desaloja, a la vez que es adoptado por el niño.
    if(ultimo_verificado > SIN_VERIFICADOS){
        fseek(amigos_mansion, (-1)*((int)sizeof(amigo_leido)), SEEK_END);
        fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
        while(strcmp(amigos_posibles[ultimo_verificado].nombre, amigo_leido.nombre) != 0){
            fseek(amigos_mansion, (-2)*((int)sizeof(amigo_leido)), SEEK_CUR);
            fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
        }
        //Desalojo de mansión:
        fseek(amigos_mansion, (-1)*((int)sizeof(amigo_leido)), SEEK_CUR);
        amigo_leido.esta_en_mansion = false;
        fwrite(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
        //Adopción por el niño:
        fprintf(amigos_ninio, FORMATO_AMIGO_NUEVO, amigo_leido.nombre);
        printf(FUENTE_VERDE"\n\n\tEl amigo"FUENTE_NORMAL" - %s - "FUENTE_VERDE"fue adoptado exitosamente!\n\n"FUENTE_NORMAL, amigo_leido.nombre);
    }
    else if(ultimo_verificado == SIN_VERIFICADOS){
        printf(FUENTE_ROJO_CLARO"\n\n\tNingun amigo presente en la mansión cumplió tus requisitos :c\n\n"FUENTE_NORMAL);
    }

    fclose(amigos_ninio);
    fclose(amigos_mansion);
}



/* 
*   Post:
*    Lee el archivo que contiene a los amigos en la mansión para mostrar los que estén presentes.
*/
void listar_amigos(){
    FILE* amigos_mansion;

    amigos_mansion = fopen(ARCHIVO_AMIGOS_MANSION, "r");
    if(amigos_mansion == NULL){
        printf("Error al abrir archivo: %s\n", ARCHIVO_AMIGOS_MANSION);
        return;
    }

    amigo_t amigo;
    size_t leidos = fread(&amigo, sizeof(amigo), 1, amigos_mansion);
    while(leidos > SIN_LEIDOS){
        if(amigo.esta_en_mansion){
            mostrar_caracteristicas(amigo);
        }
        leidos = fread(&amigo, sizeof(amigo), 1, amigos_mansion);
    }

    fclose(amigos_mansion);
}



/*
*   Pre: 
*    -El nombre del amigo a devolver viene dado por linea de comando.
*    -El amigo a devolver tiene que existir en el archivo de la mansión.
*   Post: 
*    Intenta devolver un amigo imaginario del niño a la mansión.
*    Si no se pudo hacer la devolución, no se modifica el archivo.
*/
void devolver_amigo(char amigo_a_devolver[MAX_NOMBRE]){
    FILE* amigos_mansion;
    amigos_mansion = fopen(ARCHIVO_AMIGOS_MANSION, "r+");
    if(amigos_mansion == NULL){
        printf("Error al abrir archivo: %s\n", ARCHIVO_AMIGOS_MANSION);
        return;
    }
    
    bool se_devolvio = false;
    amigo_t amigo_leido;
    size_t leidos = fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
    while((leidos > SIN_LEIDOS) && (!se_devolvio)){
        if((strcmp(amigo_a_devolver, amigo_leido.nombre) == 0) && (amigo_leido.esta_en_mansion == false)){
            fseek(amigos_mansion, (-1)*((int)sizeof(amigo_leido)), SEEK_CUR);
            amigo_leido.esta_en_mansion = true;
            fwrite(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
            se_devolvio = true;
            printf(FUENTE_VERDE"\n\n\tSe devolvió exitosamente!\n\n"FUENTE_NORMAL);
        }
        if(!se_devolvio){
            leidos = fread(&amigo_leido, sizeof(amigo_leido), 1, amigos_mansion);
        }
    }

    if(!se_devolvio){
        printf(FUENTE_ROJO_CLARO"\n\n\tNo se pudo devolver el amigo o ya se encontraba en la mansión.\n\n"FUENTE_NORMAL);
    }

    fclose(amigos_mansion);
}
