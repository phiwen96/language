#pragma once

using namespace std;


struct token
{
    enum struct type
    {
        left_paranthesis,
        right_paranthesis,
        addition,
        subtraction,
        multiplication,
        division,
        number,
        variable,
        left_curly_bracket,
        right_curly_bracket,
        left_bracket,
        right_bracket,
        unknown
    };
    
    type m_type;
    string m_str;
};




inline ostream& operator<< (ostream& os, token const& t)
{
    if (t.m_type == token::type::subtraction)
    {
        os << "<->";
        
    } else if (t.m_type == token::type::addition)
    {
        os << "<+>";
        
    } else if (t.m_type == token::type::left_paranthesis)
    {
        os << "<(>";
        
    } else if (t.m_type == token::type::right_paranthesis)
    {
        os << "<)>";
        
    } else if (t.m_type == token::type::division)
    {
        os << "</>";
        
    } else if (t.m_type == token::type::multiplication)
    {
        os << "<*>";
        
    } else if (t.m_type == token::type::number)
    {
        os << "<" << t.m_str << ">";
        
    } else if (t.m_type == token::type::variable)
    {
        os << "<" << t.m_str << ">";
        
    } else if (t.m_type == token::type::left_curly_bracket)
    {
        os << "<{>";
        
    } else if (t.m_type == token::type::right_curly_bracket)
    {
        os << "<}>";
        
    } else if (t.m_type == token::type::left_bracket)
    {
        os << "<[>";
        
    } else if (t.m_type == token::type::right_bracket)
    {
        os << "<]>";
        
    } else if (t.m_type == token::type::unknown)
    {
        os << "<unknown>";
    }
    
    return os;
}
