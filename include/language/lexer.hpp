#pragma once
#include "task.hpp"
#include "token.hpp"
#include "promise.hpp"
#include <experimental/coroutine>
using namespace std;
using namespace experimental;





using lexemes = vector <token>;


struct push
{
    
};

struct __get_char {};
struct __get_value {};

struct init {string const& str;};

constexpr __get_char get_char {};
constexpr __get_value get_value {};

struct lexer
{
    struct promise_type
    {
        inline static lexemes m_lexemes;
        token m_current_token;
        coroutine_handle <promise_type> m_parent;
        coroutine_handle <promise_type> m_child;
        
        char m_c;
        string m_value;
        
        
        auto process (char c) -> void {
            
            if (m_child)
            {
                m_child.promise().process(c);

            } else
            {
                if (auto me = coroutine_handle<promise_type>::from_promise(*this);
                    not me.done())
                {
                    m_c = c;
//                    cout << "process2" << endl;
                    me.resume();

                } else
                {
                    string s = " already done";
                    throw runtime_error (s);
                }
            }
        }
        auto set_child (coroutine_handle <promise_type> child) -> void {
            m_child = child;
        }
        auto set_parent (coroutine_handle <promise_type> parent) -> void {
            m_parent = parent;
        }
        auto get_return_object () {
            return lexer {coroutine_handle <promise_type>::from_promise (*this)};
        }
        auto initial_suspend () {
//            cout << "initial suspend" << endl;
            return suspend_never {};
//            return suspend_always {};
        }
        auto final_suspend () noexcept {
            struct awaiter
            {
                auto await_ready () noexcept {
                    return false;
                }
                auto await_suspend (coroutine_handle <promise_type> c) noexcept -> coroutine_handle<>
                {
                    if (auto coro = c.promise().m_parent; coro)
                    {
                        coro.promise().set_child({});
                        return coro;
                        
                    } else
                    {
                        return noop_coroutine();
                    }
                }
                auto await_resume () noexcept {

                }
            };
            return awaiter {};
        }
        auto unhandled_exception () {
            terminate ();
        }
        auto return_void () {
            
        }
        auto await_transform (__get_char const& g) {
            struct awaiter
            {
                promise_type& p;
  
                auto await_ready () -> bool
                {
                    
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
                    return true;
                }
                
                auto await_resume () -> char
                {
                    return p.m_c;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
        auto await_transform (__get_value const& g) {
            struct awaiter
            {
                promise_type& p;
  
                auto await_ready () -> bool
                {
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
                    return true;
                }
                
                auto await_resume () -> string&
                {
                    return p.m_value;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
        auto yield_value (token t)
        {
            m_lexemes.push_back (t);
            return suspend_never {};
        };
        
        auto yield_value (char c)
        {
            m_c = c;
            return suspend_never {};
        };
    };
    

    coroutine_handle <promise_type> m_handle;
    
    lexer () = delete;
    lexer (lexer const&) = delete;
    lexer (lexer&& o) : m_handle {exchange (o.m_handle, {})} {}
    explicit lexer (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~lexer () {
        if (m_handle)
            m_handle.destroy();
    }
    
    
    auto process (char c) {
//        cout << "process" << endl;
        m_handle.promise().process (c);
    }
    
    auto done () {
        return m_handle.done();
    }
    auto lexemes () -> auto&
    {
        return m_handle.promise().m_lexemes;
    }
    auto finish ()
    {
        m_handle.promise().process ('\0');
    }
  
    
    
};





inline auto lex () -> lexer
{
    
//    cout << "########" << endl << "LEXING" << endl << "########" << endl;
    string& value = co_await get_value;
    
    char c = co_await get_char;
    
    cout << c << endl;
//    cout << c << endl;
    
    
    start:
    {
        cout << "start " << c << endl;
        if (c == '-')
        {
//            value.push_back ('-');
            co_yield token {.m_type = token::type::subtraction};
//            goto minus;
            
        } else if (c == '+')
        {
//            cout << "ADD" << endl;
            co_yield token {.m_type = token::type::addition};
            
        } else if (c == '(')
        {
            co_yield token {.m_type = token::type::left_paranthesis};
            
        } else if (c == ')')
        {
            co_yield token {.m_type = token::type::right_paranthesis};
            
        } else if (c == '/')
        {
            co_yield token {.m_type = token::type::division};
            
        } else if (c == '*')
        {
            co_yield token {.m_type = token::type::multiplication};
            
        } else if (c == ' ')
        {
            co_yield token {.m_type = token::type::space};
            
        } else if (c == '.')
        {
            co_yield token {.m_type = token::type::dot};
            
        } else if (c == ',')
        {
            co_yield token {.m_type = token::type::comma};
            
        } else if (c == ';')
        {
            co_yield token {.m_type = token::type::semicolon};
            
        } else if (c == ':')
        {
            co_yield token {.m_type = token::type::colon};
            
        } else if (c == '*')
        {
            co_yield token {.m_type = token::type::colon};
            
        } else if (c == '\n')
        {
            co_yield token {.m_type = token::type::newline};
            
        } else if (c == '\t')
        {
            co_yield token {.m_type = token::type::tab};
            
        } else if (c >= '0' and c <= '9')
        {
            value += c;
            goto number;
            
        } else if ((c > 'a' and c < 'z') or (c > 'A' and c < 'Z') or (c == '_'))
        {
            goto identifier;
            
        } else if (c > 'a' and c < 'z')
        {
//            cout << "whaaat" << endl;
        } else if (c == '\0') {
//            cout << "finish!" << endl;
            goto finish;
        } else
        {
            co_yield token {.m_type = token::type::unknown};
        }
        
        c = co_await get_char;
        
        goto start;
    }
    
    
    
    
    number:
    {
//        cout << "number " << c << endl;

        c = co_await get_char;
        
        if (c < '0' || c > '9')
        {
            co_yield token {.m_type = token::type::number, .m_str = value};
            value.clear ();
            
            goto start;
            
        } else
        {
            value += c;
            goto number;
        }
    }
    
    minus:
    {
//        cout << "minus" << endl;

        c = co_await get_char;
        
        if (c >= '0' and c <= '9')
        {
            value += '-';
            value += c;
            
            goto number;
            
        } else
        {
            co_yield token {.m_type = token::type::subtraction};
            goto start;
        }
        
    }
    
    identifier:
    {
        
    }
    
    finish:
    
    
    
    co_return;
}








inline auto tokenize (string const& input) -> lexemes
{
    auto l = lex();
    l.process(input[0]);
//    l.process(input[1]);
//    l.process(input[2]);
//    for (auto c : input)
//    {
//        l.process(c);
//    }
//    l.finish();
    return l.lexemes();
}



