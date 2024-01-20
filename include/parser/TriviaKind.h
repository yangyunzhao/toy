#pragma once
#include <array>
#include <ostream>

enum class TriviaKind {
    Whitespace,
    Comment,
};

std::ostream& operator<<(std::ostream& os, TriviaKind kind);
std::string_view toString(TriviaKind kind);

class TriviaKind_traits {
public: static const std::array<TriviaKind, 2> values;
};

/**
 *	std::ostream& operator<<(std::ostream& os, TokenKind kind); ����һ�����ص�����������������������ֱ�ӽ�TokenKindö��ֵ�����std::ostream������std::cout��
 *	std::string_view toString(TokenKind kind); ���������TokenKindö��ֵת��Ϊ�ַ�����ʾ�����ڴ�ӡ������Ϣ�������Ϣʱ�ǳ����á�
 *	class TokenKind_traits ��������һ����̬���飬�����Ԫ�������е�TokenKindö��ֵ��������Ҫ��������TokenKindֵ������·ǳ����á�
 */