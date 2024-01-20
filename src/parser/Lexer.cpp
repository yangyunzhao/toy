#include <string_view>
#include <cctype>
#include "parser/lexer.h"

Token::Token(TokenKind type, std::string_view text)
	: type(type), text(text) {
}

TokenKind Token::getType() const { return type; }
std::string_view Token::getText() const { return text; }

class Lexer {
public:
	Lexer(std::string_view source)
		: source(source), index(0) {}

	Token lex() {
		while (index < source.size()) {
			char c = source[index++];
			if (std::isspace(c)) {
				return lexTrivia();
			}
			else if (std::isdigit(c)) {
				return lexNumber();
			}
			else {
				switch (c) {
				case '+':
					return Token(TokenKind::Plus, "+");
				case '-':
					return Token(TokenKind::Minus, "-");
				case '*':
					return Token(TokenKind::Multiply, "*");
				case '/':
					return Token(TokenKind::Divide, "/");
				}
			}
		}
		return Token(TokenKind::EndOfFile, "");
	}

private:
	Token lexNumber() {
		size_t start = index - 1;
		while (index < source.size() && std::isdigit(source[index])) {
			index++;
		}
		return Token(TokenKind::Integer, source.substr(start, index - start));
	}

	Token lexTrivia() {
		size_t start = index - 1;
		while (index < source.size() && std::isspace(source[index])) {
			index++;
		}
		return Token(TokenKind::Trivia, source.substr(start, index - start));
	}

	std::string_view source;
	size_t index;
};