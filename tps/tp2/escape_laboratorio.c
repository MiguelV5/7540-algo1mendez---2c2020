#include "escape_laboratorio.h"
#include "utiles.h"

#define FUENTE_NORMAL "\e[0m"
#define FUENTE_NEGRO "\e[30m"
#define FUENTE_ROJO "\e[31m"
#define FUENTE_ROJO_CLARO "\e[1;31m"
#define FUENTE_VERDE "\e[1;32m"
#define FUENTE_NARANJA "\e[1;33m"
#define FUENTE_AZUL_CLARO "\e[1;34m"
#define FUENTE_PURPURA "\e[1;35m"
#define FUENTE_CYAN "\e[1;36m"
#define FUENTE_FONDO_NEGRO "\e[40m"
#define FUENTE_FONDO_NARANJA "\e[1;43m"
#define FUENTE_FONDO_AZUL_C "\e[44m"
#define FUENTE_FONDO_GRIS "\e[47m"

#define DIMENSION_MIN 12
#define DIMENSION_MAX 17

#define RANGO_CORRIDO 1
#define DELIMITADOR_BORDE 2

#define BLUE 'B'
#define PURO_HUESO 'H'
#define CORAJE 'C'
#define POLLITO 'P'
#define JOHNNY_BRAVO 'J'
#define BELLOTA 'S'

// Los diferenciadores son para poder imprimir colores distintos para elementos que justo coinciden con las constantes del tipo de personaje sin cambiar sus convenciones requerida.
// Por ej.: Bellota es 'S', asi como Salida es 'S', los imprimiría con la misma fuente y fondo sin diferenciador.
#define DIFERENCIADOR_BLUE '1' 
#define DIFERENCIADOR_POLLITO '2'
#define DIFERENCIADOR_BELLOTA '3'

const int NIV_1 = 1;
const int NIV_2 = 2;
const int NIV_3 = 3;
const int NIV_4 = 4;

const int MOV_INICIALES = 10; // MOV: Movimientos. 

const int GANADO = 1;
const int PERDIDO = -1;
const int JUGANDO = 0;

const char PARED = ' ';
const char VACIO = '.';

const char BALDOSA_PINCHE = 'P';
const char MONEDA = 'M';
const char LLAVE = 'L';
const char BOMBA = 'B';
const char INTERRUPTOR = 'I';
const char ENTRADA = 'E';
const char SALIDA = 'S';
const char BALDOSA_TP = 'T';    // TP: Teletransportadora.
const char GUARDIA = 'G';

const char ARRIBA = 'w';
const char IZQ = 'a';
const char ABAJO = 's';
const char DER = 'd';




//     FUNCIONES/PROCEDIMIENTOS DE ASIGNACIONES Y MUESTREO DE LA MATRIZ LABORATORIO:
//     Nota: mapa y matriz laboratorio  ------> son indistintos.

//Post: Asigna la cantidad de elementos dependiendo del numero de nivel que se le pase.
void asignar_num_items(int num_nivel, int* cant_pinches, int* cant_guardias, bool* hay_bomba){
    if(num_nivel == 1){
        (*cant_pinches) = 4;
        (*cant_guardias) = 2;
        (*hay_bomba) = false;
    }
    else if(num_nivel == 2){
        (*cant_pinches) = 6;
        (*cant_guardias) = 3;
        (*hay_bomba) = false;
    }
    else if(num_nivel == 3){
        (*cant_pinches) = 6;
        (*cant_guardias) = 3;
        (*hay_bomba) = true;
    }
    else if(num_nivel == 4){
        (*cant_pinches) = 10;
        (*cant_guardias) = 4;
        (*hay_bomba) = true;
    }
}

//Pre: La dimension debe venir inicializada según el nivel actual.
//Post: Inicializa la matriz laboratorio con un punto que representa VACIO ('.').
void limpiar_lab(char mapa[DIMENSION_MAX][DIMENSION_MAX], int dimension_lab){
    for(int fil = 0; fil < dimension_lab; fil++){
        for(int col = 0; col < dimension_lab; col++){
            mapa[fil][col] = VACIO;
        }
    }
}

//Pre: El mapa (matriz lab) viene previamente inicializado con VACIO y ya se tienen las coordenadas de todas las paredes.
//Post: Rellena la matriz mapa con PAREDES (' ') en las coordenadas dadas.
void insertar_paredes(char mapa[DIMENSION_MAX][DIMENSION_MAX], coordenada_t paredes[MAX_PAREDES], int tope_paredes){
    for(int i = 0; i < tope_paredes; i++){
        mapa[paredes[i].fil][paredes[i].col] = PARED;
    }
}

//Pre: -Las posiciones de los obstaculos ya fueron previamente validadas.
//     -El tope_obstaculos viene correctamente aumentado con el valor correspondiente al nivel actual.
//Post: Inserta los obstaculos en la matriz lab a mostrar.
void insertar_obstaculos(char mapa[DIMENSION_MAX][DIMENSION_MAX], elemento_t obstaculos[MAX_OBSTACULOS], int tope_obstaculos){
    for(int i = 0; i < tope_obstaculos; i++){
        if(obstaculos[i].tipo == BALDOSA_PINCHE){
            mapa[obstaculos[i].posicion.fil][obstaculos[i].posicion.col] = BALDOSA_PINCHE;
        }
        else if(obstaculos[i].tipo == GUARDIA){
            mapa[obstaculos[i].posicion.fil][obstaculos[i].posicion.col] = GUARDIA;
        }
        else if(obstaculos[i].tipo == BOMBA){
            mapa[obstaculos[i].posicion.fil][obstaculos[i].posicion.col] = BOMBA;
        }
    }
}

//Pre: -Las posiciones de las herramientas ya fueron previamente validadas.
//     -El tope_herramientas viene correctamente aumentado con el valor correspondiente al nivel actual
//Post: Inserta las herramientas en la matriz lab a mostrar.
void insertar_herramientas(char mapa[DIMENSION_MAX][DIMENSION_MAX], elemento_t herramientas[MAX_HERRAMIENTAS], int tope_herramientas, bool presiono_interruptor, int nivel_actual){
    for(int i = 0; i < tope_herramientas; i++){
        if((herramientas[i].tipo == LLAVE) && ((presiono_interruptor == true) || (nivel_actual == NIV_1) || (nivel_actual == NIV_2))){
            mapa[herramientas[i].posicion.fil][herramientas[i].posicion.col] = LLAVE;
        }
        else if(herramientas[i].tipo == MONEDA){
            mapa[herramientas[i].posicion.fil][herramientas[i].posicion.col] = MONEDA;
        }
        else if(herramientas[i].tipo == BALDOSA_TP){
            mapa[herramientas[i].posicion.fil][herramientas[i].posicion.col] = BALDOSA_TP;
        }
        else if(herramientas[i].tipo == INTERRUPTOR){
            mapa[herramientas[i].posicion.fil][herramientas[i].posicion.col] = INTERRUPTOR;
        }
    }
}

//Pre: Las coordenadas de la entrada ya fueron previamente validadas.
//Post: Inserta la entrada en la matriz a mostrar.
void insertar_entrada(char mapa[DIMENSION_MAX][DIMENSION_MAX], coordenada_t entrada){
    mapa[entrada.fil][entrada.col] = ENTRADA;
}

