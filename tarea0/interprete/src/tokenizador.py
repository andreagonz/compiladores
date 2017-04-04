from token import Funcion
from token import Token

class Tokenizador:

    # Si regresa lista vacía, hubo error
    def tokeniza(self, eq):
        lst = []
        i = 0
        while i < len(eq):
            t = Token()
            if eq[i].isdigit():
                j = i
                while j < len(eq) and (eq[j].isdigit() or eq[j] == '.'):
                    j += 1
                num = 0
                try:
                    num = float(eq[i:j])
                except:
                    print("Expresion invalida: " + eq[i:j])
                    return []
                t.es_num = True
                t.num = num                
                i = j - 1
            elif eq[i] == "(":
                t.es_piz = True
            elif eq[i] == ")":
                t.es_pde = True
            elif eq[i] == "V":
                t.es_vf = True
                t.valor_vf = True
            elif eq[i] == "F":
                t.es_vf = True
                t.valor_vf = False
            else:
                t.es_fun = True
                if eq[i] == "/":
                    t.fun = Funcion.div
                elif eq[i] == "*":
                    t.fun = Funcion.mult
                elif eq[i] == "+":
                    t.fun = Funcion.sum
                elif eq[i] == "-":
                    t.fun = Funcion.res
                elif eq[i] == "=":
                    t.fun = Funcion.eq
                elif eq[i] == "v":
                    t.fun = Funcion.orr
                elif eq[i] == "^":
                    t.fun = Funcion.andd
                else:
                    print("Expresion invalida: " + eq[i])
                    return []
            i += 1
            lst.append(t)
        return lst                                   
