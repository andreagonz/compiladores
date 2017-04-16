#ifndef NODO_H
#define NODO_H

#include"token.h"
#include<string>

class Visitor;

class Nodo {
protected:
    Nodo *izq;
    Nodo *der;
    Token *token;
public:
Nodo(Token * t): token(t), der(0), izq(0) {}
    Nodo * get_izq(void);
    Nodo * get_der(void);
    Token * get_token(void);
    Tipo get_tipo(void);
    void set_izq(Nodo * n);
    void set_der(Nodo * n);
    void set_token(Token * t);
    std::string str(void);
    virtual void accept(Visitor * v) = 0;
};

class NodoSum: public Nodo {
public:
NodoSum(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoMenos: public Nodo {
public:
NodoMenos(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoNeg: public Nodo {
public:
NodoNeg(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoDiv: public Nodo {
public:
NodoDiv(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoMult: public Nodo {
public:
NodoMult(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoNum: public Nodo {
public:
NodoNum(Token * t): Nodo(t) {}
    void accept(Visitor * v);
    float get_valor(void);
};

class NodoVar: public Nodo {
public:
NodoVar(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoAsig: public Nodo {
public:
NodoAsig(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

class NodoSeq: public Nodo {
public:
NodoSeq(Token * t): Nodo(t) {}
    void accept(Visitor * v);
};

std::string str(Nodo * n);

std::string aCadena(Nodo * vertice, int nivel, bool rama[]);

std::string espacios(int n, bool rama[]);

int profundidad(Nodo * v);

#endif
