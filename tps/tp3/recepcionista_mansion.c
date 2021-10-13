#include "encargado_de_imaginarios.h"

#define LISTAR "listar_amigos"
#define ELEGIR "elegir_amigo"
#define DEVOLVER "devolver_amigo"

const int ARGUM_1 = 1;
const int ARGUM_2 = 2;
const int CANTIDAD_MIN_ARGS = 2;
const int CANTIDAD_MAX_ARGS = 3;

int main(int argc, char *argv[]){
    
    if(argc == CANTIDAD_MIN_ARGS){
        if(strcmp(argv[ARGUM_1], LISTAR) == 0){
            listar_amigos();
        }
    } 
    else if(argc == CANTIDAD_MAX_ARGS){
        if(strcmp(argv[ARGUM_1], ELEGIR) == 0){
            elegir_amigo(argv[ARGUM_2]);
        }
        else if(strcmp(argv[ARGUM_1], DEVOLVER) == 0){
            devolver_amigo(argv[ARGUM_2]);
        }
    }
    
    return 0;
}