//Pre: La posicion y el tipo del personaje deben haberse inicializado previamente.
//Post: Inserta el personaje detectado a la matriz o los diferenciadores(Explicados en la definición de constantes DIFERENCIADOR).
void insertar_personaje(char mapa[DIMENSION_MAX][DIMENSION_MAX], coordenada_t posicion, char personaje_detectado){
    if(personaje_detectado == BLUE){
        mapa[posicion.fil][posicion.col] = DIFERENCIADOR_BLUE;
    }
    else if(personaje_detectado == POLLITO){
        mapa[posicion.fil][posicion.col] = DIFERENCIADOR_POLLITO;
    }
    else if(personaje_detectado == BELLOTA){
        mapa[posicion.fil][posicion.col] = DIFERENCIADOR_BELLOTA;
    }
    else{
        mapa[posicion.fil][posicion.col] = personaje_detectado;
    }
}

//Pre: Las coordenadas de la salida ya fueron previamente validadas.
//Post: Inserta la salida en la matriz a mostrar.
void insertar_salida(char mapa[DIMENSION_MAX][DIMENSION_MAX], coordenada_t salida, bool tiene_llave){
    if(tiene_llave == true){
        mapa[salida.fil][salida.col] = SALIDA;
    }
}

//Post: Muestra el título del juego.
void mostrar_titulo(){
    printf(FUENTE_CYAN"\n\n                            ███████╗███████╗ ██████╗ █████╗ ██████╗ ███████╗    ██████╗ ███████╗██╗         ██╗      █████╗ ██████╗  ██████╗ ██████╗  █████╗ ████████╗ ██████╗ ██████╗ ██╗ ██████╗  \n                            ██╔════╝██╔════╝██╔════╝██╔══██╗██╔══██╗██╔════╝    ██╔══██╗██╔════╝██║         ██║     ██╔══██╗██╔══██╗██╔═══██╗██╔══██╗██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗██║██╔═══██╗  \n                            █████╗  ███████╗██║     ███████║██████╔╝█████╗      ██║  ██║█████╗  ██║         ██║     ███████║██████╔╝██║   ██║██████╔╝███████║   ██║   ██║   ██║██████╔╝██║██║   ██║  \n                            ██╔══╝  ╚════██║██║     ██╔══██║██╔═══╝ ██╔══╝      ██║  ██║██╔══╝  ██║         ██║     ██╔══██║██╔══██╗██║   ██║██╔══██╗██╔══██║   ██║   ██║   ██║██╔══██╗██║██║   ██║  \n                            ███████╗███████║╚██████╗██║  ██║██║     ███████╗    ██████╔╝███████╗███████╗    ███████╗██║  ██║██████╔╝╚██████╔╝██║  ██║██║  ██║   ██║   ╚██████╔╝██║  ██║██║╚██████╔╝  \n                            ╚══════╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚═╝     ╚══════╝    ╚═════╝ ╚══════╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝ ╚═════╝  \n\n"FUENTE_NORMAL);
}

//Post: Imprime por pantalla una breve explicación de la funcionalidad de los elementos que observan en la matriz laboratorio. 
void mostrar_reglas(){
    mostrar_titulo();

    printf("                                                           Las MONEDAS "FUENTE_NARANJA" M "FUENTE_NORMAL" suman un movimiento adicional.\n\n                                                           BALDOSAS PINCHE "FUENTE_FONDO_NARANJA" P "FUENTE_NORMAL" quitan dos movimientos por cada una que pises.\n\n                                                           En caso de haber BOMBA "FUENTE_ROJO_CLARO" B "FUENTE_NORMAL" o GUARDIAS ROBOT "FUENTE_ROJO" G "FUENTE_NORMAL", estos te despojarán de movimientos si te los topas.\n\n                                                           Las BALDOSAS TELETRANSPORTADORAS "FUENTE_FONDO_GRIS FUENTE_NEGRO" T "FUENTE_NORMAL" de Dexter te dejarán encima de alguna otra de las mismas.\n\n");
}

//Pre: El tipo de personaje ya debe haber sido inicializado.
//Post: Imprime por pantalla la habilidad del mismo.
void mostrar_habilidad(char personaje){
    if((personaje == BLUE)){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"BLUE (B),"FUENTE_VERDE" por ser amigo imaginario puede REVIVIR una vez si pierdes.\n\n");
    }
    else if(personaje == BELLOTA){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"BELLOTA (S),"FUENTE_VERDE" por ser superpoderosa puede REVIVIR una vez si pierdes.\n\n");
    }
    else if(personaje == PURO_HUESO){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"PURO HUESO (H),"FUENTE_VERDE" por ser esqueletico es inmune a las BALDOSAS PINCHE "FUENTE_NORMAL FUENTE_FONDO_NARANJA" P "FUENTE_NORMAL".\n\n");
    }
    else if(personaje == POLLITO){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"POLLITO (P),"FUENTE_VERDE" por ser exageradamente delgado es inmune a las BALDOSAS PINCHE "FUENTE_NORMAL FUENTE_FONDO_NARANJA" P "FUENTE_NORMAL".\n\n");
    }
    else if(personaje == JOHNNY_BRAVO){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"JOHNNY BRAVO (J),"FUENTE_VERDE" por ser ultra fachero es inmune a los GUARDIAS ROBOT "FUENTE_ROJO" G "FUENTE_NORMAL".\n\n");
    }
    else if(personaje == CORAJE){
        printf(FUENTE_VERDE"\n                                                           Tu personaje es: "FUENTE_NORMAL"CORAJE (C),"FUENTE_VERDE" por ser tan tierno es inmune a los GUARDIAS ROBOT "FUENTE_ROJO" G "FUENTE_NORMAL".\n\n");
    }
}

//Pre: El personaje ya debe tener todos sus campos inicializados.
//Post: Muestra datos importantes del nivel actual al usuario.
void mostrar_datos_nivel(int nivel_actual, personaje_t personaje){
    mostrar_reglas();

    printf(FUENTE_CYAN"\n                                                                                     ==========================\n\n                                                                                              Nivel %i\n\n                                                                                     ==========================\n\n"FUENTE_NORMAL, nivel_actual);
    
    printf(FUENTE_AZUL_CLARO"                                                           Movimientos restantes: %i     ", personaje.movimientos);

    if((personaje.presiono_interruptor == true) && (nivel_actual == NIV_3 || nivel_actual == NIV_4)){
        printf(FUENTE_VERDE "Presionaste el INTERRUPTOR "FUENTE_PURPURA" I "FUENTE_VERDE"! La LLAVE (L) se hizo visible.   " FUENTE_NORMAL);
    }
    else if((personaje.presiono_interruptor == false) && (nivel_actual == NIV_3 || nivel_actual == NIV_4)){
        printf(FUENTE_ROJO_CLARO "Obten el INTERRUPTOR "FUENTE_PURPURA" I "FUENTE_ROJO_CLARO" para visualizar la LLAVE "FUENTE_VERDE"(L)"FUENTE_NORMAL"    ");
    }
    else if((personaje.tiene_llave == false) && ((personaje.presiono_interruptor == true) || (nivel_actual == NIV_1) || (nivel_actual == NIV_2))){
        printf(FUENTE_ROJO_CLARO"Obten la LLAVE "FUENTE_VERDE" L " FUENTE_ROJO_CLARO" para visualizar la salida    "FUENTE_NORMAL);
    }
    else if(personaje.tiene_llave == true){
        printf(FUENTE_VERDE "Obtuviste la LLAVE (L)! La SALIDA " FUENTE_NORMAL FUENTE_FONDO_NEGRO" S "FUENTE_NORMAL FUENTE_VERDE" se hizo visible.   " FUENTE_NORMAL);
    }
    printf("\n\n");
    mostrar_habilidad(personaje.tipo);
}


