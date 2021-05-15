#pragma once
#include <experimental/coroutine>
using namespace std::experimental;
using namespace std;







template <bool>
struct suspend;

template <>
struct suspend <true>
{
    coroutine_handle<> me;
    
    auto await_ready () {
        cout << "_await_ready" << endl;
        return false;
    }
    auto await_suspend (coroutine_handle <> c) //-> coroutine_handle<>
    {
        cout << "_await_suspend" << endl;
//        me = c;
        return true;
        // Return std::noop_coroutine() to transfer execution to caller of coroutine_handle::resume ();
//        return noop_coroutine();
        
        // Return current coroutine's handle to immediately resume the current coroutine.
//        return c;
         
    }
    auto await_resume () {
        cout << "_await_resume" << endl;
//        return me;
//        me.resume();
    }
};

template <>
struct suspend <false>
{
    auto await_ready () {
        return true;
    }
    auto await_suspend (coroutine_handle<>) {
        
    }
    auto await_resume () {
        
    }
};









template <typename task>
struct promise_type
{
    coroutine_handle <promise_type> m_parent;
    coroutine_handle <promise_type> m_child;
    
    auto resume () -> void
    {
        if (m_child)
        {
            m_child.promise().resume();
            
        } else
        {
            if (auto me = coroutine_handle<promise_type>::from_promise(*this); not me.done())
            {
                me.resume();
                
            } else
            {
                string s = m_function + " already done";
                throw runtime_error (s);
            }
        }
    }
    
    auto set_child (coroutine_handle <promise_type> child) -> void
    {
        m_child = child;
    }
    
    auto set_parent (coroutine_handle <promise_type> parent) -> void
    {
        m_parent = parent;
    }
    
    
    
    coroutine_handle<> m_awaiting_coro;
    string m_function;
    promise_type (string s = __builtin_FUNCTION ()) : m_function {s} {
        
    }
    promise_type (promise_type&&) = delete;
    promise_type (promise_type const&) = delete;

    
    auto get_return_object () {
        return task {coroutine_handle <promise_type>::from_promise (*this)};
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
    auto await_transform (task t) {
        
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
};
