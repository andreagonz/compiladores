#ifndef NODO_H
#define NODO_H

//#include<string>

class Nodo {
protected:
    Nodo izq;
    Nodo der;
    Nodo padre;    
public:
Nodo() : {}
    Nodo get_izq(void);
    Nodo get_der(void);
    Nodo get_padre(void);
};

#endif
