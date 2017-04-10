%option C++ noyywrap

%{
    #include "token.h"
    #include <fstream>
    #include <vector>
    
    using namespace std;
    int linea = 1;
    int col = 1;
    vector<Token> tokens;
%}

num	[0-9]+|[0-9]+\.[0-9]+
var		[a-z]

%%
{num}	{
			col++;
		}

{var}	{
			col++;
			Tipo tipo = VAR;
			Token t(tipo);
			tokens.push_back(t);
			for(int i = 0; i < tokens.size(); i++)
			cout << tokens[i].get_tipo();
		}

"+"		{
			col++;
		}
"-"		{
			col++; 
		}
"*"		{
			col++; 
		}
"/"		{
			col++; 
		}
"("		{
			col++; 
		}
")"		{
			col++; 
		}
";"		{
			col++; 
		}
"="		{
			col++; 
		}
[ \t\r]	{
			col++;
		}
[\n]		{
			linea++;
			col = 1;
		}
.		{
			cout << "Carácter no reconocido en línea " << linea << ", columna " << col << ": " <<  yytext[0] << "\n";
			exit(0);
		}
%%

int main( int argc, char **argv ) {
    ifstream in(argv[1]);
    if(!in.is_open()) {
        cout << "Archivo inválido\n";
        return 1;
    }
    FlexLexer* lexer = new yyFlexLexer(in, cout);
    lexer->yylex();
    in.close();
    return 0;
}
