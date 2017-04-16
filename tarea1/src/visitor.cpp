#include"visitor.h"
#include"nodo.h"
#include<iostream>

using namespace std;

void VisitorInterpreta::visitaNodoNum(NodoNum * n) {
    if(!error)
        resultado = n->get_valor();    
}

void VisitorInterpreta::visitaNodoVar(NodoVar * n) {
    if(!error) {
        if(vars->find(n->get_token()->get_valor()) != vars->end())
            resultado = (*vars)[n->get_token()->get_valor()];
        else {
            error = true;
            cout << "Error de sintáxis en línea " << n->get_token()->get_linea() << ", columna "
                 << n->get_token()->get_col() << ". Variable '" << n->get_token()->get_valor() << "' no declarada." << endl;
        }
    }
}

void VisitorInterpreta::visitaNodoSum(NodoSum * n) {
    if(!error) {
        n->get_izq()->accept(this);
        float resi = resultado;
        n->get_der()->accept(this);
        float resd = resultado;
        resultado = resi + resd;
    }
}

void VisitorInterpreta::visitaNodoMenos(NodoMenos * n) {
    if(!error) {
        n->get_izq()->accept(this);
        float resi = resultado;
        n->get_der()->accept(this);
        float resd = resultado;
        resultado = resi - resd;
    }
}

void VisitorInterpreta::visitaNodoMult(NodoMult * n) {
    if(!error) {
        n->get_izq()->accept(this);
        float resi = resultado;
        n->get_der()->accept(this);
        float resd = resultado;
        resultado = resi * resd;
    }
}

void VisitorInterpreta::visitaNodoDiv(NodoDiv * n) {
    if(!error) {
        n->get_izq()->accept(this);
        float resi = resultado;
        n->get_der()->accept(this);
        float resd = resultado;
        resultado = resi / resd;
    }
}

void VisitorInterpreta::visitaNodoNeg(NodoNeg * n) {
    if(!error) {
        n->get_izq()->accept(this);
        resultado = -1 * resultado;
    }
}

void VisitorInterpreta::visitaNodoAsig(NodoAsig * n) {
    if(!error) {
        n->get_der()->accept(this);
        NodoVar * nv = (NodoVar*)(n->get_izq());
        (*vars)[nv->get_token()->get_valor()] = resultado;
    }
}

void VisitorInterpreta::visitaNodoSeq(NodoSeq * n) {
    if(!error) {
        n->get_izq()->accept(this);
        resultado = 0;
        if(n->get_der())
            n->get_der()->accept(this);
    }
}

bool VisitorInterpreta::hubo_error() {
    return error;
}
