%option C++ noyywrap

%{
    using namespace std;
    int linea = 1;
    int col = 1;
%}

num [0-9]+|[0-9]+\.[0-9]+
var   [a-z]

%%
{num}   {col++;}
{var}     {col++; }
"+"       {col++; }
"-"        {col++; }
"*"        {col++; }
"/"        {col++; }
"("        {col++; }
")"        {col++; }
";"        {col++; }
"="       {col++; }
[ \t\r]   {col++;}
[\n]      {linea++; col = 1;}
.           {
                cout << "Carácter no reconocido en línea " << linea << ", columna " << col << ": " <<  yytext[0] << endln;
                exit(0);
             }
%%

int main( int /* argc */, char** /* argv */ ) {
    FlexLexer* lexer = new yyFlexLexer;
    while(lexer->yylex() != 0)
        ;
    return 0;
}
