from tokenizador import Tokenizador
from parser import Parser
from token import Funcion

class Interprete():

    def __init__(self):
        self.tokenizador = Tokenizador()
        self.parser = Parser()
        
    def interpreta(self, eq):
        eq = ''.join(eq.split())
        lst = self.tokenizador.tokeniza(eq)
        cola = self.parser.inf_a_postf(lst)
        if not cola:
            return "Escribe una expresion valida"
        pila = []
        try:
            while cola:
                if cola[0].es_num:
                    pila.append(cola.popleft().num)
                elif cola[0].es_vf:
                    pila.append(cola.popleft().valor_vf)
                else:
                    t = cola.popleft()
                    a = pila.pop()
                    b = pila.pop()
                    if t.fun == Funcion.sum:
                        pila.append(a + b)
                    elif t.fun == Funcion.res:
                        pila.append(b - a)
                    elif t.fun == Funcion.div:
                        pila.append(b / a)
                    elif t.fun == Funcion.mult:
                        pila.append(a * b)
                    elif t.fun == Funcion.orr:
                        pila.append(a or b)
                    elif t.fun == Funcion.andd:
                        pila.append(a and b)
                    elif t.fun == Funcion.eq:
                        pila.append(a == b)
        except:
            return "Expresion no bien formada"
        res = pila.pop()
        if pila:
            return "Expresion no bien formada"
        return "Resultado: " + str(res)

vivo = True
intrp = Interprete()

while vivo:
    eq = input("Ingresa una expresion\n")
    print(intrp.interpreta(eq))
    eq = ""
    while eq != "s" and eq != "n":
        eq = input("¿Continuar? s/n\n")
        if eq == "n":
            vivo = False
