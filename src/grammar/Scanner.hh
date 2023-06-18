/**
 * Copyright © Mahjong squad
 * All Rights Reserved.
 * Authors:
 *          yangyunzhao@qq.com 
 */
 
#pragma once

#ifndef YY_DECL

#define	YY_DECL						    \
    toy::Parser::token_type				\
    toy::Scanner::lex(				    \
	toy::Parser::semantic_type* yylval, \
	toy::Parser::location_type* yylloc  \
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ToyFlexLexer
#include "FlexLexer.hh"
#undef yyFlexLexer
#endif

#include "parser.h"

namespace toy {
    class Scanner : public ToyFlexLexer {
    public:
        Scanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);
        virtual ~Scanner();
        virtual Parser::token_type lex(Parser::semantic_type* yylval, Parser::location_type* yylloc);
        void set_debug(bool b);
    };
}