// Pre: Recibe la matriz mapa de un nivel con todo inicializado segun el nivel correspondiente.
// Post: Imprime por pantalla la matriz.
void mostrar_laboratorio(char mapa[DIMENSION_MAX][DIMENSION_MAX], int dimension_lab, int nivel_actual){
    for(int i = 0; i < dimension_lab; i++){
        printf("\n                                                                           ");
        for(int j = 0; j < dimension_lab; j++){
            if(mapa[i][j] == PARED){
                printf(FUENTE_FONDO_AZUL_C FUENTE_NEGRO" %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == BALDOSA_PINCHE){
                printf(FUENTE_FONDO_NARANJA " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == BALDOSA_TP){
                printf(FUENTE_FONDO_GRIS FUENTE_NEGRO" %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == GUARDIA){
                printf(FUENTE_ROJO " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == BOMBA){
                printf(FUENTE_ROJO_CLARO " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == MONEDA){
                printf(FUENTE_NARANJA " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == LLAVE){
                printf(FUENTE_VERDE " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == INTERRUPTOR){
                printf(FUENTE_PURPURA " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == ENTRADA || mapa[i][j] == SALIDA){
                printf(FUENTE_FONDO_NEGRO " %c " FUENTE_NORMAL, mapa[i][j]);
            }
            else if(mapa[i][j] == DIFERENCIADOR_BLUE){
                printf(" B ");
            }
            else if(mapa[i][j] == DIFERENCIADOR_POLLITO){
                printf(" P ");
            }
            else if(mapa[i][j] == DIFERENCIADOR_BELLOTA){
                printf(" S ");
            }
            else{
                printf(" %c ", mapa[i][j]);
            }
        }
    }
    printf("\n\n");
    detener_el_tiempo((float) 0.045);
}



//     FUNCIONES DE VALIDEZ:

// Post: Devuelve true si cierta posicion de un nivel está disponible para usarse o false si está ocupada por alguna pared u obstáculo. 
bool validez_obstaculos(nivel_t nivel, coordenada_t posicion){
    bool es_pos_valida = true;
    for(int i = 0; (i < nivel.tope_paredes) && (es_pos_valida); i++){
        if((posicion.fil == nivel.paredes[i].fil) && (posicion.col == nivel.paredes[i].col)){
            es_pos_valida = false;
        }
    }
    if(es_pos_valida == false){
        return false;
    }
    for(int i = 0; (i < nivel.tope_obstaculos) && (es_pos_valida); i++){
        if((posicion.fil == nivel.obstaculos[i].posicion.fil) && (posicion.col == nivel.obstaculos[i].posicion.col)){
            es_pos_valida = false;
        }
    }
    return es_pos_valida;
}

// Post: Devuelve true si cierta posicion de un nivel está disponible para usarse o false si está ocupada por alguna herramienta o por algo de lo que verifica validez_obstaculos.
bool validez_herramientas(nivel_t nivel, coordenada_t posicion){
    bool es_pos_valida = true;
    es_pos_valida = validez_obstaculos(nivel, posicion);
    for(int i = 0; (i < nivel.tope_herramientas) && (es_pos_valida); i++){
        if((posicion.fil == nivel.herramientas[i].posicion.fil) && (posicion.col == nivel.herramientas[i].posicion.col)){
            es_pos_valida = false;
        }
    }
    return es_pos_valida;
}


// Post: Devuelve true si cierta posicion de un nivel está disponible para usarse como ENTRADA o está ocupada por algo de lo que verifica validez_herramientas.
bool validez_entrada(nivel_t nivel, coordenada_t posicion){
    bool es_pos_valida = true;
    es_pos_valida = validez_herramientas(nivel, posicion);
    return es_pos_valida;
} 

// Post: Devuelve true si cierta posicion de un nivel está disponible para usarse como SALIDA o false si está ocupada por algo de lo que verifica validez_herramientas o por la entrada.
bool validez_salida(nivel_t nivel, coordenada_t posicion){
    bool es_pos_valida = true;
    es_pos_valida = validez_herramientas(nivel, posicion);
    if(es_pos_valida == false){
        return false;
    }
    
    if((posicion.fil == nivel.entrada.fil) && (posicion.col == nivel.entrada.col)){
        es_pos_valida = false;
    }

    return es_pos_valida;
} 

// Post: Devuelve true si cierta posicion de un nivel está disponible para usarse como reposicionamiento del GUARDIA ROBOT o false si está ocupada por algo de lo que verifica validar_salida, por la salida misma o por la posicion actual del jugador.
//Nota: NO se puede simplemente llamar a validez_salida porque no se debe comparar la posicion nueva del GUARDIA con ella misma, y al final de las llamadas, en validez_obstaculos se compara con todo el vector de obstaculos incluyendo al mismo guardia. (Loop inf)
bool validez_reposicion(nivel_t nivel, coordenada_t posicion, coordenada_t pos_personaje){
    bool es_pos_valida = true;

    // Paredes:
    for(int i = 0; (i < nivel.tope_paredes) && (es_pos_valida); i++){
        if((posicion.fil == nivel.paredes[i].fil) && (posicion.col == nivel.paredes[i].col)){
            es_pos_valida = false;
        }
    }
    if(es_pos_valida == false){
        return false;
    }

    // Obstaculos (Leer Nota en firma):
    for(int i = 0; (i < nivel.tope_obstaculos) && (es_pos_valida); i++){
        while(nivel.obstaculos[i].tipo == GUARDIA){
            i++;
        }
        if((posicion.fil == nivel.obstaculos[i].posicion.fil) && (posicion.col == nivel.obstaculos[i].posicion.col)){
            es_pos_valida = false;
        }
    }
    if(es_pos_valida == false){
        return false;
    }

    // Herramientas:
    for(int i = 0; (i < nivel.tope_herramientas) && (es_pos_valida); i++){
        if((posicion.fil == nivel.herramientas[i].posicion.fil) && (posicion.col == nivel.herramientas[i].posicion.col)){
            es_pos_valida = false;
        }
    }
    if(es_pos_valida == false){
        return false;
    }
    
    // Restantes:
    if((posicion.fil == nivel.entrada.fil) && (posicion.col == nivel.entrada.col)){
        return false;
    }
    if((posicion.fil == nivel.salida.fil) && (posicion.col == nivel.salida.col)){
        return false;
    }
    if((posicion.fil == pos_personaje.fil) && (posicion.col == pos_personaje.col)){
        return false;
    }

    return es_pos_valida;
}




//    PROCEDIMIENTOS DE ASIGNACION DE COORDENADAS Y MODIFICACION DE VECTORES (OBSTACULOS/HERRAMIENTAS):

// Nota: DELIMITADOR_BORDE==2 le resta a la dimension para que no cuente los bordes de la matriz y RANGO_CORRIDO==1 para que no empiece en el borde inicial de la matriz.

//Pre: La cantidad de pinches viene inicializada según el numero_nivel.
//Post: Asigna coordenadas aleatorias para la baldosa pinche inicial y coordenadas contiguas entre sí para las demás. 
void obtener_pinches(int numero_nivel, nivel_t* nivel, int cantidad_pinches){
    bool es_pos_valida = false;
    nivel->tope_obstaculos = 0;
    int i = 0;
    int j = 1;   //j es una variable auxiliar para obtención de pinches adyacentes.
    
    nivel->obstaculos[i].tipo = BALDOSA_PINCHE;
    
    while(!es_pos_valida){
        if(numero_nivel % 2 != 0){
            nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        else{
            nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
    }
    nivel->tope_obstaculos++;

    //Pinches adyacentes: La j se encarga de revisar cada baldosa pinche puesta anteriormente (iniciando desde la ultima que se puso) en caso de que una de las mismas no tenga disponibilidad contigua para colocar la baldosa que sigue.
    for(i = 1; i < cantidad_pinches; i++){
        j = 1;
        es_pos_valida = false;
        nivel->obstaculos[i].tipo = BALDOSA_PINCHE;
        while((j <= (nivel->tope_obstaculos)) && (!es_pos_valida)){
            nivel->obstaculos[i].posicion.fil = (nivel->obstaculos[i-j].posicion.fil)+1;
            nivel->obstaculos[i].posicion.col = nivel->obstaculos[i-j].posicion.col;
            es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
            if(!es_pos_valida){
                nivel->obstaculos[i].posicion.fil = (nivel->obstaculos[i-j].posicion.fil)-1;
                nivel->obstaculos[i].posicion.col = nivel->obstaculos[i-j].posicion.col;
            }
            es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
            if(!es_pos_valida){
                nivel->obstaculos[i].posicion.fil = nivel->obstaculos[i-j].posicion.fil;
                nivel->obstaculos[i].posicion.col = (nivel->obstaculos[i-j].posicion.col)+1;
            }
            es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
            if(!es_pos_valida){
                nivel->obstaculos[i].posicion.fil = nivel->obstaculos[i-j].posicion.fil;
                nivel->obstaculos[i].posicion.col = (nivel->obstaculos[i-j].posicion.col)-1;
            }
            j++;
        }
        nivel->tope_obstaculos++;
    }  
}

//Pre: La cantidad de guardias viene inicializada según el numero_nivel.
//Post: Asigna coordenadas aleatorias a los guardias robot (por primera vez).
void obtener_guardias(int numero_nivel, nivel_t* nivel, int cantidad_guardia){
    bool es_pos_valida = false;
    int tope_aux = nivel->tope_obstaculos;
    for(int i = tope_aux; i < (tope_aux + cantidad_guardia); i++){
        es_pos_valida = false;
        nivel->obstaculos[i].tipo = GUARDIA;
        while(!es_pos_valida){
            if(numero_nivel % 2 != 0){
                nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            else{
                nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
        }
        nivel->tope_obstaculos++;
    }
}

//Pre: El parametro hay_bomba viene inicializado según el numero_nivel.
//Post: Si el numero_nivel debe tener bomba, le asigna una coordenada aleatoria a la misma.
void obtener_bomba(int numero_nivel, nivel_t* nivel, bool hay_bomba){
    if(hay_bomba){
        bool es_pos_valida = false;
        int i = nivel->tope_obstaculos;
        nivel->obstaculos[i].tipo = BOMBA;
        while(!es_pos_valida){
            if(numero_nivel % 2 != 0){
                nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            else{
                nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            es_pos_valida = validez_obstaculos((*nivel), nivel->obstaculos[i].posicion);
        }
        nivel->tope_obstaculos++;
    }
}

//Post: Asigna coordenadas aleatorias a la llave.
void obtener_llave(int numero_nivel, nivel_t* nivel){
    bool es_pos_valida = false;
    int i = 0;
    nivel->tope_herramientas = 0;
    nivel->herramientas[i].tipo = LLAVE;
    while(!es_pos_valida){
        if(numero_nivel % 2 != 0){
            nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        else{
            nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        es_pos_valida = validez_herramientas((*nivel), nivel->herramientas[i].posicion);
    }
    nivel->tope_herramientas++;
}

//Pre: La cantidad de las monedas depende de la cantidad de baldosas pinches del numero_nivel que se pasan como parametro.
//Post: Asigna coordenadas aleatorias a las monedas.
void obtener_monedas(int numero_nivel, nivel_t* nivel, int cantidad_pinches){
    bool es_pos_valida = false;
    int tope_aux = nivel->tope_herramientas;
    int cantidad_monedas = (cantidad_pinches/2);
    for(int i = tope_aux; i < (tope_aux + cantidad_monedas); i++){
        es_pos_valida = false;
        while(!es_pos_valida){
            if(numero_nivel % 2 != 0){
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            else{
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            es_pos_valida = validez_herramientas((*nivel), nivel->herramientas[i].posicion);
        }
        nivel->herramientas[i].tipo = MONEDA;
        nivel->tope_herramientas++;
    }
}

//Pre: La cantidad de baldosas teletransportadoras depende de la cantidad de guardias del numero_nivel que se pasan como parametro.
//Post: Asigna coordenadas aleatorias a las baldosas teletransportadoras.
void obtener_tps(int numero_nivel, nivel_t* nivel, int cantidad_guardia){
    bool es_pos_valida = false;
    int tope_aux = nivel->tope_herramientas;
    int cantidad_tps = cantidad_guardia;
    for(int i = tope_aux; i < (tope_aux + cantidad_tps); i++){
        es_pos_valida = false;
        while(!es_pos_valida){
            if(numero_nivel % 2 != 0){
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            else{
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            es_pos_valida = validez_herramientas((*nivel), nivel->herramientas[i].posicion);
        }
        nivel->herramientas[i].tipo = BALDOSA_TP;
        nivel->tope_herramientas++;
    }
}

//Post: Le asigna una coordenada aleatoria a la baldosa teletransportadora si el numero_nivel lo requiere.
void obtener_interruptor(int numero_nivel, nivel_t* nivel, bool hay_bomba){
    bool hay_interruptor = hay_bomba;
    if(hay_interruptor){
        bool es_pos_valida = false;
        int i = nivel->tope_herramientas;
        nivel->herramientas[i].tipo = INTERRUPTOR;
        while(!es_pos_valida){
            if(numero_nivel % 2 != 0){
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            else{
                nivel->herramientas[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                nivel->herramientas[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            }
            es_pos_valida = validez_herramientas((*nivel), nivel->herramientas[i].posicion);
        }
        nivel->tope_herramientas++;
    }
}


//Post: Asigna coordenadas aleatorias para la entrada. 
void obtener_entrada(int numero_nivel, nivel_t* nivel){  
    bool es_pos_valida = false;
    while(!es_pos_valida){
        if(numero_nivel % 2 != 0){
            nivel->entrada.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->entrada.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        else{
            nivel->entrada.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->entrada.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        es_pos_valida = validez_entrada((*nivel), nivel->entrada);
    }
}

//Post: Asigna coordenadas aleatorias para la salida.
void obtener_salida(int numero_nivel, nivel_t* nivel){  
    bool es_pos_valida = false;
    while(!es_pos_valida){
        if(numero_nivel % 2 != 0){
            nivel->salida.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->salida.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        else{
            nivel->salida.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
            nivel->salida.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
        }
        es_pos_valida = validez_salida((*nivel), nivel->salida);
    }
}

//Pre: Llamar exlusivamente para inicializar el personaje en el NIVEL 1. (Para el resto usar la funcion actualizar_personaje en juego.c)
//Post: Le asigna los valores iniciales al personaje. 
void inicializar_personaje(personaje_t* personaje, char tipo_personaje, nivel_t niveles[MAX_NIVELES]){
    personaje->tipo = tipo_personaje;
    personaje->tiene_llave = false;
    personaje->posicion.fil = niveles[NIV_1 - 1].entrada.fil;
    personaje->posicion.col = niveles[NIV_1 - 1].entrada.col;
    personaje->movimientos = MOV_INICIALES;
    personaje->murio = false;
    personaje->presiono_interruptor = false;
}


//Pre: -Debe llamarse únicamente al estarse ejecutando el movimiento y no para inicializar la posicion de los guardias.
//     -El juego ya está cargado con todos los demás obstáculos y herramientas.
//Post: Reasigna coordenadas aleatorias a los guardias robot.
void reposicionar_guardias(int numero_nivel, nivel_t* nivel, coordenada_t pos_personaje){
    bool es_pos_valida = false;
    for(int i = 0; i < (nivel->tope_obstaculos); i++){
        es_pos_valida = false;
        if(nivel->obstaculos[i].tipo == GUARDIA){
            while(!es_pos_valida){
                if(numero_nivel % 2 != 0){
                    nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                    nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MIN - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                }
                else{
                    nivel->obstaculos[i].posicion.fil = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                    nivel->obstaculos[i].posicion.col = rand() % (DIMENSION_MAX - DELIMITADOR_BORDE) + RANGO_CORRIDO;
                }
                es_pos_valida = validez_reposicion((*nivel), nivel->obstaculos[i].posicion, pos_personaje);
            }
        }
    }
}

//Post: Elimina la bomba del vector obstaculos(sin mantener el orden).
void eliminar_bomba(elemento_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos){
    bool esta_eliminada = false;
    int i = 0;
    while(!esta_eliminada){
        if(obstaculos[i].tipo == BOMBA){
            obstaculos[i] = obstaculos[(*tope_obstaculos)-1];
            (*tope_obstaculos)--;
            esta_eliminada = true;
        }
        i++;
    }
}

//Post: Elimina la moneda que el personaje pisa del vector herramientas(sin mantener el orden).
void eliminar_moneda(elemento_t herramientas[MAX_HERRAMIENTAS], int* tope_herramientas, coordenada_t pos_personaje){
    bool esta_eliminada = false;
    int i = 0;
    while(!esta_eliminada){
        if((herramientas[i].tipo == MONEDA) && (herramientas[i].posicion.fil== pos_personaje.fil) && (herramientas[i].posicion.col == pos_personaje.col)){
            herramientas[i] = herramientas[(*tope_herramientas)-1];
            (*tope_herramientas)--;
            esta_eliminada = true;
        }
        i++;
    }
}




//     FUNCIONES DE VERIFICACIÓN PARA MOVIMIENTO/MODIFICACION DE MOVIMIENTOS ACTUALES:

//Pre: El juego debe tener todos sus campos validos.
//Post: Verifica si el personaje tiene disponibilidad de moverse en cierta dirección o si una pared le bloquea.
void verificar_paredes_adyac(bool* sigue_pared_arriba, bool* sigue_pared_izq, bool* sigue_pared_abajo, bool* sigue_pared_der, juego_t juego){
    int i = 0;
    int tope_paredes = juego.niveles[juego.nivel_actual-1].tope_paredes;
    while((i < tope_paredes) && !(*sigue_pared_arriba)){
        if(((juego.personaje.posicion.fil-1) == (juego.niveles[juego.nivel_actual-1].paredes[i].fil)) && ((juego.personaje.posicion.col) == (juego.niveles[juego.nivel_actual-1].paredes[i].col))){
            (*sigue_pared_arriba) = true;
        }
        i++;
    }
    i = 0; //Reinicio cada vez para verificar en distinta dirección.
    while((i < tope_paredes) && !(*sigue_pared_izq)){
        if(((juego.personaje.posicion.fil) == (juego.niveles[juego.nivel_actual-1].paredes[i].fil)) && ((juego.personaje.posicion.col-1) == (juego.niveles[juego.nivel_actual-1].paredes[i].col))){
            (*sigue_pared_izq)= true;
        }
        i++;
    }
    i = 0;
    while((i < tope_paredes) && !(*sigue_pared_abajo)){
        if(((juego.personaje.posicion.fil+1) == (juego.niveles[juego.nivel_actual-1].paredes[i].fil)) && ((juego.personaje.posicion.col) == (juego.niveles[juego.nivel_actual-1].paredes[i].col))){
            (*sigue_pared_abajo) = true;
        }
        i++;
    }
    i = 0;
    while((i < tope_paredes) && !(*sigue_pared_der)){
        if(((juego.personaje.posicion.fil) == (juego.niveles[juego.nivel_actual-1].paredes[i].fil)) && ((juego.personaje.posicion.col+1) == (juego.niveles[juego.nivel_actual-1].paredes[i].col))){
            (*sigue_pared_der)= true;
        }
        i++;
    }
}

//Pre: El juego debe tener todos sus campos validos.
//Post: Verifica si el personaje se encuentra posicionado en un obstáculo determinado.
void verificar_obstaculos(bool* esta_en_pinches, bool* esta_en_bomba, bool* esta_en_guardia, juego_t juego){
    int i = 0;
    bool coincidio = false;
    char tipo_coincidente_obs = '-';
    while((i < juego.niveles[juego.nivel_actual-1].tope_obstaculos) && (!coincidio)){
        if(  ((juego.personaje.posicion.fil) == (juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.fil)) && ((juego.personaje.posicion.col) == (juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.col))  ){
            coincidio = true;
            tipo_coincidente_obs = juego.niveles[juego.nivel_actual-1].obstaculos[i].tipo;
        }
        i++;
    }

    if(tipo_coincidente_obs == BALDOSA_PINCHE){
        (*esta_en_pinches) = true;
    }
    else if(tipo_coincidente_obs == BOMBA){
        (*esta_en_bomba) = true;
    }
    else if(tipo_coincidente_obs == GUARDIA){
        (*esta_en_guardia) = true;
    }
}

//Post: Modifica los movimientos restantes del jugador si su posicion se encima a la de un obstáculo.
void accionar_obstaculos(bool* esta_en_pinches, bool* esta_en_bomba, bool* esta_en_guardia, int* movimientos_restantes, elemento_t obstaculos[MAX_OBSTACULOS], int* tope_obstaculos, char tipo_personaje){
    if((*esta_en_pinches) && (tipo_personaje != PURO_HUESO) && (tipo_personaje != POLLITO) && ((*movimientos_restantes) >= 2)){
        (*movimientos_restantes) -= 2;
        (*esta_en_pinches) = false; //Para resetear el valor y que vuelva a revisar bien en la proxima entrada a verificar_obstaculos.
    }
    else if((*esta_en_pinches) && (tipo_personaje != PURO_HUESO) && (tipo_personaje != POLLITO) && ((*movimientos_restantes) == 1)){
        (*movimientos_restantes)--;
        (*esta_en_pinches) = false;
    }

    if(*esta_en_bomba){
        (*movimientos_restantes) = 0;
        eliminar_bomba(obstaculos, tope_obstaculos);
        (*esta_en_bomba) = false;
    }
    if((*esta_en_guardia) && (tipo_personaje != CORAJE) && (tipo_personaje != JOHNNY_BRAVO)){
        (*movimientos_restantes) = 0;
        (*esta_en_guardia) = false;
    }
}


//Pre: El juego debe tener todos sus campos validos.
//Post: Verifica si el personaje se encuentra posicionado en una herramienta determinada.
void verificar_herramientas(bool* esta_en_llave, bool* esta_en_moneda, bool* esta_en_tp, bool* esta_en_interruptor, juego_t juego, int tope_herramientas){
    int i = 0;
    bool coincidio = false;
    char herramienta_coincidente = '-';
    while((i < tope_herramientas) && (!coincidio)){
        if(  ((juego.personaje.posicion.fil) == (juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.fil)) && ((juego.personaje.posicion.col) == (juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.col))  ){
            coincidio = true;
            herramienta_coincidente = juego.niveles[juego.nivel_actual-1].herramientas[i].tipo;
        }
        i++;
    }

    if(herramienta_coincidente == LLAVE){
        (*esta_en_llave) = true;
    }
    else if(herramienta_coincidente == MONEDA){
        (*esta_en_moneda) = true;
    }
    else if(herramienta_coincidente == BALDOSA_TP){
        (*esta_en_tp) = true;
    }
    else if(herramienta_coincidente == INTERRUPTOR){
        (*esta_en_interruptor) = true;
    }
}

//Pre: Recibe el juego con todos los campos del personaje validos.
//Post: Modifica campos según la interacción del personaje con las herramientas.
void accionar_herramientas(bool esta_en_llave, bool* esta_en_moneda, bool esta_en_tp, bool esta_en_interruptor, juego_t* juego){
    int i = 0;
    int aux_pos_herramienta = 0;
    bool se_teletransporto = false;
    bool era_ultimo_tp = false; //(era_ultimo_tp: era ultima baldosa teletransportadora del vector herramientas).
    if(esta_en_interruptor){
        juego->personaje.presiono_interruptor = true;
    }

    if((esta_en_llave) && ((juego->nivel_actual == NIV_1) || (juego->nivel_actual == NIV_2))){
        juego->personaje.tiene_llave = true;
    }
    else if((esta_en_llave) && (juego->personaje.presiono_interruptor == true) && ((juego->nivel_actual == NIV_3) || (juego->nivel_actual == NIV_4))){
        juego->personaje.tiene_llave = true;
    }

    if(*esta_en_moneda){
        juego->personaje.movimientos++;
        eliminar_moneda(juego->niveles[juego->nivel_actual-1].herramientas, &(juego->niveles[juego->nivel_actual-1].tope_herramientas), juego->personaje.posicion);
        (*esta_en_moneda) = false; //Reinicio el valor para que no figure que esta pisandola permanentemente.
    }
    if(esta_en_tp){
        while((i < (juego->niveles[juego->nivel_actual-1].tope_herramientas)) && (!se_teletransporto)){
            if((juego->niveles[juego->nivel_actual-1].herramientas[i].tipo == BALDOSA_TP) && (juego->niveles[juego->nivel_actual-1].herramientas[i].posicion.fil == juego->personaje.posicion.fil) && (juego->niveles[juego->nivel_actual-1].herramientas[i].posicion.col == juego->personaje.posicion.col)){
                aux_pos_herramienta = i;
            }
            else if((juego->niveles[juego->nivel_actual-1].herramientas[i].tipo == BALDOSA_TP) && (i > aux_pos_herramienta)){
                juego->personaje.posicion = juego->niveles[juego->nivel_actual-1].herramientas[i].posicion;
                se_teletransporto = true;
            }

            if((i == (juego->niveles[juego->nivel_actual-1].tope_herramientas) - 1) && (!se_teletransporto)){
                era_ultimo_tp = true;
            }
            i++;
        }
        i = 0; //Reinicio el valor para iterar nuevamente en caso de acabarse el vector y no encontrar a donde teletransportarlo.
        if(era_ultimo_tp){
            while((i < (juego->niveles[juego->nivel_actual-1].tope_herramientas)) && (!se_teletransporto)){
                if(juego->niveles[juego->nivel_actual-1].herramientas[i].tipo == BALDOSA_TP){
                    juego->personaje.posicion = juego->niveles[juego->nivel_actual-1].herramientas[i].posicion;
                    se_teletransporto = true;
                }
                i++;
            }
        }
    }
}



/*==================================================== // ====================================================*/



/*
 * Inicializará el juego, cargando la informacion de los cuatro niveles
 * y los datos del personaje.
 */
void inicializar_juego(juego_t* juego, char tipo_personaje){
    int cant_pinches_niv_1 = 0;
    int cant_guardias_niv_1 = 0;
    bool hay_bomba_niv_1 = false;

    int cant_pinches_niv_2 = 0;
    int cant_guardias_niv_2 = 0;
    bool hay_bomba_niv_2 = false;

    int cant_pinches_niv_3 = 0;
    int cant_guardias_niv_3 = 0;
    bool hay_bomba_niv_3 = false;

    int cant_pinches_niv_4 = 0;
    int cant_guardias_niv_4 = 0;
    bool hay_bomba_niv_4 = false;

    juego->nivel_actual = NIV_1;

    asignar_num_items(NIV_1, &cant_pinches_niv_1, &cant_guardias_niv_1, &hay_bomba_niv_1);
    inicializar_nivel(&(juego->niveles[NIV_1 - 1]), NIV_1, cant_pinches_niv_1, cant_guardias_niv_1, hay_bomba_niv_1);

    asignar_num_items(NIV_2, &cant_pinches_niv_2, &cant_guardias_niv_2, &hay_bomba_niv_2);
    inicializar_nivel(&(juego->niveles[NIV_2 - 1]), NIV_2, cant_pinches_niv_2, cant_guardias_niv_2, hay_bomba_niv_2);

    asignar_num_items(NIV_3, &cant_pinches_niv_3, &cant_guardias_niv_3, &hay_bomba_niv_3);
    inicializar_nivel(&(juego->niveles[NIV_3 - 1]), NIV_3, cant_pinches_niv_3, cant_guardias_niv_3, hay_bomba_niv_3);
    
    asignar_num_items(NIV_4, &cant_pinches_niv_4, &cant_guardias_niv_4, &hay_bomba_niv_4);
    inicializar_nivel(&(juego->niveles[NIV_4 - 1]), NIV_4, cant_pinches_niv_4, cant_guardias_niv_4, hay_bomba_niv_4);

    inicializar_personaje(&(juego->personaje), tipo_personaje, juego->niveles);
}


/*
 * Recibe un juego con todas sus estructuras válidas.
 * El juego se dará por ganado si el personaje está en el último nivel
 * y posicionado en la salida.
 * El juego se dará por perdido, si el personaje queda sin movimientos.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * -> -1 si el estado es perdido.
 * ->  1 si el estado es ganado.
 */
int estado_juego(juego_t juego){
    int estado_juego = 0;
    int estado_niv = estado_nivel(juego.personaje, juego.niveles[juego.nivel_actual-1].salida);
    if((juego.nivel_actual == NIV_4) && (estado_niv == GANADO) && (juego.personaje.murio == false) && (juego.personaje.tipo != BELLOTA) && (juego.personaje.tipo != BLUE)){
        estado_juego = GANADO;
    }
    else if((juego.nivel_actual == NIV_4) && (estado_niv == GANADO) && (juego.personaje.murio == true) && (juego.personaje.movimientos != 0) && ((juego.personaje.tipo == BELLOTA) || (juego.personaje.tipo == BLUE))){
        estado_juego = GANADO;
    }
    else if(((juego.personaje.movimientos == 0) || (juego.personaje.murio == true)) && (estado_niv == JUGANDO) && (juego.personaje.tipo != BELLOTA) && (juego.personaje.tipo != BLUE)){
        estado_juego = PERDIDO;
    }
    else if((juego.personaje.movimientos == 0) && (juego.personaje.murio == true) && (estado_niv == JUGANDO) && ((juego.personaje.tipo == BELLOTA) || (juego.personaje.tipo == BLUE))){
        estado_juego = PERDIDO;
    }
    else if(((juego.personaje.movimientos == 0) || (juego.personaje.murio == true)) && (estado_niv == GANADO) && (juego.personaje.tipo != BELLOTA) && (juego.personaje.tipo != BLUE)){
        estado_juego = PERDIDO;
    }
    else if((juego.personaje.movimientos == 0) && (juego.personaje.murio == true) && (estado_niv == GANADO) && ((juego.personaje.tipo == BELLOTA) || (juego.personaje.tipo == BLUE))){
        estado_juego = PERDIDO;
    }
    else{
        estado_juego = JUGANDO;
    }
    return estado_juego;
}

/*
 * Recibe el personaje con todas sus estructuras válidas, y la coordenada de la salida del nivel en ejecución.
 * El nivel se dará por ganado cuando el personaje se
 * posicione en la salida habiendo obtenido previamente la llave.
 * Devolverá:
 * ->  0 si el estado es jugando.
 * ->  1 si el estado es ganado.
 */
int estado_nivel(personaje_t personaje, coordenada_t salida){
    int estado_niv = 0;
    if((personaje.tiene_llave) && (personaje.posicion.fil == salida.fil) && (personaje.posicion.col == salida.col)){
        estado_niv = GANADO;
    }
    else{
        estado_niv = JUGANDO;
    }
    return estado_niv;
}


/*
 * Inicializara un nivel cargando su entrada,
 * salida, obtáculos, herramientas y paredes.
 */
void inicializar_nivel(nivel_t* nivel, int numero_nivel, int cantidad_baldosas_pinches, int cantidad_guardia, bool hay_bomba){
    obtener_paredes(numero_nivel, nivel->paredes, &(nivel->tope_paredes));
    obtener_pinches(numero_nivel, nivel, cantidad_baldosas_pinches);
    obtener_guardias(numero_nivel, nivel, cantidad_guardia);
    obtener_bomba(numero_nivel, nivel, hay_bomba);
    obtener_llave(numero_nivel, nivel);
    obtener_monedas(numero_nivel, nivel, cantidad_baldosas_pinches);
    obtener_tps(numero_nivel, nivel, cantidad_guardia);        //tps == baldosas teletransportadoras
    obtener_interruptor(numero_nivel, nivel, hay_bomba);
    obtener_entrada(numero_nivel, nivel);
    obtener_salida(numero_nivel, nivel);
}


/*
 * Mueve el personaje en la dirección indicada por el usuario
 * y actualiza el juego según los elementos que haya en el camino
 * del personaje.
 * El juego quedará en un estado válido al terminar el movimiento.
 * El movimiento será:
 * -> w: Si el personaje debe moverse para la arriba.
 * -> a: Si el personaje debe moverse para la derecha.
 * -> s: Si el personaje debe moverse para la abajo.
 * -> d: Si el personaje debe moverse para la izquierda.
 * En caso de que en la dirección que se quiere mover haya una pared
 * se contará como un movimiento, los guardias se moverán y
 * el personaje quedará en la misma baldosa.
 */
void mover_personaje(juego_t* juego, char movimiento){
    bool sigue_pared_arriba = false;
    bool sigue_pared_izq = false;
    bool sigue_pared_abajo = false;
    bool sigue_pared_der = false;
    
    bool esta_en_pinches = false;
    bool esta_en_bomba = false;
    bool esta_en_guardia = false;

    bool esta_en_llave = false;
    bool esta_en_moneda = false;
    bool esta_en_tp = false;   //(está en teletransportador)
    bool esta_en_interruptor = false;

    bool debe_parar = false; //Para caso especifico en el que se usa el último movimiento pero frena por llegar a la salida con la llave.
    int estado_niv = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual-1].salida);

    verificar_paredes_adyac(&sigue_pared_arriba, &sigue_pared_izq, &sigue_pared_abajo, &sigue_pared_der, (*juego));

    if(juego->personaje.movimientos > 0){

        if(movimiento == ARRIBA){

            juego->personaje.movimientos--;

            while((!sigue_pared_arriba) && (!esta_en_tp) && (estado_niv == JUGANDO) && (!debe_parar)){
                juego->personaje.posicion.fil--;
                verificar_paredes_adyac(&sigue_pared_arriba, &sigue_pared_izq, &sigue_pared_abajo, &sigue_pared_der, (*juego));
                verificar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, (*juego));
                verificar_herramientas(&esta_en_llave, &esta_en_moneda, &esta_en_tp, &esta_en_interruptor, (*juego), juego->niveles[juego->nivel_actual-1].tope_herramientas);
                
                estado_niv = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual-1].salida);

                accionar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, &(juego->personaje.movimientos), juego->niveles[juego->nivel_actual-1].obstaculos, &(juego->niveles[juego->nivel_actual-1].tope_obstaculos), juego->personaje.tipo);
                accionar_herramientas(esta_en_llave, &esta_en_moneda, esta_en_tp, esta_en_interruptor, juego);

                if((juego->personaje.movimientos == 0) && ((juego->personaje.tipo == BELLOTA) || (juego->personaje.tipo == BLUE)) && (juego->personaje.murio == false)){
                    juego->personaje.movimientos = MOV_INICIALES;
                    juego->personaje.murio = true;
                }
                else if((juego->personaje.movimientos == 0) && (juego->personaje.tipo != BELLOTA) && (juego->personaje.tipo != BLUE)){
                    juego->personaje.murio = true;
                }
                
                if((juego->personaje.movimientos == 0) && (sigue_pared_arriba) && (estado_niv != JUGANDO)){
                    debe_parar = true;
                }

                mostrar_juego(*juego);
            }
            
            reposicionar_guardias(juego->nivel_actual, &(juego->niveles[juego->nivel_actual-1]), juego->personaje.posicion);
        
        }
        else if(movimiento == IZQ){

            juego->personaje.movimientos--;
            while((!sigue_pared_izq) && (!esta_en_tp) && (estado_niv == JUGANDO) && (!debe_parar)){
                juego->personaje.posicion.col--;
                verificar_paredes_adyac(&sigue_pared_arriba, &sigue_pared_izq, &sigue_pared_abajo, &sigue_pared_der, (*juego));
                verificar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, (*juego));
                verificar_herramientas(&esta_en_llave, &esta_en_moneda, &esta_en_tp, &esta_en_interruptor, (*juego), juego->niveles[juego->nivel_actual-1].tope_herramientas);
                
                estado_niv = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual-1].salida);

                accionar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, &(juego->personaje.movimientos), juego->niveles[juego->nivel_actual-1].obstaculos, &(juego->niveles[juego->nivel_actual-1].tope_obstaculos), juego->personaje.tipo);
                accionar_herramientas(esta_en_llave, &esta_en_moneda, esta_en_tp, esta_en_interruptor, juego);

                if((juego->personaje.movimientos == 0) && ((juego->personaje.tipo == BELLOTA) || (juego->personaje.tipo == BLUE)) && (juego->personaje.murio == false)){
                    juego->personaje.movimientos = MOV_INICIALES;
                    juego->personaje.murio = true;
                }
                else if((juego->personaje.movimientos == 0) && (juego->personaje.tipo != BELLOTA) && (juego->personaje.tipo != BLUE)){
                    juego->personaje.murio = true;
                }

                if((juego->personaje.movimientos == 0) && (sigue_pared_izq) && (estado_niv != JUGANDO)){
                    debe_parar = true;
                }

                mostrar_juego(*juego);
            } 
            reposicionar_guardias(juego->nivel_actual, &(juego->niveles[juego->nivel_actual-1]), juego->personaje.posicion);
                
        }
        else if(movimiento == ABAJO){

            juego->personaje.movimientos--;
            while((!sigue_pared_abajo) && (!esta_en_tp) && (estado_niv == JUGANDO) && (!debe_parar)){
                juego->personaje.posicion.fil++;
                verificar_paredes_adyac(&sigue_pared_arriba, &sigue_pared_izq, &sigue_pared_abajo, &sigue_pared_der, (*juego));
                verificar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, (*juego));
                verificar_herramientas(&esta_en_llave, &esta_en_moneda, &esta_en_tp, &esta_en_interruptor, (*juego), juego->niveles[juego->nivel_actual-1].tope_herramientas);
                
                estado_niv = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual-1].salida);

                accionar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, &(juego->personaje.movimientos), juego->niveles[juego->nivel_actual-1].obstaculos, &(juego->niveles[juego->nivel_actual-1].tope_obstaculos), juego->personaje.tipo);
                accionar_herramientas(esta_en_llave, &esta_en_moneda, esta_en_tp, esta_en_interruptor, juego);

                if((juego->personaje.movimientos == 0) && ((juego->personaje.tipo == BELLOTA) || (juego->personaje.tipo == BLUE)) && (juego->personaje.murio == false)){
                    juego->personaje.movimientos = MOV_INICIALES;
                    juego->personaje.murio = true;
                }
                else if((juego->personaje.movimientos == 0) && (juego->personaje.tipo != BELLOTA) && (juego->personaje.tipo != BLUE)){
                    juego->personaje.murio = true;
                }

                if((juego->personaje.movimientos == 0) && (sigue_pared_abajo) && (estado_niv != JUGANDO)){
                    debe_parar = true;
                }

                mostrar_juego(*juego);
            }
            reposicionar_guardias(juego->nivel_actual, &(juego->niveles[juego->nivel_actual-1]), juego->personaje.posicion);
               
        }
        else if(movimiento == DER){

            juego->personaje.movimientos--;
            while((!sigue_pared_der) && (!esta_en_tp) && (estado_niv == JUGANDO) && (!debe_parar)){
                juego->personaje.posicion.col++;
                verificar_paredes_adyac(&sigue_pared_arriba, &sigue_pared_izq, &sigue_pared_abajo, &sigue_pared_der, (*juego));
                verificar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, (*juego));
                verificar_herramientas(&esta_en_llave, &esta_en_moneda, &esta_en_tp, &esta_en_interruptor, (*juego), juego->niveles[juego->nivel_actual-1].tope_herramientas);
                
                estado_niv = estado_nivel(juego->personaje, juego->niveles[juego->nivel_actual-1].salida);

                accionar_obstaculos(&esta_en_pinches, &esta_en_bomba, &esta_en_guardia, &(juego->personaje.movimientos), juego->niveles[juego->nivel_actual-1].obstaculos, &(juego->niveles[juego->nivel_actual-1].tope_obstaculos), juego->personaje.tipo);
                accionar_herramientas(esta_en_llave, &esta_en_moneda, esta_en_tp, esta_en_interruptor, juego);

                if((juego->personaje.movimientos == 0) && ((juego->personaje.tipo == BELLOTA) || (juego->personaje.tipo == BLUE)) && (juego->personaje.murio == false)){
                    juego->personaje.movimientos = MOV_INICIALES;
                    juego->personaje.murio = true;
                }
                else if((juego->personaje.movimientos == 0) && (juego->personaje.tipo != BELLOTA) && (juego->personaje.tipo != BLUE)){
                    juego->personaje.murio = true;
                }

                if((juego->personaje.movimientos == 0) && (sigue_pared_der)){
                    debe_parar = true;
                }

                mostrar_juego(*juego);
            }
            reposicionar_guardias(juego->nivel_actual, &(juego->niveles[juego->nivel_actual-1]), juego->personaje.posicion);       
        
        }
    }

}


/*
 * Mostrará el juego por pantalla.
 */
void mostrar_juego(juego_t juego){
    char mapa[DIMENSION_MAX][DIMENSION_MAX];
    int dimension_lab = DIMENSION_MAX;
    if(juego.nivel_actual % 2 != 0){
        dimension_lab = DIMENSION_MIN;
    }
    
    limpiar_lab(mapa, dimension_lab);
    insertar_paredes(mapa, juego.niveles[juego.nivel_actual-1].paredes, juego.niveles[juego.nivel_actual-1].tope_paredes);
    insertar_obstaculos(mapa, juego.niveles[juego.nivel_actual-1].obstaculos, juego.niveles[juego.nivel_actual-1].tope_obstaculos);
    insertar_herramientas(mapa, juego.niveles[juego.nivel_actual-1].herramientas, juego.niveles[juego.nivel_actual-1].tope_herramientas, juego.personaje.presiono_interruptor, juego.nivel_actual);
    insertar_entrada(mapa, juego.niveles[juego.nivel_actual-1].entrada);
    insertar_personaje(mapa, juego.personaje.posicion, juego.personaje.tipo);
    insertar_salida(mapa, juego.niveles[juego.nivel_actual-1].salida, juego.personaje.tiene_llave);

    system("clear");
    mostrar_datos_nivel(juego.nivel_actual, juego.personaje);
    mostrar_laboratorio(mapa, dimension_lab, juego.nivel_actual);
}