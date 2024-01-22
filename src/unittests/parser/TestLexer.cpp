#include "catch2/catch.hpp"
#include "parser/Lexer.h"

TEST_CASE("Lexer lexToken Normal", "[Lexer]") {
    SECTION("lexToken should lex integers") {
        Lexer lexer("123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }

    SECTION("lexToken should lex integers") {
        Lexer lexer("-123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Minus);
        REQUIRE(token.getText() == "-");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }

    SECTION("lexToken should lex plus sign") {
        Lexer lexer("+");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Plus);
        REQUIRE(token.getText() == "+");
    }

    SECTION("lexToken should lex minus sign") {
        Lexer lexer("-");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Minus);
        REQUIRE(token.getText() == "-");
    }

    SECTION("lexToken should lex multiply sign") {
        Lexer lexer("*");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Multiply);
        REQUIRE(token.getText() == "*");
    }

    SECTION("lexToken should lex divide sign") {
        Lexer lexer("/");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Divide);
        REQUIRE(token.getText() == "/");
    }

    SECTION("lexToken should skip whitespace") {
        Lexer lexer(" 123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }

    SECTION("lexToken should lex multiple tokens") {
        Lexer lexer("123+456*789");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Plus);
        REQUIRE(token.getText() == "+");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "456");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Multiply);
        REQUIRE(token.getText() == "*");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "789");
    }

    SECTION("lexToken should lex left parenthesis") {
        Lexer lexer("(");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::OpenParen);
        REQUIRE(token.getText() == "(");
    }

    SECTION("lexToken should lex right parenthesis") {
        Lexer lexer(")");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::CloseParen);
        REQUIRE(token.getText() == ")");
    }

    SECTION("lexToken should lex multiple tokens with parentheses") {
        Lexer lexer("(123+456)*789");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::OpenParen);
        REQUIRE(token.getText() == "(");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Plus);
        REQUIRE(token.getText() == "+");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "456");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::CloseParen);
        REQUIRE(token.getText() == ")");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Multiply);
        REQUIRE(token.getText() == "*");
        token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "789");
    }

    SECTION("lexToken should lex right parenthesis") {
        Lexer lexer("/**/");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::EndOfFile);
        REQUIRE(token.getText() == "");
    }

    SECTION("lexToken should lex line comment") {
        Lexer lexer("// This is a comment\n123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }

    SECTION("lexToken should lex block comment") {
        Lexer lexer("/* This is a comment */123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }

    SECTION("lexToken should lex nested block comment") {
        Lexer lexer("/* This is a /* nested */ comment */123");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "123");
    }
}

TEST_CASE("Lexer lexToken Arithmetic", "[Lexer][Arithmetic]") {
    SECTION("lexToken should lex divide sign", "[Divide]") {
        Lexer lexer("/");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Divide);
        REQUIRE(token.getText() == "/");
    }
}

TEST_CASE("Lexer lexToken Brackets", "[Lexer][Brackets]") {
    SECTION("lexToken should lex open bracket", "[OpenBracket]") {
        Lexer lexer("(");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::OpenParen);
        REQUIRE(token.getText() == "(");
    }

    SECTION("lexToken should lex close bracket", "[CloseBracket]") {
        Lexer lexer(")");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::CloseParen);
        REQUIRE(token.getText() == ")");
    }
}