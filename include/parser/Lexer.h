/**
 * @file  Lexer.h
 * @brief 包含了词法分析器类的头文件。
 * @author yangyunzhao@gmail.com
 */

#pragma once

#include "Token.h"
#include <string_view>
#include <vector>

/**
 * @brief 状态枚举
 */
enum class LexerState {
    Normal,         /**< 正常状态 */
    InBlockComment, /**< 处于块注释状态 */
    InLineComment   /**< 处于行注释状态 */
};

/**
 * @brief 词法分析器类，用于将输入的文本解析为标记和Trivia
 */
class Lexer {
public:
    /**
     * @brief 构造函数
     * @param text 要解析的文本
     */
    Lexer(std::string_view text);

    /**
     * @brief 解析下一个标记
     * @return 解析得到的标记
     */
    Token lexToken();

    /**
     * @brief 解析Trivia
     * @return 解析得到的Trivia向量
     */
    std::vector<Trivia> lexTrivia(); // 用于处理Trivia

private:
    std::string_view text; /**< 要解析的文本 */
    size_t pos;            /**< 当前解析位置 */
    char currentChar;      /**< 当前字符 */
    LexerState state;      /**< 当前解析状态 */

    /**
     * @brief 报告解析错误
     */
    void error();

    /**
     * @brief 回溯解析位置
     */
    void backTracking();

    /**
     * @brief 前进解析位置
     * @param offset 前进的偏移量，默认为1
     */
    void advance(int offset = 1);

    /**
     * @brief 查看指定偏移量的字符
     * @param offset 偏移量，默认为0
     * @return 指定偏移量的字符
     */
    char peek(int offset = 0) const; // 新增peek方法

    /**
     * @brief 解析整数
     * @return 解析得到的整数字符串
     */
    std::string_view integer();

    /**
     * @brief 扫描块注释
     * @param trivia 存储Trivia的向量
     */
    void scanBlockComment(std::vector<Trivia>& trivia);

    /**
     * @brief 扫描行注释
     * @param trivia 存储Trivia的向量
     */
    void scanLineComment(std::vector<Trivia>& trivia);

    /**
     * @brief 跳过空白字符
     * @param trivia 存储Trivia的向量
     */
    void skipWhitespace(std::vector<Trivia>& trivia);
};
