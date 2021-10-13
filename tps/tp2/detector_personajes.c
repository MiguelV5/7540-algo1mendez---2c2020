#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char BLUE = 'B';
const char PURO_HUESO = 'H'; 
const char CORAJE = 'C';
const char POLLITO = 'P';
const char JOHNNY_BRAVO = 'J';
const char BELLOTA = 'S';

const char SALADO = 'S';
const char DULCE = 'D';
const char AMARGO = 'A';

const char AZUL = 'A';
const char AMARILLO = 'Y';
const char VERDE = 'V';
const char NEGRO = 'N';
const char BLANCO = 'B';
const char ROSA = 'R';

const int PREDET_ALTURA_BLUE = 140;
const int PREDET_ALTURA_HUESO = 200;
const int PREDET_ALTURA_CORAJE = 30;
const int PREDET_ALTURA_POLLITO = 50;
const int PREDET_ALTURA_JHONNY = 180;
const int PREDET_ALTURA_BELLOTA = 120;

const int FECHA_MIN = 1988;
const int FECHA_MAX = 2008;

const int PUNTOS_SALADO = 5;
const int PUNTOS_DULCE = 15;
const int PUNTOS_AMARGO = 20;

const int TALLA_MIN = 33;
const int TALLA_MAX = 47;
const int SIN_ZAPATOS = 0;

const int ZAPATO_MUY_CHICO = 33;
const int ZAPATO_CHICO = 37;
const int ZAPATO_MEDIANO = 42;
const int ZAPATO_GRANDE = 47;

const int MULTIPLICADOR_1 = 1;
const int MULTIPLICADOR_2 = 2;
const int MULTIPLICADOR_3 = 3;
const int MULTIPLICADOR_4 = 4;

const int PUNTOS_ROSA_AMARILLO = 5;
const int PUNTOS_NEGRO_BLANCO = 15;
const int PUNTOS_AZUL_VERDE = 20;

const int ALTURA_MIN = 10;
const int ALTURA_MAX = 250;

const int RANGO_MIN = 1;
const int RANGO_MIN_TOPE = 80;
const int RANGO_MEDIO = 160;
const int RANGO_MAX = 240;

// Post: Debe mostrar al usuario valores posibles de año.
void mostrar_convencion_nacimiento(){
    printf("(Ingresa número entre 1988 y 2008, ambos inclusive.)\n"); 
}

// Pre: Debe recibir un año cualquiera.
// Post: Devuelve true si es valido ; false si es invalido.
bool validez_fecha(int fecha){ 
    return ((fecha >= FECHA_MIN) && (fecha <= FECHA_MAX));
}

//Post: Le debe preguntar al usuario las veces que haga falta para asignar correctamente el año.
void preguntar_anio(int* anio){
    printf("Escribe el año de nacimiento.\n");
    mostrar_convencion_nacimiento();
    scanf("%i", anio);

    while(!(validez_fecha(*anio))){
        printf("\nOjo piojo, ese que me diste no es un año válido.\n");
        mostrar_convencion_nacimiento();
        scanf("%i", anio);
    }
}

// Pre: Debe recibir una fecha previamente validada.
// Post: Asigna puntos calculados correspondientes al año dado.
void asignar_puntos_fecha(int fecha_valida, int *puntos_fecha){
    (*puntos_fecha) = ((fecha_valida % 20) + 1);
}

// Post: Debe mostrar al usuario caracteres posibles de sabor a ingresar.
void mostrar_convencion_sabor(){
    printf("(Inserta una letra:\n S para Salado.\n D para Dulce.\n A  para Amargo.)\n");    
}

// Pre: Debe recibir un sabor cualquiera.
// Post: Devuelve true si el sabor es valido, false si es invalido.
bool validez_sabor(char sabor){
    return ((sabor == SALADO) || (sabor == DULCE) || (sabor == AMARGO));
}

