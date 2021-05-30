#pragma once



template <bool scoped = true>
struct timer
{
    using clock = std::chrono::steady_clock;

    timer () noexcept : m_start {clock::now ()}, m_name {""}
    {
        
    }
    
    timer (char const* name) noexcept : m_start {clock::now ()}, m_name {name}
    {
        
    }
    
    ~timer () noexcept
    {
        if constexpr (scoped)
        {
            std::cout << stop <std::chrono::milliseconds> () << "ms " << m_name << std::endl;
        }
    }
    

    
private:
    template <typename T>
    auto stop () const noexcept -> decltype (auto)
    {
        auto stop = clock::now ();
        auto duration = (stop - m_start);
        auto ms = duration_cast <std::chrono::milliseconds> (duration).count ();
        return ms;
    }
    
    char const* m_name;
    clock::time_point m_start;
};
