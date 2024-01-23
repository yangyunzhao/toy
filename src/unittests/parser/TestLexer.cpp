#include "catch2/catch.hpp"
#include "parser/Lexer.h"
using namespace toy;

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

TEST_CASE("Lexer lexToken HexInteger and BinaryInteger", "[Lexer]") {
    SECTION("HexInteger without underscore") {
        Lexer lexer("0x1F");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::HexInteger);
        REQUIRE(token.getText() == "0x1F");
    }

    SECTION("BinaryInteger without underscore") {
        Lexer lexer("0b1010");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::BinaryInteger);
        REQUIRE(token.getText() == "0b1010");
    }

    SECTION("HexInteger with underscore") {
        Lexer lexer("0x1_F");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::HexInteger);
        REQUIRE(token.getText() == "0x1_F");
    }

    SECTION("BinaryInteger with underscore") {
        Lexer lexer("0b10_10");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::BinaryInteger);
        REQUIRE(token.getText() == "0b10_10");
    }
}

TEST_CASE("Lexer lexToken HexInteger and BinaryInteger with underscore", "[Lexer]") {
    SECTION("HexInteger with underscore at the start") {
        Lexer lexer("0x_1F");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::HexInteger);
        REQUIRE(token.getText() == "0x_1F");
    }

    SECTION("BinaryInteger with underscore at the start") {
        Lexer lexer("0b_1010");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::BinaryInteger);
        REQUIRE(token.getText() == "0b_1010");
    }

    SECTION("HexInteger with underscore at the end") {
        Lexer lexer("0x1F_");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::HexInteger);
        REQUIRE(token.getText() == "0x1F_");
    }

    SECTION("BinaryInteger with underscore at the end") {
        Lexer lexer("0b1010_");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::BinaryInteger);
        REQUIRE(token.getText() == "0b1010_");
    }

    SECTION("HexInteger with multiple underscores") {
        Lexer lexer("0x1__F");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::HexInteger);
        REQUIRE(token.getText() == "0x1__F");
    }

    SECTION("BinaryInteger with multiple underscores") {
        Lexer lexer("0b10__10");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::BinaryInteger);
        REQUIRE(token.getText() == "0b10__10");
    }
}

TEST_CASE("Lexer lexToken DecimalInteger with multiple underscores", "[Lexer]") {
    SECTION("DecimalInteger with one underscore") {
        Lexer lexer("1_234");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "1_234");
    }

    SECTION("DecimalInteger with multiple underscores at different positions") {
        Lexer lexer("1_2_3_4");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "1_2_3_4");
    }

    SECTION("DecimalInteger with multiple underscores at the end") {
        Lexer lexer("1234__");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "1234__");
    }

    SECTION("DecimalInteger with multiple underscores at the start") {
        Lexer lexer("1234__5678");
        Token token = lexer.lexToken();
        REQUIRE(token.getKind() == TokenKind::Integer);
        REQUIRE(token.getText() == "1234__5678");
    }
}