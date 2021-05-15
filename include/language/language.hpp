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



struct task
{
    struct promise_type
    {
        static void* operator new (size_t sz)
        {
            cout << "custom new for size " << sz << endl;
            return ::operator new (sz);
        }
        
        static void operator delete (void* ptr)
        {
            cout << "custom delete" << endl;
            ::operator delete (ptr);
        }
        
        coroutine_handle<> m_parent;
        
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
                auto await_suspend (coroutine_handle <promise_type> c) noexcept //-> coroutine_handle<>
                {
                    if (auto coro = c.promise().m_awaiting_coro; coro) {
//                        return coro;
                    }
                    else
                        return noop_coroutine();
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
//            cout << t.m_promise.m_function << endl;
//            t.m_promise.m_awaiting_coro = coroutine_handle<promise_type>::from_promise(*this);
            
            struct awaiter
            {
                coroutine_handle <promise_type> m_promise;
                
                auto await_ready () {
                    cout << "await_ready" << endl;
                    return m_promise.done();
//                    return !m_promise || m_promise.done();
                }
                auto await_suspend (coroutine_handle <promise_type> awaiting_coro)
                {
                    cout << "await_suspend" << endl;
                    cout << m_promise.promise().m_function << ":" << awaiting_coro.promise().m_function << endl;
                    m_promise.promise().m_awaiting_coro = awaiting_coro;
                    return m_promise;
//                    m_promise.resume();
                }
                auto await_resume () {
                    cout << "await_resumeee" << endl;
//                    cout << m_promise.promise().m_function << endl;
                    
//                    while (not m_promise.done()) {
//                        m_promise.resume();
//                    }
                }
            };
            return awaiter {t.m_handle};
        }
        auto await_transform (suspend <true> a) {
            return forward <decltype (a)> (a);
        }
    };
    
    coroutine_handle <promise_type> m_handle;
    
    task () = delete;
    task (task const&) = delete;
    task (task&& o) : m_handle {exchange (o.m_handle, {})} {}
    explicit task (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~task () {
        if (m_handle)
            m_handle.destroy();
//        if (auto coro = coroutine_handle<promise_type>::from_promise(m_promise); coro)
//            coro.destroy();
    }
    
    auto resume () {
        if (not m_handle.done())
            m_handle.resume();
        else
            throw runtime_error ("already done");
    }
};









