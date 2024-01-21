/**
 * @file Token.h
 * @brief 定义了 Trivia 类
 * @author yangyunzhao@gmail.com
 */

#pragma once
#include "parser/TokenKind.h"
#include "parser/TriviaKind.h"
#include <string_view>

/**
 * @class Trivia
 * @brief 表示源代码中的附加信息
 */
class Trivia {
public:
    /**
     * @brief 构造函数
     * @param kind 附加信息的类型
     * @param text 附加信息的文本内容
     */
    Trivia(TriviaKind kind, std::string_view text);

    /**
     * @brief 获取附加信息的类型
     * @return 附加信息的类型
     */
    TriviaKind getKind() const;

    /**
     * @brief 获取附加信息的文本内容
     * @return 附加信息的文本内容
     */
    std::string_view getText() const;

private:
    TriviaKind kind; ///< 附加信息的类型
    std::string_view text; ///< 附加信息的文本内容
};

class Token {
public:
    Token(TokenKind kind, std::string_view text);

    TokenKind getKind() const;
    std::string_view getText() const;

private:
    TokenKind kind;
    std::string_view text;
};