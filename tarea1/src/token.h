#ifndef TOKEN_H
#define TOKEN_H

#include<string>

typedef enum Tipo {
    NUM,
    VAR,
    PVAR,
    MAS,
    DIV,
    MULT,
    MENOS,
    ASIG,
    IZQ,
    DER,
    SEQ
} Tipo;

class Token {
protected:
    Tipo tipo;
    std::string valor;
    int linea;
    int col;
public:
Token(Tipo t, std::string v, int l, int c) : tipo(t), valor(v), linea(l), col(c) {}
    Tipo get_tipo(void);
    int get_linea(void);
    int get_col(void);
    std::string get_valor(void);
    std::string str(void);
};

#endif
