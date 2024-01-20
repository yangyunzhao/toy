#include "parser/Lexer.h"
#include <stdexcept>
#include <spdlog/spdlog.h>

Lexer::Lexer(std::string_view text) : text(text), pos(0), currentChar(text.at(0)) {

}

void Lexer::error() {
	throw std::runtime_error("Invalid character");
}

void Lexer::advance() {
	pos++;
	if (pos > text.length() - 1) {
		currentChar = '\0';
	}
	else {
		currentChar = text.at(pos);
	}
}

void Lexer::skipWhitespace() {
	while (currentChar != '\0' && isspace(currentChar)) {
		advance();
	}
}

std::string_view Lexer::integer() {
	size_t startPos = pos;
	while (currentChar != '\0' && isdigit(currentChar)) {
		advance();
	}
	return text.substr(startPos, pos - startPos);
}

Token Lexer::lexToken() {
	while (currentChar != '\0') {

		if (isspace(currentChar)) {
			spdlog::info("Whitespace encountered, skipping");
			skipWhitespace();
			continue;
		}

		if (isdigit(currentChar)) {
			spdlog::info("Digit encountered, lexing integer");
			return Token{ TokenKind::Integer, integer() };
		}

		if (currentChar == '+') {
			spdlog::info("Plus sign encountered");
			advance();
			return Token{ TokenKind::Plus, "+" };
		}

		if (currentChar == '-') {
			spdlog::info("Minus sign encountered");
			advance();
			return Token{ TokenKind::Minus, "-" };
		}

		if (currentChar == '*') {
			spdlog::info("Multiply sign encountered");
			advance();
			return Token{ TokenKind::Multiply, "*" };
		}

		if (currentChar == '/') {
			spdlog::info("Divide sign encountered");
			advance();
			return Token{ TokenKind::Divide, "/" };
		}

		spdlog::error("Unexpected character encountered");
		error();
	}

	return Token{ TokenKind::EndOfFile, "" };
}