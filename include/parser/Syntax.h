#pragma once
#include "parser/SyntaxKind.h"
#include "parser/SyntaxNode.h"

namespace toy{
    struct ExpressionSyntax : public SyntaxNode {

        ExpressionSyntax(SyntaxKind kind) :
            SyntaxNode(kind) {
        }

        explicit ExpressionSyntax(const ExpressionSyntax&) = default;

        static bool isKind(SyntaxKind kind);
    };

    struct BinaryExpressionSyntax : public ExpressionSyntax {
        std::shared_ptr<ExpressionSyntax*> left;
        Token operatorToken;
        std::shared_ptr<ExpressionSyntax*> right;

        BinaryExpressionSyntax(SyntaxKind kind, ExpressionSyntax& left, Token operatorToken, const SyntaxList<AttributeInstanceSyntax>& attributes, ExpressionSyntax& right) :
            ExpressionSyntax(kind), left(&left), operatorToken(operatorToken), attributes(attributes), right(&right) {
            this->left->parent = this;
            this->attributes.parent = this;
            for (auto child : this->attributes)
                child->parent = this;
            this->right->parent = this;
        }

        explicit BinaryExpressionSyntax(const BinaryExpressionSyntax&) = default;

        static bool isKind(SyntaxKind kind);

        TokenOrSyntax getChild(size_t index);
        ConstTokenOrSyntax getChild(size_t index) const;
        void setChild(size_t index, TokenOrSyntax child);

    };
}
