#pragma once
#include "parser/TokenKind.h"
#include "parser/TriviaKind.h"
#include <string_view>

class Trivia {
public:
    Trivia(TriviaKind kind, std::string_view text);

    TriviaKind getKind() const;
    std::string_view getText() const;

private:
    TriviaKind kind;
    std::string_view text;
};

class Token {
public:
    Token(TokenKind kind, std::string_view text);

    TokenKind getKind() const;
    std::string_view getText() const;

private:
    TokenKind kind;
    std::string_view text;
};