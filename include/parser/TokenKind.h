/**
 * @file TokenKind.h
 * @brief 包含了TokenKind枚举类的头文件。
 * @author yangyunzhao@gmail.com
 */

#pragma once
#include <array>
#include <ostream>

namespace toy {
    //! @brief 表示词法单元的种类的枚举类
    enum class TokenKind {
        Unknown         ,        ///< 未知，默认
        Integer         ,        ///< 整数
        HexInteger      ,        ///< 十六进制整数
        BinaryInteger   ,        ///< 二进制整数
        Plus            ,        ///< 加号
        Minus           ,        ///< 减号
        Multiply        ,        ///< 乘号
        Divide          ,        ///< 除号
        OpenParen       ,        ///< 左括号
        CloseParen      ,        ///< 右括号
        EndOfFile       ,        ///< 文件结束标记
        UnderLine       ,        ///< 下划线
    };

    //! @brief 重载的输出流运算符，用于将TokenKind枚举值输出到std::ostream对象
    //! @param os 输出流对象
    //! @param kind TokenKind枚举值
    //! @return 输出流对象
    std::ostream& operator<<(std::ostream& os, TokenKind kind);

    //! @brief 将TokenKind枚举值转换为字符串表示
    //! @param kind TokenKind枚举值
    //! @return 字符串表示
    std::string_view toString(TokenKind kind);

    //! @brief 包含所有TokenKind枚举值的静态数组
    class TokenKind_traits {
    public: 
        static const std::array<TokenKind, 12> values;  ///< 包含所有TokenKind枚举值的静态数组
    };
}  // namespace toy