%option C++ noyywrap

%{
    #include "token.h"
    #include "nodo.h"
    #include "asintactico.h"
    #include "visitor.h"
    #include <fstream>
    #include <queue>
    #include <string>
    #include <unordered_map>
    
    using namespace std;
    int linea = 1;
    int col = 1;
    queue<Token*> * tokens = new queue<Token*>;
    queue<Nodo*> * nodos = new queue<Nodo*>;
%}

num	[0-9]+|[0-9]+\.[0-9]+
var	[a-z][a-zA-Z0-9]*

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
            clear(tokens, nodos);
	    exit(1);
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

    Nodo * n = S(tokens, nodos);

    ofstream arbolf("arbol.txt");
    arbolf << str(n);
    arbolf.close();
    
    unordered_map<string, float> * vars = new unordered_map<string, float>;
    VisitorInterpreta * vi = new VisitorInterpreta(vars);
    n->accept(vi);
    if(!vi->hubo_error()) {
        for(auto elem : (*vars))
            cout << elem.first << ": " << elem.second << endl;
        ofstream logf("log.txt");
        logf << vi->get_log();
        logf.close();
    }
    
    clear(tokens, nodos);
    delete vi;
    delete vars;

    return 0;
}
