#pragma once

#include "parser/SyntaxKind.h"
#include "parser/Token.h"

namespace toy {
    //! @brief toy库的命名空间。
    class SyntaxNode {
    public:
        //! @brief 将语法节点转换为字符串表示。
        //! @return 语法节点的字符串表示。
        std::string toString() const;

        //! @brief 获取语法节点的第一个标记。
        //! @return 语法节点的第一个标记。
        Token getFirstToken() const;

        //! @brief 获取语法节点的最后一个标记。
        //! @return 语法节点的最后一个标记。
        Token getLastToken() const;

        //! @brief 获取父语法节点。
        //! @return 父语法节点。
        const SyntaxNode* getParent() const;

        //! @brief 获取父语法节点。
        //! @return 父语法节点。
        SyntaxNode* getParent();

        //! @brief 设置父语法节点。
        //! @param parent 父语法节点。
        void setParent(SyntaxNode* parent);

        //! @brief 获取指定索引处的子语法节点。
        //! @param index 子语法节点的索引。
        //! @return 指定索引处的子语法节点。
        const SyntaxNode* childNode(size_t index) const;

        //! @brief 获取子语法节点的数量。
        //! @return 子语法节点的数量。
        size_t childCount() const;

        //! @brief 获取指定索引处的子标记。
        //! @param index 子标记的索引。
        //! @return 指定索引处的子标记。
        Token childToken(size_t index) const;

        //! @brief 获取子节点的数量。
        //! @return 子节点的数量。
        size_t childCount() const;

        //! @brief 获取语法节点的语法类型。
        //! @return 语法节点的语法类型。
        SyntaxKind getKind() const;

        //! @brief 将语法节点转换为指定的类型。
        //! @tparam T 要转换的类型。
        //! @return 转换后的语法节点。
        template <typename T>
        T& as() {
            return *static_cast<T*>(this);
        }

        //! @brief 将语法节点转换为指定的类型。
        //! @tparam T 要转换的类型。
        //! @return 转换后的语法节点。
        template <typename T>
        const T& as() const {
            return *static_cast<const T*>(this);
        }

    protected:
        SyntaxNode* parent = nullptr; ///< 父语法节点。
        SyntaxKind kind;              ///< 语法节点的语法类型。

        //! @brief 使用指定的语法类型构造语法节点。
        //! @param kind 语法节点的语法类型。
        explicit SyntaxNode(SyntaxKind kind)
            : kind(kind) {
        }
    };

    //! @brief 表示一个标记或语法节点。
    struct TokenOrSyntax {
        //! @brief 使用标记构造一个TokenOrSyntax对象。
        //! @param token 标记。
        TokenOrSyntax(Token token)
            : value(token) {
        }

        //! @brief 使用语法节点构造一个TokenOrSyntax对象。
        //! @param node 语法节点。
        TokenOrSyntax(SyntaxNode* node)
            : value(node) {
        }

        //! @brief 使用nullptr构造一个TokenOrSyntax对象。
        //! @param nullptr_t nullptr。
        TokenOrSyntax(nullptr_t)
            : value(Token()) {
        }

        //! @brief 检查对象是否为标记。
        //! @return 如果对象是标记，则返回true，否则返回false。
        bool isToken() const {
            return value.index() == 0;
        }

        //! @brief 检查对象是否为语法节点。
        //! @return 如果对象是语法节点，则返回true，否则返回false。
        bool isNode() const {
            return value.index() == 1;
        }

        //! @brief 获取对象作为标记的访问权限。
        //! @return 标记。
        //! @throws std::bad_variant_access 如果对象实际上不是标记。
        Token token() const {
            return std::get<0>(value);
        }

        //! @brief 获取对象作为语法节点的访问权限。
        //! @return 语法节点。
        //! @throws std::bad_variant_access 如果对象实际上不是语法节点。
        const SyntaxNode* node() const {
            return std::get<1>(value);
        }

    protected:
        std::variant<Token, SyntaxNode*> value; ///< 标记或语法节点。
    };
} // namespace toy