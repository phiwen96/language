#pragma once

#include "array_.hpp"
#include "common.hpp"
#include "allocator.hpp"
#include "pointee.hpp"
//template <typename T>
//concept is_ok = requires (Pointee& p) {
//    typename Pointee::value_type;
//    typename Pointee::reference;
//    typename Pointee::pointer;
//};
#ifdef GROW
#undef GROW
#define GROW \
    size_t act = active(); \
    p *= growth_factor; \
    allocator::reallocate (p); \
    p.now = p.begin + act;
#endif

template <typename T>
struct array <T>
{
    cexp int growth_factor = 2;
    using pointee = pointee <T>;
    using allocator = allocator <pointee>;
    using value_type = typename pointee::value_type;
    using reference = typename pointee::reference;
    using pointer = typename pointee::pointer;
    
    array (size_t passive = 2);
    ~array ();
    
    auto push_back (value_type) -> auto&;
    auto passive () const -> size_t;
    auto active () const -> size_t;
    auto capacity () const -> size_t;
    auto begin ()   -> pointer;
    auto begin () const   -> pointer;
    auto end ()     -> pointer;
    auto end () const    -> pointer;
    
    
    auto operator[] (size_t i) -> reference;
    auto operator[] (size_t i) const -> reference;
    auto operator+= (value_type) -> auto&;
    


private:
    pointee p;
};

template <typename T>
inline std::ostream& operator<< (std::ostream& os, array<T> const& a)
{
    for (int i = 0; i < a.active(); ++i)
    {
        os << a [i] << " ";
    }
    return os;
}

template <typename T>
array <T>::array (size_t passive) : p {passive}
{
    allocator::allocate (p);
    p.now = p.begin;
}

template <typename T>
array <T>::~array ()
{
    allocator::deallocate (p);
}

template <typename T>
auto array <T>::push_back (value_type value) -> auto&
{
    if (FULL)
    {
        GROW
    }
//    ++p.now;
    
    *p.now = value;
    ++p.now;
    return *this;
}

template <typename T>
auto array <T>::passive () const -> size_t
{
    return p.passive ();
}

template <typename T>
auto array <T>::active () const -> size_t
{
    return p.active ();
}

template <typename T>
auto array <T>::capacity () const -> size_t
{
    return p.active () + p.passive ();
}

template <typename T>
auto array <T>::begin () -> pointer
{
    return p.begin;
}

template <typename T>
auto array <T>::begin () const -> pointer
{
    return p.begin;
}

template <typename T>
auto array <T>::end () -> pointer
{
    return p.now;
}

template <typename T>
auto array <T>::end () const -> pointer
{
    return p.now;
}

template <typename T>
auto array <T>::operator[] (size_t i) -> reference
{
    assert (i >= 0 and i <= active());
    return * (p.begin + i);
}

template <typename T>
auto array <T>::operator[] (size_t i) const -> reference
{
    assert (i >= 0 and i <= active());
    return * (p.begin + i);
}

template <typename T>
auto array <T>::operator+= (value_type value) -> auto&
{
    return push_back (value);
}




#include "array_static.hpp"
