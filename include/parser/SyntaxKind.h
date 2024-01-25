#pragma once

#include <array>
#include <ostream>
#include <string_view>

namespace toy {
    enum class SyntaxKind {
        Unknown,
        AddExpression,
        SubtractExpression,
        MultiplyExpression,
        DivideExpression,
        ParenthesizedExpression,
        NumberExpression,
    };

    std::ostream& operator<<(std::ostream& os, SyntaxKind kind);
    std::string_view toString(SyntaxKind kind);

    class SyntaxKind_traits {
    public:
        static const std::array<SyntaxKind, 7> values;
    };

    const std::type_info* typeFromSyntaxKind(SyntaxKind kind);
} // namespace toy