//Post: Le debe preguntar al usuario las veces que haga falta para asignar correctamente el sabor.
void preguntar_sabor(char* sabor){
    printf("\nPerfecto, ahora dime, ¿Cuál es tu sabor preferido?\n");
    mostrar_convencion_sabor();
    scanf(" %c", sabor);

    while(!(validez_sabor(*sabor))){
        printf("\nNo tengo un paladar artificial tan sofisticado. Dale, escribe un sabor que yo conozca.\n");
        mostrar_convencion_sabor();
        scanf(" %c", sabor);
    }
}

// Pre: Debe recibir un sabor previamente validado.
// Post: Asigna los puntos correspondientes al sabor dado.
void asignar_puntos_sabor(char sabor_valido, int *puntos_sabor){

    if(sabor_valido == SALADO){
        (*puntos_sabor) = PUNTOS_SALADO;
    }
    else if(sabor_valido == DULCE){
        (*puntos_sabor) = PUNTOS_DULCE;
    }
    else if(sabor_valido == AMARGO){
        (*puntos_sabor) = PUNTOS_AMARGO;
    }          
}

// Post: Debe mostrar al usuario los posibles valores de talla que puede ingresar.
void mostrar_convencion_talla(){
    printf("(Ingresa un número entre 33 y 47 (ambos inclusive), y si no usa zapatos ingrese 0.)\n");
}

// Pre: Debe recibir una talla cualquiera.
// Post: Devuelve true si la talla es valida ; false si es invalida.
bool validez_talla(int talla){
    return (((talla >= TALLA_MIN) && (talla <= TALLA_MAX)) || (talla == SIN_ZAPATOS));
}

//Post: Le debe preguntar al usuario las veces que haga falta para asignar correctamente la talla.
void preguntar_talla(int* talla){
    printf("\nEspléndido, lo siguiente es que me brindes tu talla de zapatos.\n");
    mostrar_convencion_talla();
    scanf("%i", talla);

    while(!(validez_talla(*talla))){
        printf("\nQue olor a pies...\nDigoo, esa talla no figura en mi base de datos. Dame una correcta.\n");
        mostrar_convencion_talla();
        scanf("%i", talla);
    }
}

// Pre: Debe recibir una talla previamente validada.
// Post: Asigna el número multiplicador correspondiente a la talla dada.
void asignar_multiplicador_talla(int talla_valida, int *multiplicador){
    if(talla_valida == SIN_ZAPATOS){
        (*multiplicador) = MULTIPLICADOR_1;
    }
    else if((talla_valida >= ZAPATO_MUY_CHICO) && (talla_valida <= ZAPATO_CHICO)){
        (*multiplicador) = MULTIPLICADOR_2;
    }
    else if((talla_valida > ZAPATO_CHICO) && (talla_valida <= ZAPATO_MEDIANO)){
        (*multiplicador) = MULTIPLICADOR_3;
    }
    else if((talla_valida > ZAPATO_MEDIANO) && (talla_valida <= ZAPATO_GRANDE)){
        (*multiplicador) = MULTIPLICADOR_4;
    }
}

// Post: Debe mostrar al usuario los posibles caracteres de color a ingresar.
void mostrar_convencion_color(){
    printf("(Ingresa una letra:\n A para Azul.\n Y para Amarillo.\n V para Verde.\n N para Negro.\n B para Blanco.\n R para Rosa.)\n");
}

// Pre: Debe recibir un color cualquiera.
// Post: Devuelve true si el color es valido ; false si es invalido.
bool validez_color(char color){
    return ((color == AZUL) || (color == AMARILLO) || (color == VERDE) || (color == NEGRO) || (color == BLANCO) || (color == ROSA));
}

//Post: Le debe preguntar al usuario las veces que haga falta para asignar correctamente el color.
void preguntar_color(char* color){
    printf("\nQue sujeto tan colaborador, ¿Cuál es su color favorito?\n");
    mostrar_convencion_color();
    scanf(" %c", color);

    while(!(validez_color(*color))){
        printf("\nLo siento, mis receptores no captan ese color.\nDime un color que yo identifique.\n");
        mostrar_convencion_color();
        scanf(" %c", color);
    }
}

