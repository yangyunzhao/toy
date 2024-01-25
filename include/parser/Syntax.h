#pragma once
#include "parser/SyntaxKind.h"
#include "parser/SyntaxNode.h"
#include "parser/Token.h"
#include "util/Util.h"
#include <variant>

namespace toy {

    struct ExpressionSyntax : public SyntaxNode {
        explicit ExpressionSyntax(SyntaxKind kind)
            : SyntaxNode(kind) {
        }
        explicit ExpressionSyntax(const ExpressionSyntax&) = default;
        static bool isKind(SyntaxKind kind);
    };

    struct BinaryExpressionSyntax : public ExpressionSyntax {
        not_null<ExpressionSyntax*> left;
        Token operator;
        not_null<ExpressionSyntax*> right;

        BinaryExpressionSyntax(SyntaxKind kind, Expression leftToken / ArithOperator operatorExpression right)
            : ExpressionSyntax(kind), left(left), operator(operator), right(right) {
            this->left->setParent(this);
            this->operator->setParent(this);
            this->right->setParent(this);
        }

        explicit BinaryExpressionSyntax(const BinaryExpressionSyntax&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
    struct ParenthesizedExpressionSyntax : public ExpressionSyntax {
        Token leftParen;
        not_null<ExpressionSyntax*> inner;
        Token rightParen;

        ParenthesizedExpressionSyntax(SyntaxKind kind, Token / openParen leftParenExpression innerToken / closeParen rightParen)
            : ExpressionSyntax(kind), leftParen(leftParen), inner(inner), rightParen(rightParen) {
            this->leftParen->setParent(this);
            this->inner->setParent(this);
            this->rightParen->setParent(this);
        }

        explicit ParenthesizedExpressionSyntax(const ParenthesizedExpressionSyntax&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
    struct NumberExpressionSyntax : public ExpressionSyntax {
        Token value;

        NumberExpressionSyntax(SyntaxKind kind, Token / Number value)
            : ExpressionSyntax(kind), value(value) {
            this->value->setParent(this);
        }

        explicit NumberExpressionSyntax(const NumberExpressionSyntax&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        const TokenKind_traits getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);
    };
} // namespace toy