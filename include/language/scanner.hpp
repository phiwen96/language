#pragma once
#include <experimental/coroutine>
using namespace std::experimental;

using namespace std;

struct __get_char {};
struct __get_value {};


template <typename TokenType>
struct scanner
{
    using token_type = TokenType;
    
    struct promise_type
    {
//        inline static lexemes m_lexemes;
        token_type m_current_token;
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
            return scanner {coroutine_handle <promise_type>::from_promise (*this)};
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
        auto yield_value (token_type t)
        {
//            m_lexemes.push_back (t);
            return suspend_never {};
        };
        
        auto yield_value (char c)
        {
            m_c = c;
            return suspend_never {};
        };
    };
    

    coroutine_handle <promise_type> m_handle;
    
    scanner () = delete;
    scanner (scanner const&) = delete;
    scanner (scanner&& o) : m_handle {exchange (o.m_handle, {})} {}
    explicit scanner (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~scanner () {
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
