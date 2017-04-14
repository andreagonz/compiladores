%option C++ noyywrap

%{
    #include "token.h"
    #include "nodo.h"
    #include "asintactico.h"
    #include <fstream>
    #include <queue>
    #include <string>
    
    using namespace std;
    int linea = 1;
    int col = 1;
    queue<Token*> * tokens = new queue<Token*>;
    queue<Nodo*> * nodos = new queue<Nodo*>;
%}

num	[0-9]+|[0-9]+\.[0-9]+
var	[a-z]

%%
"var"	{
	    Token * t = new Token(PVAR, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}
{num}	{
	    Token * t = new Token(NUM, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

{var}	{
	    Token * t = new Token(VAR, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"+"	{
	    Token * t = new Token(MAS, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"-"	{
	    Token * t = new Token(MENOS, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"*"	{
	    Token * t = new Token(MULT, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"/"	{
	    Token * t = new Token(DIV, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"("	{
	    Token * t = new Token(IZQ, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

")"	{
	    Token * t = new Token(DER, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

";"	{
	    Token * t = new Token(SEQ, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

"="	{
	    Token * t = new Token(ASIG, YYText(), linea, col);
	    tokens->push(t);
	    col++;            
	}

[ \t\r]	{
	    col++;
	}

[\n]	{
	    linea++;
	    col = 1;
	}
.	{
	    cout << "Carácter no reconocido en línea " << linea << ", columna " << col << ": " <<  yytext[0] << "\n";
	    exit(0);
	}
%%

int main( int argc, char **argv ) {
    ifstream in(argv[1]);
    if(!in.is_open()) {
        cout << "Archivo inválido" << endl;
        return 1;
    }
    FlexLexer* lexer = new yyFlexLexer(in, cout);
    lexer->yylex();
    in.close();

    //Parser (lanza error si tiene error sintactico la entrada)
    Nodo * n = S(tokens, nodos);
    cout << "Exito" << endl;

    cout << str(n) << endl;
    
    clear(tokens, nodos);   
    
    // CHECAR QUE LA COLA NO SE VACIE AL CHECAR EL TIPO EN ASINTACTICO
    
    //Interpretar usando cosa de visitor, regresa resultados: (un diccionario con las variables y sus valores asignados)
    return 0;
}
