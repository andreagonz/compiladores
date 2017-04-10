#ifndef TOKEN_H
#define TOKEN_H

typedef enum Tipo {
    NUM,
    VAR,
    MAS,
    DIV,
    MULT,
    MENOS,
    ASIG,
    IZQ,
    DER
} Tipo;

class Token {
protected:
    Tipo tipo;
public:
    Token(Tipo t) : tipo(t) {}
    Tipo get_tipo(void);
};

class Num: Token {
    int num;
public:
    Num(Tipo t) : Token(t) {}
};

class Var: Token {
    char c;
public:
    Var(Tipo t) : Token(t) {}
};

class Op: Token {
public:
    Op(Tipo t) : Token(t) {}
};

class Asig: Token {
public:
    Asig(Tipo t) : Token(t) {}
};

class Par: Token {
public:
    Par(Tipo t) : Token(t) {}
};

#endif
