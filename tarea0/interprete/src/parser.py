from collections import deque

class Parser:
    
    def inf_a_postf(self, lst):
        cola = deque()
        pila = []
        for t in lst:
            if t.es_num or t.es_vf:
                cola.append(t)
            elif t.es_fun:
                while pila and pila[-1].es_fun and pila[-1].get_precedencia() <= t.get_precedencia():
                    cola.append(pila.pop())
                pila.append(t)
            elif t.es_piz:
                pila.append(t)
            elif t.es_pde:
                while pila and not pila[-1].es_piz:
                    cola.append(pila.pop())
                if not pila:
                    print("Parentesis no cierran")
                    return []
                pila.pop()
        while pila:
            if pila[-1].es_piz or pila[-1].es_pde:
                print("Parentesis no cierran")
                return []
            cola.append(pila.pop())
        return cola
