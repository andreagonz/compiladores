#include "token.h"
#include <string>

std::string tipo_str(Tipo t) {
    switch(t){
    case NUM:
        return "NUM";
    case VAR:
        return "VAR";
    case MAS:
        return "MAS";
    case DIV:
        return "DIV";
    case MULT:
        return "MULT";
    case MENOS:
        return "MENOS";            
    case ASIG:
        return "ASIG";            
    case IZQ:
        return "IZQ";            
    case DER:
        return "DER";            
    case SEQ:
        return "SEQ";
    case PVAR:
        return "PVAR";
    default:
        return "";
    }
}

Tipo Token::get_tipo() {
    return tipo;
}

int Token:: get_linea() {
    return linea;
}

int Token:: get_col() {
    return col;
}

std::string Token::get_valor() {
    return valor;
}

std::string Token::str() {
    return "(" + tipo_str(tipo) + ", " + valor + ")";
}
