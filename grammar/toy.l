/**
 * Copyright © Mahjong squad
 * All Rights Reserved.
 * Authors:
 *          yangyunzhao@qq.com 
 */
 
%{
    #include <string>
    #include "Scanner.hh"
    typedef toy::Parser::token token;
    typedef toy::Parser::token_type token_type;

#define yyterminate() return token::END
#define YY_NO_UNISTD_H
%}