// Pre: Debe recibir un color previamente validado.
// Post: Asigna los puntos correspondientes al color dado.
void asignar_puntos_color(char color_valido, int *puntos_color){
    if((color_valido == ROSA) || (color_valido == AMARILLO)){
        (*puntos_color) = PUNTOS_ROSA_AMARILLO;
    }
    else if((color_valido == NEGRO) || (color_valido == BLANCO)){
        (*puntos_color) = PUNTOS_NEGRO_BLANCO;
    }
    else if((color_valido == AZUL) || (color_valido == VERDE)){
        (*puntos_color = PUNTOS_AZUL_VERDE);
    }
}              

// Post: Debe mostrar al usuario los valores posibles de altura que puede ingresar.
void mostrar_convencion_altura(){
    printf("(Ingrese su altura en centímetros, entre 10 y 250 (ambos inclusive).)\n");
}

// Pre: Debe recibir una altura cualquiera.
// Post: Devuelve 1 si es altura valida ; 0 si es invalida.
bool validez_altura(int altura){
    return ((altura >= ALTURA_MIN) && (altura <= ALTURA_MAX));
}

//Post: Le debe preguntar al usuario las veces que haga falta para asignar correctamente la altura.
void preguntar_altura(int* altura){
    printf("\nExcelente.\nUna última cuestión, digame cuál es su altura.\n");
    mostrar_convencion_altura(); 
    scanf("%i", altura);

    while(!(validez_altura(*altura))){ 
        printf("\nPara su desgracia, cuento con detector de mentiras.\nAdelante, brindeme su altura real.\n");
        mostrar_convencion_altura();
        scanf("%i", altura);
    }
}

// Pre: Debe recibir todos los datos previamente validados excepto la altura.
// Post: Asigna un puntaje final calculado.
void calcular_puntaje(int puntos_anio, int puntos_sabor, int puntos_color, int multiplicador_talla, int *puntaje_final){
    (*puntaje_final) = (puntos_anio + puntos_sabor + puntos_color)*multiplicador_talla;
}

//Pre: Debe recibir el puntaje final calculado.
//Post: Asigna una dupla de caracteres(iniciales de personajes) según un rango de puntajes. 
void corresponder_dupla(int puntaje_final, char *personaje_1, char *personaje_2){
    if((puntaje_final >= RANGO_MIN) && (puntaje_final <= RANGO_MIN_TOPE)){
        (*personaje_1) = JOHNNY_BRAVO;
        (*personaje_2) = CORAJE;
    }
    else if((puntaje_final > RANGO_MIN_TOPE) && (puntaje_final <= RANGO_MEDIO)){
        (*personaje_1) = PURO_HUESO;
        (*personaje_2) = POLLITO;
    }
    else if((puntaje_final > RANGO_MEDIO) && (puntaje_final <= RANGO_MAX)){
        (*personaje_1) = BLUE;
        (*personaje_2) = BELLOTA;
    }
}

//Pre: Debe recibir la dupla de personajes.
//Post: Asigna la altura predeterminada de dichos personajes.
void corresponder_altura_predet(char personaje_1, char personaje_2, int *altura_predet_personaje_1, int *altura_predet_personaje_2){
    if((personaje_1 == JOHNNY_BRAVO) && (personaje_2 == CORAJE)){
        (*altura_predet_personaje_1) = PREDET_ALTURA_JHONNY;
        (*altura_predet_personaje_2) = PREDET_ALTURA_CORAJE;
    }
    else if((personaje_1 == PURO_HUESO) && (personaje_2 == POLLITO)){
        (*altura_predet_personaje_1) = PREDET_ALTURA_HUESO;
        (*altura_predet_personaje_2) = PREDET_ALTURA_POLLITO;
    }
    else if((personaje_1 == BLUE) && (personaje_2 == BELLOTA)){
        (*altura_predet_personaje_1) = PREDET_ALTURA_BLUE;
        (*altura_predet_personaje_2) = PREDET_ALTURA_BELLOTA;
    }
}

