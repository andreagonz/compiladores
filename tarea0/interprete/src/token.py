from enum import Enum

Funcion = Enum('Funcion', 'div mult sum res orr andd eq')

class Token:
    
    def __init__(self):
        self.num = 0
        self.valor_vf = False
        self.fun = None
        self.es_fun = False
        self.es_num = False
        self.es_vf = False
        self.es_piz = False
        self.es_pde = False

    def __str__(self):
        if self.es_fun:
            return str(self.fun)
        if self.es_num:
            return str(self.num)
        if self.es_vf:
            return str(self.valor_vf)
        if self.es_piz:
            return "("
        if self.es_pde:
            return ")"
        else:
            return "oy vey"

    def __repr__(self):
       return self.__str__()

    def get_precedencia(self):
        if self.es_fun:
            if self.fun == Funcion.mult or self.fun == Funcion.div:
                return 1
            if self.fun == Funcion.orr or self.fun == Funcion.andd:
                return 1
            if self.fun == Funcion.sum or self.fun == Funcion.res:
                return 2
            if self.fun == Funcion.eq:
                return 3
        else:
            return 0
