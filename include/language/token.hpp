#pragma once

using namespace std;

#define TOKENS \
    X (equal) \
    X (less) \
    X (greater) \
    X (left_paranthesis) \
    X (right_paranthesis) \
    X (addition) \
    X (subtraction) \
    X (multiplication) \
    X (division) \
    X (number) \
    X (variable) \
    X (left_curly_bracket) \
    X (right_curly_bracket) \
    X (left_bracket) \
    X (right_bracket) \
    X (comma) \
    X (dot) \
    X (semicolon) \
    X (space) \
    X (tab) \
    X (newline) \
    X (colon) \
    X (unknown) \
    X (factor) \
    X (term) \
    X (expression)

    
struct token
{
    enum struct type
    {
#define X(x) x,
        TOKENS
#undef X

    };
    
    auto operator== (token const& other) -> bool
    {
        return m_type == other.m_type and m_str == other.m_str;
    }
    
    auto operator== (type const& t) -> bool
    {
        return m_type == t;
    }
    
//    token (token const& other) : m_type {other.m_type}, m_str {other.m_str}
//    {
//
//    }
//
//    token (token&& other) : m_type {other.m_type}, m_str {move (other.m_str)}
//    {
//
//    }
    
    type m_type;
    string m_str;
};




inline ostream& operator<< (ostream& os, token const& t)
{
    switch (t.m_type)
    {
    #define X(x) \
    case token::type::x: \
        os << "<" << #x << ">"; \
        break;
    
    TOKENS
    #undef X
    }

    return os;
}
