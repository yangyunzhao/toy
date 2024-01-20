#include <array>
#include <ostream>

enum class TokenKind {
    Integer,
    Plus,
    Minus,
    Multiply,
    Divide,
    EndOfFile,
};

std::ostream& operator<<(std::ostream& os, TokenKind kind);
std::string_view toString(TokenKind kind);

class TokenKind_traits {
public: static const std::array<TokenKind, 6> values;
};

/**
 *	std::ostream& operator<<(std::ostream& os, TokenKind kind); ����һ�����ص�����������������������ֱ�ӽ�TokenKindö��ֵ�����std::ostream������std::cout��
 *	std::string_view toString(TokenKind kind); ���������TokenKindö��ֵת��Ϊ�ַ�����ʾ�����ڴ�ӡ������Ϣ�������Ϣʱ�ǳ����á�
 *	class TokenKind_traits ��������һ����̬���飬�����Ԫ�������е�TokenKindö��ֵ��������Ҫ��������TokenKindֵ������·ǳ����á�
 */