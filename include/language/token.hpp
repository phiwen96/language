#pragma once

using namespace std;

#define TOKENS \
    X (TOKEN_LEFT_PAREN) \
    X (TOKEN_RIGHT_PAREN) \
    X (TOKEN_LEFT_BRACE) \
    X (TOKEN_RIGHT_BRACE) \
    X (TOKEN_COMMA) \
    X (TOKEN_DOT) \
    X (TOKEN_MINUS) \
    X (TOKEN_PLUS) \
    X (TOKEN_SEMICOLON) \
    X (TOKEN_SLASH) \
    X (TOKEN_STAR) \
    X (TOKEN_BANG) \
    X (TOKEN_BANG_EQUAL) \
    X (TOKEN_EQUAL) \
    X (TOKEN_EQUAL_EQUAL) \
    X (TOKEN_GREATER) \
    X (TOKEN_GREATER_EQUAL) \
    X (TOKEN_LESS) \
    X (TOKEN_LESS_EQUAL) \
    X (TOKEN_IDENTIFIER) \
    X (TOKEN_STRING) \
    X (TOKEN_NUMBER, double value = strtod (parser.previous.start, NULL); emitConstant(value);) \
    X (TOKEN_AND) \
    X (TOKEN_CLASS) \
    X (TOKEN_ELSE) \
    X (TOKEN_FALSE) \
    X (TOKEN_FOR) \
    X (TOKEN_FUN) \
    X (TOKEN_IF) \
    X (TOKEN_NIL) \
    X (TOKEN_OR) \
    X (TOKEN_PRINT) \
    X (TOKEN_RETURN) \
    X (TOKEN_SUPER) \
    X (TOKEN_THIS) \
    X (TOKEN_TRUE) \
    X (TOKEN_VAR) \
    X (TOKEN_WHILE) \
    X (TOKEN_ERROR) \
    X (TOKEN_EOF)

    
struct token
{
    enum type
    {
#define X(x, ...) x,
        TOKENS
#undef X

    };
    
//    auto operator== (token const& other) -> bool
//    {
//        return m_type == other.m_type and m_str == other.m_str;
//    }
//
//    auto operator== (type const& t) -> bool
//    {
//        return m_type == t;
//    }
    
//    token (token const& other) : m_type {other.m_type}, m_str {other.m_str}
//    {
//
//    }
//
//    token (token&& other) : m_type {other.m_type}, m_str {move (other.m_str)}
//    {
//
//    }
    
    type t;
    char const* start;
    int length;
    int line;
};




inline ostream& operator<< (ostream& os, token const& tok)
{
    switch (tok.t)
    {
    #define X(x, ...) \
    case token::type::x: \
        os << "<" << #x << ">"; \
        break;
    
    TOKENS
    #undef X
        default:
            break;
    }

    return os;
}
