#ifndef VISITOR_H
#define VISITOR_H

#include<unordered_map>

class NodoNum;
class NodoVar;
class NodoSum;
class NodoMenos;
class NodoMult;
class NodoDiv;
class NodoNeg;
class NodoAsig;
class NodoSeq;

class Visitor {
public:
    virtual void visitaNodoNum(NodoNum * n) = 0;
    virtual void visitaNodoVar(NodoVar * n)  = 0;
    virtual void visitaNodoSum(NodoSum * n) = 0;
    virtual void visitaNodoMenos(NodoMenos * n) = 0;
    virtual void visitaNodoMult(NodoMult * n) = 0;
    virtual void visitaNodoDiv(NodoDiv * n) = 0;
    virtual void visitaNodoNeg(NodoNeg * n) = 0;
    virtual void visitaNodoAsig(NodoAsig * n) = 0;
    virtual void visitaNodoSeq(NodoSeq * n) = 0;
};

class VisitorInterpreta: public Visitor {
    float resultado;
    bool error;
    std::unordered_map<std::string, float> * vars;
public:
VisitorInterpreta(std::unordered_map<std::string, float> * um) : resultado(0), vars(um), error(false) {}
    void visitaNodoNum(NodoNum * n);
    void visitaNodoVar(NodoVar * n);
    void visitaNodoSum(NodoSum * n);
    void visitaNodoMenos(NodoMenos * n);
    void visitaNodoMult(NodoMult * n);
    void visitaNodoDiv(NodoDiv * n);
    void visitaNodoNeg(NodoNeg * n);
    void visitaNodoAsig(NodoAsig * n);
    void visitaNodoSeq(NodoSeq * n);
    bool hubo_error();
};

#endif
