%define parse.error verbose
%locations

%{
    #include "ast.h"
    std::shared_ptr<CompUnitAST> root;

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char* msg);
%}

%union {
    CompUnitAST* compUnit;
    
    int64_t integer;
    double floatpoint;
    std::shared_ptr<std::string> token;
}