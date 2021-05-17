#pragma once

using namespace std;

#define TOKENS \
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
    X (unknown)
    
struct token
{
    enum struct type
    {
#define X(x) x,
        TOKENS
#undef X

    };
    
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
