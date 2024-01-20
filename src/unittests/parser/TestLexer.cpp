#include "parser/Lexer.h"
#include "catch2/catch.hpp"

TEST_CASE("Lexer lexToken", "[Lexer]") {
	SECTION("lexToken should lex integers") {
		Lexer lexer("123");
		Token token = lexer.lexToken();
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
}