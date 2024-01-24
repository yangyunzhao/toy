#pragma once

#include "parser/SyntaxKind.h"
#include "parser/Token.h"

namespace toy{
    class SyntaxNode{
    public:
        std::string toString() const;
        Token getFirstToken() const;
        Token getLastToken() const;
        const SyntaxNode* getParent() const;
        SyntaxNode* getParent();
        const SyntaxNode* childNode(size_t index) const;
        Token childToken(size_t index) const;
        size_t childCount() const;
        SyntaxKind getKind() const;

        template<typename T>
        T & as(){
            return *static_cast<T*>(this);
        }
        template<typename T>
        const T & as() const{
            return *static_cast<const T*>(this);
        }
    protected:
        SyntaxNode* parent = nullptr;
        SyntaxKind kind;
        explicit SyntaxNode(SyntaxKind kind) : kind(kind) {}
    };
}
