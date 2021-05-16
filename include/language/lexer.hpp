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

struct __get_char
{

};

constexpr __get_char get_char {};

struct lexer
{
    struct promise_type
    {
        inline static lexemes m_lexemes;
        token m_current_token;
        coroutine_handle <promise_type> m_parent;
        coroutine_handle <promise_type> m_child;
        
        char m_c;
        
        
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
//                    cout << "await_ready" << endl;
                    return false;
                }
                
                auto await_suspend (coroutine_handle<> c) -> auto
                {
//                    cout << "await_suspend" << endl;
            //        return c;
                    return true;
                }
                
                auto await_resume () -> char
                {
//                    cout << "await_resume" << endl;
                    return p.m_c;
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
        
    }
    
};





inline auto lex () -> lexer
{
    char c;
    c = co_await get_char;
    
    string nr;
    nr.push_back (c);
    
    start:
    {
        if (c == '-')
        {
            co_yield token {.m_type = token::type::subtraction};
            
        } else if (c == '+')
        {
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
            
        } else if (c >= '0' || c <= '9')
        {
            goto number;
            
        } else
        {
            co_yield token {.m_type = token::type::unknown};
        }
        
        c = co_await get_char;
        
        goto start;
    }
    
    
    
    
    number:
    {
        for (;;)
        {
            c = co_await get_char;
            
            if (c < '0' || c > '9')
            {
                co_yield token {.m_type = token::type::number, .m_str = nr};
                goto start;
                
            } else
            {
                nr.push_back (c);
            }
        }
    }
    
minus:
{
    for (;;)
    {
        c = co_await get_char;
        
        if (c < '0' || c > '9')
        {
            co_yield token {.m_type = token::type::subtraction};
            goto start;
            
        } else
        {
            nr.push_back('-');
            nr.push_back (c);
            goto number;
        }
    }
}
    
    
    
    
    co_return;
}
