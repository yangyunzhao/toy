#pragma once
#include <array>
#include <ostream>

enum class TriviaKind {
    Whitespace,
    Comment,
};

/**
 *  这是一个重载的输出流运算符，它允许我们直接将TriviaKind枚举值输出到std::ostream对象，如std::cout
 */
std::ostream& operator<<(std::ostream& os, TriviaKind kind);

/**
 *  这个函数将TriviaKind枚举值转换为字符串表示，这在打印调试信息或错误消息时非常有用
 */
std::string_view toString(TriviaKind kind);

/**
 *  这个类包含一个静态数组，数组的元素是所有的TriviaKind枚举值。这在需要遍历所有TriviaKind值的情况下非常有用
 */
class TriviaKind_traits {
public: 
    static const std::array<TriviaKind, 2> values;
};