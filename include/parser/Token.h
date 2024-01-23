/**
 * @file Token.h
 * @brief 定义了 Trivia 和Token 类，词法分析产物
 * @author yangyunzhao@gmail.com
 */

#pragma once
#include "parser/TokenKind.h"
#include "parser/TriviaKind.h"
#include <string_view>
namespace toy {
    //! @class Trivia
    //! @brief 表示源代码中的附加信息杨云召
    class Trivia {
    public:
        //! @brief 构造函数
        //! @param kind 附加信息的类型
        //! @param text 附加信息的文本内容
        Trivia(TriviaKind kind, std::string_view text);

        //! @brief 获取附加信息的类型
        //! @return 附加信息的类型
        TriviaKind getKind() const;

        //! @brief 获取附加信息的文本内容
        //! @return 附加信息的文本内容
        std::string_view getText() const;

    private:
        TriviaKind kind;       ///< 附加信息的类型
        std::string_view text; ///< 附加信息的文本内容
    };

    //! @brief 表示解析器中的一个标记。
    class Token {
    public:
        //! @brief 使用指定的类型和文本构造一个 Token 对象。
        //! @param kind 标记的类型。
        //! @param text 标记的文本。
        Token(TokenKind kind, std::string_view text);

        //! @brief 获取标记的类型。
        //! @return 标记的类型。
        TokenKind getKind() const;

        //! @brief 获取标记的文本。
        //! @return 标记的文本。
        std::string_view getText() const;

    private:
        TokenKind kind;        ///< 标记的类型。
        std::string_view text; ///< 标记的文本。
    };
} // namespace toy