#include "detector_personajes.h"
#include "escape_laboratorio.h"
#include "utiles.h"
#include <time.h>

#define FUENTE_NORMAL "\e[0m"
#define FUENTE_ROJO "\e[31m"
#define FUENTE_ROJO_CLARO "\e[1;31m"
#define FUENTE_VERDE "\e[1;32m"
#define FUENTE_CYAN "\e[36m"
#define FUENTE_FONDO_GRIS "\e[47m"

#define MOV_INICIALES 10
#define ARRIBA 'w'
#define IZQ 'a'
#define ABAJO 's'
#define DER 'd'

#define NIV_1 1
#define NIV_2 2
#define NIV_3 3
#define NIV_4 4

#define JUGANDO 0
#define PERDIDO -1
#define GANADO 1

#define CONTINUAR 'C'
#define CONTINUAR_ALT 'c'

// (Implementacion los sgtes. procedimientos bajo el main)

//Post: Muestra al usuario una breve introduccion al juego y le pregunta si quiere continuar o no.
void mostrar_intro();

//Pre: El usuario ganó el juego.
//Post: Muestra al usuario que ganó.
void mostrar_victoria();

//Pre: El usuario perdió el juego.
//Post: Muestra al usuario que perdió.
void mostrar_derrota();

//Post: Le pregunta al usuario qué movimiento quiere realizar con el personaje en la matriz laboratorio.
void solicitar_movimiento(char* movimiento);

//Pre: El nivel actual no puede ser NIVEL 1. Para este hay una funcion inicializar_personaje en escape_laboratorio.c
//Post: Le asigna los valores iniciales al personaje dependiendo del nivel actual.
void actualizar_personaje(personaje_t* personaje, char tipo_personaje, nivel_t niveles[MAX_NIVELES], int nivel_actual);


int main(){
    srand ((unsigned)time(NULL)); 
    juego_t juego;
    char opcion_elegida = '-';
    char personaje_detectado = '-';
    char movimiento = '-';

    mostrar_intro();
    scanf(" %c", &opcion_elegida);
    if((opcion_elegida != CONTINUAR) && (opcion_elegida != CONTINUAR_ALT)){
        return 0;
    }
    
    system("clear");
    detectar_personaje(&personaje_detectado);
    inicializar_juego(&juego, personaje_detectado);
    mostrar_juego(juego);

    while(estado_juego(juego) == JUGANDO){
        if(estado_nivel(juego.personaje, juego.niveles[juego.nivel_actual-1].salida) == GANADO){
            juego.nivel_actual++;
            actualizar_personaje(&(juego.personaje), personaje_detectado, juego.niveles, juego.nivel_actual);
            mostrar_juego(juego);
        }
        solicitar_movimiento(&movimiento);
        mover_personaje(&juego, movimiento);
        mostrar_juego(juego);
    }
 
    if(estado_juego(juego) == GANADO){
        mostrar_victoria();
    }
    else if(estado_juego(juego) == PERDIDO){
        mostrar_derrota();
    }

    return 0;
}












//========================================================//========================================================//

