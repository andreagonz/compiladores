#include<string>
#include"token.h"
#include"nodo.h"
#include<iostream>

using namespace std;

Nodo * Nodo::get_izq() {
    return izq;
}

Nodo * Nodo::get_der() {
    return der;
}

Token * Nodo::get_token() {
    return token;
}

Tipo Nodo::get_tipo() {
    return token->get_tipo();
}

void Nodo::set_izq(Nodo * n) {    
    izq = n;
}

void Nodo::set_der(Nodo * n){
    der = n;
}

void Nodo::set_token(Token * t){
    token = t;
}

string Nodo::str() {
    return token->str();
}

string str(Nodo * n) {
    int p = profundidad(n) + 1;
    bool rama[p];
    for (int i = 0; i < p; i++)
        rama[i] = false;    
    string s = aCadena(n, 0, rama);
    return s.substr(0, s.length()-1);
}

string aCadena(Nodo * vertice, int nivel, bool rama[]) {
    string s = vertice->str() + "\n";
    rama[nivel] = true;
    if (vertice->get_izq() && vertice->get_der()) {
        s += espacios(nivel, rama);
        s += "├─›";
        s += aCadena(vertice->get_izq(), nivel + 1, rama);
        s += espacios(nivel, rama);
        s += "└─»";
        rama[nivel] = false;
        s += aCadena(vertice->get_der(), nivel + 1, rama);
    } else if (vertice->get_izq()) {
        s += espacios(nivel, rama);
        s += "└─›";
        rama[nivel] = false;
        s += aCadena(vertice->get_izq(), nivel + 1, rama);
    } else if (vertice->get_der()) {
        s += espacios(nivel, rama);
        s += "└─»";
        rama[nivel] = false;
        s += aCadena(vertice->get_der(), nivel + 1, rama);
    }
    return s;
}

string espacios(int n, bool rama[]) {
    string s = "";
    for (int i = 0; i < n; i++)
        if (rama[i])
            s += "│  ";
        else
            s += "   ";
    return s;
}

int profundidad(Nodo * v){
    int izq = -1;
    int der = -1;
    if(v->get_izq())
        izq = profundidad(v->get_izq());
    
    if(v->get_der())
        der = profundidad(v->get_der());

    if(izq > der)
        return izq + 1;
    return der + 1;
}
