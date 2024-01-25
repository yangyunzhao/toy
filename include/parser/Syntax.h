#pragma once
#include "parser/SyntaxKind.h"
#include "parser/SyntaxNode.h"
#include "parser/Token.h"
#include "util/Util.h"
#include <variant>

namespace toy {

    template<typename T>
    concept not_null = 
        !std::is_assignable_v<T&, std::nullptr_t> && 
        requires(T t) {
            { *t } -> std::convertible_to<typename std::pointer_traits<T>::element_type&>;
            { t->*t } -> std::convertible_to<typename std::pointer_traits<T>::element_type*>;
        };

    struct ExpressionSyntax : public SyntaxNode {
        explicit ExpressionSyntax(SyntaxKind kind) : SyntaxNode(kind) {}
        explicit ExpressionSyntax(const ExpressionSyntax&) = default;
        static bool isKind(SyntaxKind kind);
    };

    struct BinaryExpression : public ExpressionSyntax {
        not_null<ExpressionSyntax*> left;
        Token op;
        not_null<ExpressionSyntax*> right;

        BinaryExpression(SyntaxKind kind, not_null<ExpressionSyntax*> left, Token op, not_null<ExpressionSyntax*> right)
            : ExpressionSyntax(kind), left(left), op(op), right(right) {
            this->left->setParent(this);
            this->right->setParent(this);
        }

        explicit BinaryExpression(const BinaryExpression&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
    struct ParenthesizedExpression : public ExpressionSyntax {
        Token leftParen;
        not_null<ExpressionSyntax*> inner;
        Token rightParen;

        ParenthesizedExpression(SyntaxKind kind, Token leftParen, not_null<ExpressionSyntax*> inner, Token rightParen)
            : ExpressionSyntax(kind), leftParen(leftParen), inner(inner), rightParen(rightParen) {
            this->inner->setParent(this);
        }

        explicit ParenthesizedExpression(const ParenthesizedExpression&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
    struct NumberExpression : public ExpressionSyntax {
        Token value;

        NumberExpression(SyntaxKind kind, Token value)
            : ExpressionSyntax(kind), value(value) {
        }

        explicit NumberExpression(const NumberExpression&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
}