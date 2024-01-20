#include <string_view>
#include <cctype>

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
	Lexer(std::string_view source);

	Token lex();

private:
	Token lexNumber();

	Token lexTrivia();

	std::string_view source;
	size_t index;
};