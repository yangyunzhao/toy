#include "parser/Lexer.h"
#include <spdlog/spdlog.h>
#include <stdexcept>

Lexer::Lexer(std::string_view text)
    : text(text), pos(0), currentChar(text.empty() ? '\0' : text[0]), state(LexerState::Normal) {
}

void Lexer::error() {
    throw std::runtime_error("Invalid character");
}

void Lexer::advance(int offset) {
    for (int idx = 0; idx < offset; ++idx) {
        pos++;
        if (pos > text.length() - 1) {
            currentChar = '\0';
        } else {
            currentChar = text.at(pos);
        }
    }
}

void Lexer::skipWhitespace(std::vector<Trivia>& trivia) {
    size_t startPos = pos;
    while (isspace(currentChar)) {
        advance();
    }
    if (pos > startPos) {
        trivia.push_back({TriviaKind::Whitespace, text.substr(startPos, pos - startPos)});
    }
}

std::string_view Lexer::integer() {
    size_t startPos = pos;
    while (isdigit(currentChar)) {
        advance();
    }
    return text.substr(startPos, pos - startPos);
}

Token Lexer::lexToken() {
    std::vector<Trivia> trivia; // 用于存储Trivia信息

    while (currentChar != '\0') {
        if (isspace(currentChar)) {
            spdlog::info("Whitespace encountered, skipping");
            skipWhitespace(trivia);
            continue;
        }

        if (isdigit(currentChar)) {
            spdlog::info("Digit encountered, lexing integer");
            return Token{TokenKind::Integer, integer()};
        }

        if (currentChar == '+') {
            spdlog::info("Plus sign encountered");
            advance();
            return Token{TokenKind::Plus, "+"};
        }

        if (currentChar == '-') {
            spdlog::info("Minus sign encountered");
            advance();
            return Token{TokenKind::Minus, "-"};
        }

        if (currentChar == '*') {
            spdlog::info("Multiply sign encountered");
            advance();
            return Token{TokenKind::Multiply, "*"};
        }

        if (currentChar == '/') {
            if (peek(1) == '*') {
                // 处理块注释
                scanBlockComment(trivia);
                continue; // 继续查找下一个Token
            } else if (peek(1) == '/') {
                // 处理行注释
                scanLineComment(trivia);
                continue; // 继续查找下一个Token
            } else {
                // 确实是除法操作符
                spdlog::info("Divide sign encountered");
                advance();
                return Token{TokenKind::Divide, "/"};
            }
        }

        if (currentChar == '(') {
            spdlog::info("Left Parenthesis sign encountered");
            advance();
            return Token{TokenKind::OpenParen, "("};
        }

        if (currentChar == ')') {
            spdlog::info("Right Parenthesis sign encountered");
            advance();
            return Token{TokenKind::CloseParen, ")"};
        }

        spdlog::error("Unexpected character encountered");
        error();
    }

    return Token{TokenKind::EndOfFile, ""};
}

void Lexer::scanBlockComment(std::vector<Trivia>& trivia) {
    size_t startPos = pos;
    int nestedLevel = 1; // 初始化嵌套级别
    advance(2);          // 跳过初始的 "/*"

    while (nestedLevel > 0 && currentChar != '\0') {
        if (currentChar == '/' && peek(1) == '*') {
            // 增加嵌套级别
            nestedLevel++;
            advance(2); // 跳过新的 "/*"
        } else if (currentChar == '*' && peek(1) == '/') {
            // 减少嵌套级别
            nestedLevel--;
            advance(2); // 跳过结束的 "*/"
        } else {
            advance();
        }
    }

    if (nestedLevel != 0) {
        error(); // 如果嵌套级别不为0，则注释未正确结束
    } else {
        trivia.push_back({TriviaKind::BlockComment, text.substr(startPos, pos - startPos)});
    }
}

void Lexer::scanLineComment(std::vector<Trivia>& trivia) {
    size_t startPos = pos;
    advance(2); // 跳过 "//"
    while (currentChar != '\0' && currentChar != '\n') {
        advance();
    }
    trivia.push_back({TriviaKind::LineComment, text.substr(startPos, pos - startPos)});
}

std::vector<Trivia> Lexer::lexTrivia() {
    std::vector<Trivia> trivia;
    while (true) {
        if (state == LexerState::Normal) {
            if (isspace(currentChar)) {
                skipWhitespace(trivia);
            } else if (currentChar == '/' && peek(1) == '*') {
                state = LexerState::InBlockComment;
                scanBlockComment(trivia);
            } else if (currentChar == '/' && peek(1) == '/') {
                state = LexerState::InLineComment;
                scanLineComment(trivia);
            } else {
                break;
            }
        } else if (state == LexerState::InBlockComment) {
            scanBlockComment(trivia);
            if (currentChar == '*' && peek(1) == '/') {
                state = LexerState::Normal;
                advance(2); // 跳过注释结束标记
            }
        } else if (state == LexerState::InLineComment) {
            scanLineComment(trivia);
            if (currentChar == '\n') {
                state = LexerState::Normal;
            }
        }
    }
    return trivia;
}

char Lexer::peek(int offset) const {
    size_t peekPos = pos + offset;
    if (peekPos >= text.length()) {
        return '\0'; // 如果超出文本范围，则返回空字符
    }
    return text[peekPos];
}
void Lexer::backTracking() {
    if (pos > 0) {
        pos--;
        currentChar = text[pos];
    }
}