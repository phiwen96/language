#pragma once

using namespace std;


enum struct token
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



inline ostream& operator<< (ostream& os, token const& t)
{
    if (t == token::subtraction)
    {
        os << "<->";
        
    } else if (t == token::addition)
    {
        os << "<+>";
        
    } else if (t == token::left_paranthesis)
    {
        os << "<(>";
        
    } else if (t == token::right_paranthesis)
    {
        os << "<)>";
        
    } else if (t == token::division)
    {
        os << "</>";
        
    } else if (t == token::multiplication)
    {
        os << "<*>";
        
    } else if (t == token::number)
    {
        os << "<12>";
        
    } else if (t == token::left_curly_bracket)
    {
        os << "<{>";
        
    } else if (t == token::right_curly_bracket)
    {
        os << "<}>";
        
    } else if (t == token::left_bracket)
    {
        os << "<[>";
        
    } else if (t == token::right_bracket)
    {
        os << "<]>";
        
    } else if (t == token::unknown)
    {
        os << "<unknown>";
    }
    
    return os;
}
