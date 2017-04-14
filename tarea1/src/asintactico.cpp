#include "asintactico.h"
#include "token.h"
#include "nodo.h"
#include<queue>
#include<string>
#include<iostream>
#include <stdlib.h>

using namespace std;

void clear(queue<Token*> * q, queue<Nodo*> * nodos) {
    while(q->empty()) {
        pop_del(q);
    }
    delete q;
    while(nodos->empty()) {
        Nodo *n = nodos->front();
        Token *t = n->get_token();
        nodos->pop();
        delete n;
        delete t;
    }
    delete nodos;
}

Nodo * error(queue<Token*> * q, queue<Nodo*> * nodos) {
    cout << "Error de sintáxis en línea " << q->front()->get_linea() << ", columna "
         << q->front()->get_col() << ": " <<  "[" << q->front()->get_valor() << "]" << endl;
    clear(q, nodos);
    exit(1);
    return NULL;
}

Nodo * error(string s, queue<Token*> * q, queue<Nodo*> * nodos) {
    cout << "Error de sintáxis en línea " << q->front()->get_linea() << ", columna "
         << q->front()->get_col() << ": " <<  "[" << q->front()->get_valor() << "]" << endl;
    cout << s << endl;
    clear(q, nodos);
    exit(1);
    return NULL;
}

Nodo * S(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == PVAR
       || q->front()->get_tipo() == NUM
       || q->front()->get_tipo() == VAR
       || q->front()->get_tipo() == IZQ
       || q->front()->get_tipo() == MENOS) {
        Nodo * n = Inst(q, nodos);
        Nodo * m = Prog(q, nodos);
        if(m) {
            n->set_der(m);
        }
        return n;
    }
    return error("Asignación o expresión experados.", q, nodos);
}

Nodo * Prog(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->empty())
        return NULL;
    else if(q->front()->get_tipo() == PVAR
            || q->front()->get_tipo() == NUM
            || q->front()->get_tipo() == VAR
            || q->front()->get_tipo() == IZQ
            || q->front()->get_tipo() == MENOS) {
        Nodo * n = Inst(q, nodos);
        Nodo * prog = Prog(q, nodos);
        if(prog)
            n->set_der(prog);        
        return n;
    }
    return error(q, nodos);
}

Nodo * Inst(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == PVAR) {
        Nodo * n = Asig(q, nodos);
        if(q->front()->get_tipo() == SEQ) {
            NodoSeq * m = new NodoSeq(q->front()->clona());
            nodos->push(m);
            pop_del(q);
            m->set_izq(n);
            return m;
        }
        return error("Punto y coma ';' esperado.", q, nodos);
    }
    
    else if(q->front()->get_tipo() == NUM
            || q->front()->get_tipo() == VAR
            || q->front()->get_tipo() == IZQ
            || q->front()->get_tipo() == MENOS) {
        Nodo * n = Exp(q, nodos);
        if(q->front()->get_tipo() == SEQ) {
            NodoSeq * m = new NodoSeq(q->front()->clona());
            nodos->push(m);
            pop_del(q);
            m->set_izq(n);
            return m;
        }
        return error("Punto y coma ';' esperado.", q, nodos);
    }
    
    return error("Punto y coma ';' esperado.", q, nodos);
}

Nodo * Asig(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == PVAR) {
        pop_del(q);
        if(q->front()->get_tipo() == VAR) {
            NodoVar * n = new NodoVar(q->front()->clona());
            nodos->push(n);
            pop_del(q);
            Nodo *  m = AsigP(q, nodos);
            m->set_izq(n);
            return m;
        }
    }
    return error("Asignación esperada", q, nodos);
}

Nodo * AsigP(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == ASIG) {
        NodoAsig * n = new NodoAsig(q->front()->clona());
        nodos->push(n);
        pop_del(q);
        Nodo * m = Exp(q, nodos);
        n->set_der(m);
        return n;
    }
    return error("Asignación esperada", q, nodos);
}

