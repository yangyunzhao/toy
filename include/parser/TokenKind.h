#include <array>
#include <ostream>

enum class TokenKind {
    Integer,
    Plus,
    Minus,
    Multiply,
    Divide,
    EndOfFile,
};

std::ostream& operator<<(std::ostream& os, TokenKind kind);
std::string_view toString(TokenKind kind);

class TokenKind_traits {
public: static const std::array<TokenKind, 6> values;
};

/**
 *	std::ostream& operator<<(std::ostream& os, TokenKind kind); 这是一个重载的输出流运算符，它允许我们直接将TokenKind枚举值输出到std::ostream对象，如std::cout。
 *	std::string_view toString(TokenKind kind); 这个函数将TokenKind枚举值转换为字符串表示，这在打印调试信息或错误消息时非常有用。
 *	class TokenKind_traits 这个类包含一个静态数组，数组的元素是所有的TokenKind枚举值。这在需要遍历所有TokenKind值的情况下非常有用。
 */