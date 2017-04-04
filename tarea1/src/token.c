#include<stdio.h>

enum Tipo {
    NUM,
    VAR,
    MAS,
    DIV,
    MULT,
    MENOS,
    ASIG,
    IZQ,
    DER
};

/*
  0 - número
  1 - variable
  2 - operador
  3 - asignación
  4 - paréntesis
 */
int token_tipo(enum token t) {
    if(t == NUM)
        return 0;
    if(t == VAR)
        return 1;
    if(t == ASIG)
        return 3;
    if(t == IZQ || t == DER)
        return 4;
    return 2;
}

int main() {
    enum token t = VAR;
    printf("%d", token_tipo(t));
    return 0;
}
