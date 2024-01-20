
std::ostream& operator<<(std::ostream& os, TokenKind kind) {
    os << toString(kind);
    return os;
}

std::string_view toString(TokenKind kind) {
    switch (kind) {
        case TokenKind::Integer: return "Integer";
        case TokenKind::Plus: return "Plus";
        case TokenKind::Minus: return "Minus";
        case TokenKind::Multiply: return "Multiply";
        case TokenKind::Divide: return "Divide";
        case TokenKind::EndOfFile: return "EndOfFile";
        default: return "";
    }
}

decltype(TokenKind_traits::values) TokenKind_traits::values = {
    TokenKind::Integer,
    TokenKind::Plus,
    TokenKind::Minus,
    TokenKind::Multiply,
    TokenKind::Divide,
    TokenKind::EndOfFile,
};