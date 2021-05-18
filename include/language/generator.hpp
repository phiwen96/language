#pragma once


#include <experimental/coroutine>
#include <memory>
using namespace std;
using namespace experimental;


struct generator
{
    struct promise_type
    {
        int m_value;
        auto get_return_object ()
        {
            return generator {coroutine_handle <promise_type>::from_promise (*this)};
        }
        auto return_void ()
        {
            
        }
        auto initial_suspend ()
        {
            return suspend_always {};
        }
        auto final_suspend () noexcept
        {
            return suspend_always {};
        }
        void unhandled_exception ()
        {
            throw;
        }
        auto yield_value (int v)
        {
            m_value = v;
            return suspend_always {};
        }
        
    };
    
    coroutine_handle <promise_type> m_handle;
    
    generator (generator&& other) : m_handle {exchange (other.m_handle, {})}
    {
        
    }
    generator (coroutine_handle <promise_type> handle) : m_handle {handle}
    {
        
    }
    
    
    auto begin ()
    {
        cout << "gen::iter::begin ()" << endl;
        return _iterator {m_handle};
    }
    
    auto end ()
    {
        return _sentinel {};
    }
    
    struct _sentinel {};
    struct _iterator
    {
        using iterator_category = input_iterator_tag;
        using value_type = int;
        using difference_type = ptrdiff_t;
        using pointer = int*;
        using reference = int&;
        
        coroutine_handle <promise_type> m_handle;
        
        _iterator& operator++ ()
        {
            m_handle.resume();
            return *this;
        }
        void operator++(int)
        {
            (void)operator++();
        }
        int operator* () const
        {
            return m_handle.promise().m_value;
        }
        int* operator-> () const
        {
            return addressof (m_handle.promise().m_value);
        }
        bool operator == (_sentinel)
        {
            return m_handle.done();
        }
    };
};
