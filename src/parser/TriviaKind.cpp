#include "parser/TriviaKind.h"

std::ostream& operator<<(std::ostream& os, TriviaKind kind) {
    os << toString(kind);
    return os;
}

std::string_view toString(TriviaKind kind) {
    switch (kind) {
        case TriviaKind::Whitespace: return "Whitespace";
        case TriviaKind::Comment: return "Comment";
        default: return "";
    }
}

decltype(TriviaKind_traits::values) TriviaKind_traits::values = {
    TriviaKind::Whitespace,
    TriviaKind::Comment,
};