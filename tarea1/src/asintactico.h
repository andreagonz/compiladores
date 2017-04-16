#include<queue>
#include<string>
#include"token.h"
#include"nodo.h"

void clear(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Tipo front_tipo(std::queue<Token*> * q);

Nodo * error(std::string s, std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * error(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * S(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * Prog(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * Inst(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * Asig(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * AsigP(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * Exp(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * ExpP(std::queue<Token*> * q, std::queue<Nodo*> * nodos, Nodo ** tope);

Nodo * Term(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

Nodo * TermP(std::queue<Token*> * q, std::queue<Nodo*> * nodos, Nodo ** tope);

Nodo * Fact(std::queue<Token*> * q, std::queue<Nodo*> * nodos);

void pop_del(std::queue<Token*> * q);
