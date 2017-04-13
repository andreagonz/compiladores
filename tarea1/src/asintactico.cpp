#include "asintactico.h"
#include "token.h"
#include<queue>
#include<string>
#include<iostream>
#include <stdlib.h>

using namespace std;

queue<Token> q;

void set_queue(queue<Token> queue) {
    q = queue;
}

bool error() {
    cout << "Error de sintáxis en línea " << q.front().get_linea() << ", columna "
         << q.front().get_col() << ": " <<  "[" << q.front().get_valor() << "]" << endl;
    exit(1);
    return false;
}

bool error(string s) {
    cout << "Error de sintáxis en línea " << q.front().get_linea() << ", columna "
         << q.front().get_col() << ": " <<  "[" << q.front().get_valor() << "]" << endl;
    cout << s << endl;
    exit(1);
    return false;
}

bool S() {
    if(q.front().get_tipo() == PVAR
       || q.front().get_tipo() == NUM
       || q.front().get_tipo() == VAR
       || q.front().get_tipo() == IZQ
       || q.front().get_tipo() == MENOS) {
        if(Inst())
            return Prog();
    }
    return error("Asignación o expresión experados.");
}

bool Prog() {
    if(q.empty())
        return true;
    else if(q.front().get_tipo() == PVAR
            || q.front().get_tipo() == NUM
            || q.front().get_tipo() == VAR
            || q.front().get_tipo() == IZQ
            || q.front().get_tipo() == MENOS) {
        if(Inst())
            return Prog();
    }
    return error();
}

bool Inst() {
    if(q.front().get_tipo() == PVAR) {
        if(Asig()) {
            if(q.front().get_tipo() == SEQ) {
                q.pop();
                return true;
            }
            return error("Punto y coma ';' esperado.");
        }
    }
    else if(q.front().get_tipo() == NUM
            || q.front().get_tipo() == VAR
            || q.front().get_tipo() == IZQ
            || q.front().get_tipo() == MENOS) {
        if(Exp()) {
            if(q.front().get_tipo() == SEQ) {
                q.pop();
                return true;
            }
            return error("Punto y coma ';' esperado.");
        }
    }
    //Not sure
    return error("Punto y coma ';' esperado.");
}

bool Asig() {
    if(q.front().get_tipo() == PVAR) {
        q.pop();
        if(q.front().get_tipo() == VAR) {
            q.pop();
            return AsigP();
        }
    }
    return error("Asignación esperada");
}

bool AsigP() {
    if(q.front().get_tipo() == ASIG) {
        q.pop();
        return Exp();
    }
    return error("Asignación esperada");
}

bool Exp() {
    if(q.front().get_tipo() == NUM
       || q.front().get_tipo() == VAR
       || q.front().get_tipo() == IZQ
       || q.front().get_tipo() == MENOS) {
        if(Term())
            return ExpP();
    }
    return error("Expresión mal formada");
}

bool ExpP() {
    if(q.front().get_tipo() == MAS) {
        q.pop();
        if(Term())
            return ExpP();
    }

    else if(q.front().get_tipo() == MENOS) {
        q.pop();
        if(Term())
            return ExpP();
    }
    
    else if(q.front().get_tipo() == DER
            || q.front().get_tipo() == SEQ
            || q.front().get_tipo() == MULT
            || q.front().get_tipo() == DIV)
        return true;
    
    return error("Expresión mal formada");
}

bool Term() {
    if(q.front().get_tipo() == NUM
       || q.front().get_tipo() == VAR
       || q.front().get_tipo() == IZQ
       || q.front().get_tipo() == MENOS) {
        if(Fact())
            return TermP();
    }    
    return error("Expresión mal formada");
}

bool TermP() {
    if(q.front().get_tipo() == MULT) {
        q.pop();
        if(Fact())
            return TermP();
    }

    else if(q.front().get_tipo() == DIV) {
        q.pop();
        if(Fact())
            return TermP();
    }

    else if(q.front().get_tipo() == DER
            || q.front().get_tipo() == SEQ
            || q.front().get_tipo() == MAS
            || q.front().get_tipo() == MENOS)
        return true;
    
    return error("Expresión mal formada");
}

bool Fact() {
    if(q.front().get_tipo() == NUM) {
        q.pop();
        return true;
    }

    else if(q.front().get_tipo() == VAR) {
        q.pop();
        return true;
    }

    else if(q.front().get_tipo() == IZQ) {
        q.pop();
        if(Exp()) {
            if(q.front().get_tipo() == DER) {
                q.pop();
                return true;
            }
            return error("Paréntesis derecho ')' esperado.");
        }
    }

    else if(q.front().get_tipo() == MENOS) {
        q.pop();
        return Exp();
    }
    
    return error("Expresión mal formada");
}
