#include "parser/TriviaKind.h"

namespace toy {
    std::ostream& operator<<(std::ostream& os, TriviaKind kind) {
        os << toString(kind);
        return os;
    }

    // clang-format off
    std::string_view toString(TriviaKind kind) {
        switch (kind) {
            case TriviaKind::Whitespace: return "Whitespace";
            case TriviaKind::BlockComment: return "BlockComment";
            case TriviaKind::LineComment: return "LineComment";
            default: return "";
        }
    }
    // clang-format on

    decltype(TriviaKind_traits::values) TriviaKind_traits::values = {
        TriviaKind::Whitespace,
        TriviaKind::BlockComment,
        TriviaKind::LineComment,
    };
}  // namespace toy