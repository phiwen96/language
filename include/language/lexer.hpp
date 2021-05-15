#pragma once
#include "task.hpp"
#include "token.hpp"
#include "promise.hpp"
#include <experimental/coroutine>
using namespace std;
using namespace experimental;



using lexemes = vector <token>;


struct __get_char
{
    char m_c;
    
    auto await_ready () -> bool
    {
        return false;
    }
    
    auto await_suspend (coroutine_handle<>) -> void
    {
        
    }
    
    auto await_resume () -> char
    {
        return m_c;
    }
};

constexpr __get_char get_char {};

struct lexer
{
    enum class type {
        bajs
    };
    struct promise_type
    {
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
            return suspend_always {};
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
        auto await_transform (lexer t) {
            
            set_child(t.m_handle);
            t.m_handle.promise().set_parent(coroutine_handle<promise_type>::from_promise(*this));

            
            struct awaiter
            {
                coroutine_handle <promise_type> m_promise;
                
                auto await_ready () {
                    cout << "await_ready" << endl;
                    return m_promise.done();
                }
                auto await_suspend (coroutine_handle <promise_type> awaiting_coro)
                {
                    cout << "await_suspend" << endl;
                    return m_promise;
                }
                auto await_resume () {
                    cout << "await_resumeee" << endl;
                }
            };
            return awaiter {t.m_handle};
        }
        auto await_transform (suspend <true> a) {
            return forward <decltype (a)> (a);
        }
        auto await_transform (__get_char) -> __get_char {
            return {m_c};
        }
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
        m_handle.promise().process (c);
    }
    
    auto done () {
        return m_handle.done();
    }
    
    
};





inline auto lex () -> lexer
{
    for (;;)
    {
        char c = co_await get_char;
        
        
        if (c == '+')
        {
            
        }
            
        
        
        cout << c << " :O" << endl;
    }
    co_return;
}