//Pre: Debe recibir altura validada y alturas predeterminadas previamente asignadas por otra función.
//Post: Asigna la diferencia calculada.
void asignar_diferencia_personajes(int altura, int altura_predet_personaje_1, int altura_predet_personaje_2, int *diferencia_personaje_1, int *diferencia_personaje_2){
    (*diferencia_personaje_1) = abs(altura_predet_personaje_1 - altura);
    (*diferencia_personaje_2) = abs(altura_predet_personaje_2 - altura);
}

//Pre: Debe recibir la diferencia de alturas ya calculada.
//Post: Asigna el caracter del personaje detectado.
void determinar_personaje(char *personaje_determinado, char personaje_1, char personaje_2,int diferencia_personaje_1, int diferencia_personaje_2){
    if(diferencia_personaje_1 <= diferencia_personaje_2){
        (*personaje_determinado) = personaje_1;
    }
    else if(diferencia_personaje_2 <= diferencia_personaje_1){
        (*personaje_determinado) = personaje_2;
    }
}

//Pre: Recibe el caracter del personaje detectado.
//Post: Imprime por pantalla el nombre del personaje.
void mostrar_resultados(char personaje_determinado){
    if(personaje_determinado == BLUE){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Blue -.\n\n");
    }
    else if(personaje_determinado == PURO_HUESO){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Puro Hueso -.\n\n");
    }
    else if(personaje_determinado == CORAJE){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Coraje -.\n\n");
    }
    else if(personaje_determinado == POLLITO){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Pollito -.\n\n");
    }
    else if(personaje_determinado == JOHNNY_BRAVO){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Johnny Bravo -.\n\n");
    }
    else if(personaje_determinado == BELLOTA){
        printf("\nEscaneo completo.\nEl gran Detectotrón 2020 v9.0 concluyó la identificación del sujeto como:  - Bellota -.\n\n");
    }
}

void detectar_personaje(char* personaje_detectado){
    char sabor;
    char color;
    char personaje_1, personaje_2, personaje_determinado;

    int anio;
    int talla;
    int altura;
    int puntos_fecha, puntos_sabor, puntos_color;
    int multiplicador;
    int puntaje_final;
    int altura_predet_personaje_1, altura_predet_personaje_2;
    int diferencia_personaje_1, diferencia_personaje_2;

    personaje_1 = 'a';
    personaje_2 = 'b';
    personaje_determinado = 'c';

    puntos_fecha = 0;
    puntos_sabor = 0;
    puntos_color = 0;
    multiplicador = 1;
    puntaje_final = 0;

    altura_predet_personaje_1 = 0;
    altura_predet_personaje_2 = 0;
    diferencia_personaje_1 = 0;
    diferencia_personaje_2 = 0;

    printf("\n\nVaya vaya, a quién tenemos por aqui. Permitame hacerle ciertas preguntas\n\n");

    preguntar_anio(&anio);
    
    asignar_puntos_fecha(anio, &puntos_fecha);
    
    preguntar_sabor(&sabor);

    asignar_puntos_sabor(sabor, &puntos_sabor);

    preguntar_talla(&talla);

    asignar_multiplicador_talla(talla, &multiplicador);

    preguntar_color(&color);

    asignar_puntos_color(color, &puntos_color);

    preguntar_altura(&altura);

    calcular_puntaje(puntos_fecha, puntos_sabor, puntos_color, multiplicador, &puntaje_final);

    corresponder_dupla(puntaje_final, &personaje_1, &personaje_2);

    corresponder_altura_predet(personaje_1, personaje_2, &altura_predet_personaje_1, &altura_predet_personaje_2);

    asignar_diferencia_personajes(altura, altura_predet_personaje_1, altura_predet_personaje_2, &diferencia_personaje_1, &diferencia_personaje_2);

    determinar_personaje(&personaje_determinado, personaje_1, personaje_2, diferencia_personaje_1, diferencia_personaje_2);

    (*personaje_detectado) = personaje_determinado;
    system("clear"); //modificación del TP2
    mostrar_resultados(personaje_determinado);

}
