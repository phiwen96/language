#pragma once
#include "token.hpp"
#include <experimental/coroutine>
using namespace std;
using namespace experimental;

struct __get_token {};
//struct __get_value {};

constexpr __get_token get_token {};
//constexpr __get_value get_value {};

struct parser
{
    struct promise_type
    {
        inline static vector <token> m_lexemes;
        token m_current_token;
        coroutine_handle <promise_type> m_parent;
        coroutine_handle <promise_type> m_child;
        
        token m_token;
        
        
        auto process (token const& t) -> void {
            
            if (m_child)
            {
                m_child.promise().process(t);

            } else
            {
                if (auto me = coroutine_handle<promise_type>::from_promise(*this);
                    not me.done())
                {
                    m_token = t;
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
            return parser {coroutine_handle <promise_type>::from_promise (*this)};
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
        
        auto await_transform (parser t) {
            
            set_child(t.m_handle);
            t.m_handle.promise().set_parent(coroutine_handle<promise_type>::from_promise(*this));

            
            struct awaiter
            {
                coroutine_handle <promise_type> m_promise;
                
                auto await_ready () {
//                    cout << "await_ready" << endl;
                    return m_promise.done();
                }
                auto await_suspend (coroutine_handle <promise_type> awaiting_coro)
                {
//                    cout << "await_suspend" << endl;
                    return m_promise;
                }
                auto await_resume () {
//                    cout << "await_resumeee" << endl;
                }
            };
            return awaiter {t.m_handle};
        }
        auto await_transform (__get_token const& g) {
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

                auto await_resume () -> token&
                {
                    return p.m_token;
                }
            };
//            cout << "await_transform (get_char g)" << endl;
            return awaiter {*this};
        }
//        auto await_transform (__get_value const& g) {
//            struct awaiter
//            {
//                promise_type& p;
//
//                auto await_ready () -> bool
//                {
//                    return false;
//                }
//
//                auto await_suspend (coroutine_handle<> c) -> auto
//                {
//                    return true;
//                }
//
//                auto await_resume () -> string&
//                {
//                    return p.m_value;
//                }
//            };
////            cout << "await_transform (get_char g)" << endl;
//            return awaiter {*this};
//        }
        auto yield_value (token t)
        {
            m_lexemes.push_back (t);
            return suspend_never {};
        };
    
    };
    

    coroutine_handle <promise_type> m_handle;
    
    parser () = delete;
    parser (parser const&) = delete;
    parser (parser&& o) : m_handle {exchange (o.m_handle, {})} {}
    explicit parser (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~parser () {
        if (m_handle)
            m_handle.destroy();
    }
    
    
    auto process (token const& c) {
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
//        m_handle.promise().process ('\0');
    }
    
};


inline auto factor () -> parser
{
    start:
    {
        token& tok = co_await get_token;
        
        switch (tok.t)
        {
            case token::type::TOKEN_NUMBER:
//                co_yield {token::type::factor, tok.m_str};
                
            case token::type::TOKEN_MINUS:
                goto got_minus;
                
            default:
                throw runtime_error ("");
        }
        
        goto start;
    }
    
    
    got_minus:
    {
        token& tok = co_await get_token;
        
        switch (tok.t)
        {
            case token::type::TOKEN_NUMBER:
//                co_yield {token::type::factor, string ("-") + tok.m_str};
                
            case token::type::TOKEN_LEFT_PAREN:
                goto got_minus_leftparan;
                
            default:
                throw runtime_error ("");
        }
        
        goto start;
    }
    
    got_minus_leftparan:
    {
        token& tok = co_await get_token;
        
        switch (tok.t)
        {
//            case token::type::expression:
//                goto got_minus_leftparan_expression;
                
            default:
                throw runtime_error ("");
        }
        
        goto start;
    }
    
    got_minus_leftparan_expression:
    {
        token& tok = co_await get_token;
        
        switch (tok.t)
        {
            case token::type::TOKEN_RIGHT_PAREN:
                break;
//                co_yield {token::type::factor, string ("-")};
                
            default:
                throw runtime_error ("");
        }
        
        goto start;
    }
    
    co_return;
}

inline auto term () -> parser
{
//    cout << "hej" << endl;
    start:
    {
        cout << "yo" << endl;
        token& tok = co_await get_token;
        
        cout << tok << endl;
        
        switch (tok.t)
        {
//            case token::type::term:
//                goto await_mult_or_div;
//                break;
                
//            case token::type::factor:
//                co_yield {token::type::term};
//                break;
                
            default:
//                co_await factor ();
                break;
        }
        
        goto start;
    }
    
    await_mult_or_div:
    {
        token& tok = co_await get_token;
        
        switch (tok.t)
        {
//            case token::type::term:
                goto await_mult_or_div;
                
//            case token::type::factor:
                break;
                
            default:
                co_await term ();
        }
        
        goto start;
    }
    
    co_return;
}

inline auto expression () -> parser
{
    token tok = co_await get_token;

    start:
    {
        switch (tok.m_type)
        {
            case token::type::term:
                co_yield {token::type::expression};
                tok = co_await get_token;
                
            case token::type::expression:
                goto await_plus_or_minus;
                
            default:
//                cout << tok << endl;
                co_await term ();
                break;
        }
        
        goto start;
    }
    
    await_plus_or_minus:
    {
        token& tok = co_await get_token;
        
        switch (tok.m_type)
        {
            case token::type::addition:
                break;
                
            case token::type::subtraction:
                break;
                
            default:
                throw runtime_error ("ooops");
                break;
        }
    }
    
    
    co_return;
}


inline auto parse () -> parser
{
//    cout << "########" << endl << "PARSING" << endl << "########" << endl;

    start:
//    token t = co_await get_token;
//    cout << t << endl;
//    goto start;
    co_await expression ();
    
    co_return;
}
