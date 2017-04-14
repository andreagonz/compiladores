#ifndef NODO_H
#define NODO_H

#include"token.h"
#include<string>

class Nodo {
protected:
    Nodo *izq;
    Nodo *der;
    Token *token;
    bool bder;
    bool bizq;
public:
Nodo(Token * t): token(t), der(0), izq(0), bder(false), bizq(false) {}
    Nodo * get_izq(void);
    Nodo * get_der(void);
    Token * get_token(void);
    bool tiene_izq(void);
    bool tiene_der(void);
    Tipo get_tipo(void);
    void set_izq(Nodo * n);
    void set_der(Nodo * n);
    void set_token(Token * t);
    std::string str(void);
};

class NodoOp: public Nodo {
public:
NodoOp(Token * t): Nodo(t) {}
};

class NodoSum: public NodoOp {
public:
NodoSum(Token * t): NodoOp(t) {}
};

class NodoMenos: public NodoOp {
public:
NodoMenos(Token * t): NodoOp(t) {}
};

class NodoNeg: public NodoOp {
public:
NodoNeg(Token * t): NodoOp(t) {}
};

class NodoDiv: public NodoOp {
public:
NodoDiv(Token * t): NodoOp(t) {}
};

class NodoMult: public NodoOp {
public:
NodoMult(Token * t): NodoOp(t) {}
};

class NodoNum: public NodoOp {
public:
NodoNum(Token * t): NodoOp(t) {}
};

class NodoVar: public NodoOp {
public:
NodoVar(Token * t): NodoOp(t) {}
};

class NodoAsig: public Nodo {
public:
NodoAsig(Token * t): Nodo(t) {}
};

class NodoSeq: public Nodo {
public:
NodoSeq(Token * t): Nodo(t) {}
};

std::string str(Nodo * n);

std::string aCadena(Nodo * vertice, int nivel, bool rama[]);

std::string espacios(int n, bool rama[]);

int profundidad(Nodo * v);
#endif
