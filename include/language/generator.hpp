#pragma once

#include <ph_debug/debug.hpp>
#include <experimental/coroutine>
#include <memory>
using namespace std;
using namespace experimental;


struct generator
{
    struct promise_type
    {
        int m_value {0};
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
    explicit generator (coroutine_handle <promise_type> handle) : m_handle {handle}
    {
        
    }
    
    
    auto begin ()
    {
        m_handle.resume();
//        cout << "called from: " << str << line << endl;
//        debug_print_called_from(red, 0);
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
//        int* operator-> () const
//        {
//            return addressof (m_handle.promise().m_value);
//        }
        bool operator == (_sentinel)
        {
            return m_handle.done();
        }
        bool operator == (int i)
        {
            return m_handle.promise().m_value == i;
        }
    };
    
    friend ostream& operator<< (ostream& os, generator const& g)
    {
        return os << g.m_handle.promise().m_value;
    }
};
