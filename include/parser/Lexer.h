#pragma once

#include <string_view>
#include "Token.h"

class Lexer {
public:
	Lexer(std::string_view text);

	Token lexToken();

private:
	std::string_view text;
	size_t pos;
	char currentChar;

	void error();
	void advance();
	void skipWhitespace();
	std::string_view integer();
};
