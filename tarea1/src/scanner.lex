%option C++ noyywrap

%{
    #include "token.h"
    #include "asintactico.h"
    #include <fstream>
    #include <queue>
    #include <string>
    
    using namespace std;
    int linea = 1;
    int col = 1;
    queue<Token> tokens;
%}

num	[0-9]+|[0-9]+\.[0-9]+
var	[a-z]

%%
"var"	{
	    Token t(PVAR, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}
{num}	{
	    Token t(NUM, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

{var}	{
	    Token t(VAR, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"+"	{
	    Token t(MAS, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"-"	{
	    Token t(MENOS, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"*"	{
	    Token t(MULT, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"/"	{
	    Token t(DIV, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"("	{
	    Token t(IZQ, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

")"	{
	    Token t(DER, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

";"	{
	    Token t(SEQ, YYText(), linea, col);
	    tokens.push(t);
	    col++;            
	}

"="	{
	    Token t(ASIG, YYText(), linea, col);
	    tokens.push(t);
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
    set_queue(tokens);    
    S();
    
    cout << "Éxito" << endl;
    
    /*
    for(int i = 0; !tokens.empty(); i++) {
        cout << tokens.front().str() << " ";
        tokens.pop();
    }
    cout << "\n";
    */

    //Interpretar usando cosa de visitor, regresa resultados: (un diccionario con las variables y sus valores asignados)
    return 0;
}
