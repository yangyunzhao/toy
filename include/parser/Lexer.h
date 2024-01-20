#include <string_view>
#include <cctype>
#include "parser/TokenKind.h"
#include "parser/TriviaKind.h"

class Token {
public:
	Token(TokenKind type, std::string_view text)
		: type(type), text(text) {}

	TokenKind getType() const { return type; }
	std::string_view getText() const { return text; }

private:
	TokenKind type;
	std::string_view text;
};

class Lexer {
public:
	Lexer(std::string_view source);

	Token lex();

private:
	Token lexNumber();

	Token lexTrivia();

	std::string_view source;
	size_t index;
};