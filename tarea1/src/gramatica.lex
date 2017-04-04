%{
#include<stdio.h>
#include <stdlib.h>

int linea = 1;
int col = 1;

%}

num [0-9]+|[0-9]+\.[0-9]+
var   [a-z]

%%
{num}  {col++;}
{var}    {col++; }
"+"      {col++; }
"-"       {col++; }
"*"       {col++; }
"/"       {col++; }
"("       {col++; }
")"       {col++; }
";"       {col++; }
"="      {col++; }
[ \t\r]   {col++;}
[\n]      {linea++; col = 1;}
.           {printf("Carácter no reconocido en línea %d, columna %d: [%c]\n", linea, col, yytext[0]); exit(0);}
%%

int main() {
    yylex();
}