Nodo * Exp(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == NUM
       || q->front()->get_tipo() == VAR
       || q->front()->get_tipo() == IZQ
       || q->front()->get_tipo() == MENOS) {
        Nodo * n = Term(q, nodos);
        Nodo * m = ExpP(q, nodos);
        if(m) {
            m->set_izq(n);
            return m;
        }
        return n;
    }
    return error("Expresión mal formada", q, nodos);
}

Nodo * ExpP(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == MAS) {
        NodoSum * mas = new NodoSum(q->front()->clona());
        nodos->push(mas);
        pop_del(q);
        Nodo * term = Term(q, nodos);
        Nodo * expp = ExpP(q, nodos);
        if(expp) {
            expp->set_izq(term);
            mas->set_der(expp);
        }
        else
            mas->set_der(term);
        return mas;
    }

    else if(q->front()->get_tipo() == MENOS) {
        NodoMenos * menos = new NodoMenos(q->front()->clona());
        nodos->push(menos);
        pop_del(q);
        Nodo * term = Term(q, nodos);
        Nodo * expp = ExpP(q, nodos);
        if(expp) {
            expp->set_izq(term);
            menos->set_der(expp);
        }
        else
            menos->set_der(term);
        return menos;
    }
    
    else if(q->front()->get_tipo() == DER
            || q->front()->get_tipo() == SEQ
            || q->front()->get_tipo() == MULT
            || q->front()->get_tipo() == DIV) 
        return NULL;    
    
    return error("Expresión mal formada", q, nodos);
}

Nodo * Term(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == NUM
       || q->front()->get_tipo() == VAR
       || q->front()->get_tipo() == IZQ
       || q->front()->get_tipo() == MENOS) {
        Nodo * fact = Fact(q, nodos);
        Nodo * termp = TermP(q, nodos);
        if(termp) {
            termp->set_izq(fact);
            return termp;
        }
        return fact;
    }    
    return error("Expresión mal formada", q, nodos);
}

Nodo * TermP(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == MULT) {
        NodoMult * mult = new NodoMult(q->front()->clona());
        nodos->push(mult);
        pop_del(q);
        Nodo * fact = Fact(q, nodos);
        Nodo * termp = TermP(q, nodos);
        if(termp) {
            termp->set_izq(fact);
            mult->set_der(termp);
        }
        else
            mult->set_der(fact);
        return mult;
    }
    
    else if(q->front()->get_tipo() == DIV) {
        NodoDiv * div = new NodoDiv(q->front()->clona());
        nodos->push(div);
        pop_del(q);
        Nodo * fact = Fact(q, nodos);
        Nodo * termp = TermP(q, nodos);
        if(termp) {
            termp->set_izq(fact);
            div->set_der(termp);
        }
        else
            div->set_der(fact);
        return div;
    }

    else if(q->front()->get_tipo() == DER
            || q->front()->get_tipo() == SEQ
            || q->front()->get_tipo() == MAS
            || q->front()->get_tipo() == MENOS)
        return NULL;
    
    return error("Expresión mal formada", q, nodos);
}

Nodo * Fact(queue<Token*> * q, queue<Nodo*> * nodos) {
    if(q->front()->get_tipo() == NUM) {
        NodoNum * n = new NodoNum(q->front()->clona());
        nodos->push(n);
        pop_del(q);
        return n;
    }

    else if(q->front()->get_tipo() == VAR) {
        NodoVar * n = new NodoVar(q->front()->clona());
        nodos->push(n);
        pop_del(q);
        return n;
    }

    else if(q->front()->get_tipo() == IZQ) {
        pop_del(q);
        Nodo * n = Exp(q, nodos);
        if(q->front()->get_tipo() == DER) {
            pop_del(q);
            return n;
        }
        return error("Paréntesis derecho ')' esperado.", q, nodos);
    }

    else if(q->front()->get_tipo() == MENOS) {
        NodoNeg * neg = new NodoNeg(q->front()->clona());
        nodos->push(neg);
        pop_del(q);
        Nodo * exp = Exp(q, nodos);
        neg->set_izq(exp);
        return neg;
    }
    
    return error("Expresión mal formada", q, nodos);
}

void pop_del(queue<Token*> * q) {
    Token *t = q->front();
    q->pop();
    delete t;
}