void mostrar_intro(){
    printf(FUENTE_CYAN"\n\n                            ███████╗███████╗ ██████╗ █████╗ ██████╗ ███████╗    ██████╗ ███████╗██╗         ██╗      █████╗ ██████╗  ██████╗ ██████╗  █████╗ ████████╗ ██████╗ ██████╗ ██╗ ██████╗  \n                            ██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝    ██╔══██╗██╔════╝██║         ██║     ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗██║██╔═══██╗  \n                            █████╗  ███████╗██║     ███████║██████╔╝█████╗      ██║  ██║█████╗  ██║         ██║     ███████║██████╔╝██║   ██║██████╔╝███████║   ██║   ██║   ██║██████╔╝██║██║   ██║  \n                            ██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██╔══╝      ██║  ██║██╔══╝  ██║         ██║     ██╔══██║██╔══██╗██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗██║██║   ██║  \n                            ███████╗███████║╚██████╗██║  ██║██║     ███████╗    ██████╔╝███████╗███████╗    ███████╗██║  ██║██████╔╝╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║██║╚██████╔╝  \n                            ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚══════╝    ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝ ╚═════╝  \n\n"FUENTE_NORMAL);
    printf("\n\n\n\n\n\n\n\n\n                                                 (Maximiza para tener mejor experiencia visual del juego)\n\n                                                 Has sido encontrado husmeando en el laboratorio de Dexter, y este se encuentra muuuy enfadado\n                                                 Sin pensarlo mucho te ha encerrado en uno de los muchisimos cuartos de su laboratorio, el cual\n                                                 está repleto de trampas y artilugios creados por él para mantener alli a los que se atreven a entrar\n                                                 a tocar sus inventos sin su permiso. Además de esto, el cuarto tiene el suelo extremadamente jabonoso, entonces,\n                                                 si te mueves, solo te detendrás al chocar contra una pared. Al entrar serás interrogado por uno de sus Robots, quien, según\n                                                 tus respuestas, detectará el personaje que te ayudara a salir del laboratorio.\n\n                                                 INGRESA:     "FUENTE_VERDE"C"FUENTE_NORMAL" para continuar.     "FUENTE_ROJO"Q"FUENTE_NORMAL" para salir.  (+Enter)\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void mostrar_victoria(){
    printf(FUENTE_VERDE"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n                                             ██╗  ██╗ █████╗ ███████╗    ███████╗███████╗ ██████╗ █████╗ ██████╗  █████╗ ██████╗  ██████╗ \n                                             ██║  ██║██╔══██╗██╔════╝    ██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔══██╗██╔══██╗██╔═══██╗\n                                             ███████║███████║███████╗    █████╗  ███████╗██║     ███████║██████╔╝███████║██║  ██║██║   ██║\n                                             ██╔══██║██╔══██║╚════██║    ██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██╔══██║██║  ██║██║   ██║\n                                             ██║  ██║██║  ██║███████║    ███████╗███████║╚██████╗██║  ██║██║     ██║  ██║██████╔╝╚██████╔\n                                             ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚═╝  ╚═╝╚═════╝  ╚═════╝ \n\n\n\n\n\n\n\n\n\n\n\n\n"FUENTE_NORMAL);
}

void mostrar_derrota(){
    printf(FUENTE_ROJO_CLARO"\n\n\n                                                             Noooooooo, has fallado en escapar :(\n\n                                                              ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n                                                             ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n                                                             ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n                                                             ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n                                                             ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n                                                              ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝\n\n\n\n\n\n\n"FUENTE_NORMAL);
}

void solicitar_movimiento(char* movimiento){
    (*movimiento)='w';
    
    printf("\n                                                           Presiona una de las teclas(+Enter) para moverte:   (minúsculas)\n                                                           w: arriba   a: izquierda   s: abajo   d: derecha\n");
    scanf(" %c", movimiento);
    while(((*movimiento) != ARRIBA) && ((*movimiento) != IZQ) && ((*movimiento) != ABAJO) && ((*movimiento) != DER)){
        printf(FUENTE_ROJO_CLARO"                                                           Ese no es un movimiento válido!\n"FUENTE_NORMAL);
        printf("\n                                                           Ingresa una de las teclas(+Enter) para moverte:   (minúsculas)\n                                                           w: arriba   a: izquierda   s: abajo   d: derecha\n");
    scanf(" %c", movimiento);
    }
    
}


void actualizar_personaje(personaje_t* personaje, char tipo_personaje, nivel_t niveles[MAX_NIVELES], int nivel_actual){
    personaje->tipo = tipo_personaje;
    personaje->tiene_llave = false;
    personaje->posicion.fil = niveles[nivel_actual - 1].entrada.fil;
    personaje->posicion.col = niveles[nivel_actual - 1].entrada.col;
    personaje->movimientos += MOV_INICIALES;
    personaje->presiono_interruptor = false;
}