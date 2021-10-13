#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_STRING 20

int main(){
    int resultado;
    char string[MAX_STRING];
    strcpy(string, "<150ajdskasj");
    resultado = atoi(string);
    printf("\n\tSale numerito: %i\n", resultado);
    return 0;
}