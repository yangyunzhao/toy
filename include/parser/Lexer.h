#pragma once

#include "Token.h"
#include <string_view>
#include <vector>

// 新增状态枚举
enum class LexerState {
    Normal,
    InBlockComment,
    InLineComment
};

class Lexer {
public:
    Lexer(std::string_view text);

    Token lexToken();
    std::vector<Trivia> lexTrivia(); // 用于处理Trivia

private:
    std::string_view text;
    size_t pos;
    char currentChar;
    LexerState state; // 当前解析状态

    void error();
    void advance(int offset = 1);
    char peek(int offset = 0) const; // 新增peek方法
    std::string_view integer();

    void scanBlockComment(std::vector<Trivia>& trivia);
    void scanLineComment(std::vector<Trivia>& trivia);
    void skipWhitespace(std::vector<Trivia>& trivia);
};
