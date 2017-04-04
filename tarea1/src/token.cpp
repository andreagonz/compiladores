enum Tipo {
    NUM,
    VAR,
    MAS,
    DIV,
    MULT,
    MENOS,
    ASIG,
    IZQ,
    DER
};

class Token {
protected:
    enum Tipo tipo;
public:
    Token(enum Tipo t) : tipo(t) {}
    enum Tipo get_tipo(void) {return tipo;}
};

class Num: Token {
    int num;
public:
    Num(enum Tipo t) : Token(t) {}
};

class Var: Token {
    char c;
public:
    Var(enum Tipo t) : Token(t) {}
};

class Op: Token {
public:
    Op(enum Tipo t) : Token(t) {}
};

class Asig: Token {
public:
    Asig(enum Tipo t) : Token(t) {}
};

class Par: Token {
public:
    Par(enum Tipo t) : Token(t) {}
};
