#include <string_view>
#include <cctype>
#include "parser/lexer.h"

enum class TokenType {
	Integer,
	Plus,
	Minus,
	Multiply,
	Divide,
	EndOfFile,
	Trivia
};

class Token {
public:
	Token(TokenType type, std::string_view text)
		: type(type), text(text) {}

	TokenType getType() const { return type; }
	std::string_view getText() const { return text; }

private:
	TokenType type;
	std::string_view text;
};

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
					return Token(TokenType::Plus, "+");
				case '-':
					return Token(TokenType::Minus, "-");
				case '*':
					return Token(TokenType::Multiply, "*");
				case '/':
					return Token(TokenType::Divide, "/");
				}
			}
		}
		return Token(TokenType::EndOfFile, "");
	}

private:
	Token lexNumber() {
		size_t start = index - 1;
		while (index < source.size() && std::isdigit(source[index])) {
			index++;
		}
		return Token(TokenType::Integer, source.substr(start, index - start));
	}

	Token lexTrivia() {
		size_t start = index - 1;
		while (index < source.size() && std::isspace(source[index])) {
			index++;
		}
		return Token(TokenType::Trivia, source.substr(start, index - start));
	}

	std::string_view source;
	size_t index;
};