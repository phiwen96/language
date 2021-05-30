#pragma once


#define MAXED_OUT (m_current == m_end)
#define GROW m_size *= growth_factor; grow();


//#include "allocate.hpp"

//#include "deallocate.hpp"











template <typename...>
struct allocator;



template <typename Pointee>
struct allocator <Pointee>// : Pointee
{
    using pointee = Pointee;
    using value_type = typename pointee::value_type;
    using reference = typename pointee::reference;
    using pointer = typename pointee::pointer;
    
    /**
            1 1 1 0 0 0
            1 1 1 1 0 0
     */
    
    static auto allocate (pointee& p) -> void
    {
        assert (p.end != nullptr and p.begin != p.end);
        
        size_t size = p.end - p.begin;
        p.begin = reinterpret_cast <pointer> (std::malloc (sizeof (value_type) * size));
        p.end = p.begin + size;
    }
    
    static auto deallocate (pointee& p) -> void
    {
        std::free (p.begin);
        p.begin = nullptr;
        p.end = nullptr;
        p.now = p.begin;
    }
    
    static auto reallocate (pointee& p) -> void
    {
        size_t size = p.end - p.begin;
        p.begin = reinterpret_cast <pointer> (std::realloc (p.begin, sizeof (value_type) * size));
        p.end = p.begin + size;
    }
};
