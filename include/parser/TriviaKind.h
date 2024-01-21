/**
 * @file TriviaKind.h
 * @brief 包含了TriviaKind枚举类的头文件。
 * @author yangyunzhao@gmail.com
 */

#pragma once
#include <array>
#include <ostream>

/// @brief TriviaKind枚举定义了三种类型的Trivia
enum class TriviaKind {
    Whitespace  ,        ///< 空白
    BlockComment,        ///< 块注释
    LineComment ,        ///< 行注释
};

/**
 * @brief 重载的输出流运算符
 * 这是一个重载的输出流运算符，它允许我们直接将TriviaKind枚举值输出到std::ostream对象，如std::cout
 * 
 * @param os 输出流
 * @param kind TriviaKind枚举值
 * @return 返回输出流
 */
std::ostream& operator<<(std::ostream& os, TriviaKind kind);

/**
 * @brief 将TriviaKind枚举值转换为字符串
 * 这个函数将TriviaKind枚举值转换为字符串表示，这在打印调试信息或错误消息时非常有用
 * 
 * @param kind TriviaKind枚举值
 * @return 返回枚举值的字符串表示
 */
std::string_view toString(TriviaKind kind);

/**
 * @brief TriviaKind_traits类
 * 这个类包含一个静态数组，数组的元素是所有的TriviaKind枚举值。这在需要遍历所有TriviaKind值的情况下非常有用
 */
class TriviaKind_traits {
public: 
    static const std::array<TriviaKind, 3> values;
};