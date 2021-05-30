#pragma once

namespace ph{


constexpr auto mid (auto&& a, auto&& b) -> decltype (auto)
{
    return (a + b) / 2;
}

constexpr auto mid (auto&& a) -> decltype (auto)
{
    return a / 2;
}

constexpr auto mid (auto&& a) -> decltype (auto)
requires requires () {
    {a.size ()};
}
{
    return a.size () / 2;
}

static_assert (mid (2, 6) == 4, "");
static_assert (mid (6) == 3, "");


}



template <typename T>
std::ostream& operator<< (std::ostream& os, std::vector <T> const& v)
{
    for (auto const& i : v)
        os << i << " ";
    return os;
}



template <typename T>
struct analyzer
{
#define ANALYZER(value) analyzer <decltype (value)> {value, __builtin_FUNCTION (), __builtin_LINE()}
    
    T t;
    char const* m_function_name;
    int const m_line;
    
    
    
    auto operator== (auto&& o) const noexcept
    {
        return t == forward <decltype (o)> (o);
    }
    auto operator!= (auto const& o) const noexcept
    {
        return t != o;
    }
    auto operator= (auto&& o) noexcept -> auto&
    {
        t = forward <decltype (o)> (o);
    }
    auto operator++ () noexcept -> auto&
    {
        std::cout << "++" << std::endl;
        ++t;
        return *this;
    }
    auto operator++ (int) noexcept -> auto&
    {
        std::cout << "++" << std::endl;
        t++;
        return *this;
    }
    auto operator-- () noexcept -> auto&
    {
        --t;
        return *this;
    }
    auto operator-- (int) noexcept -> auto&
    {
        t--;
        return *this;
    }
    auto operator< (auto const& o) const noexcept
    {
        std::cout << "<" << std::endl;

        return t < o;
    }
    auto operator> (auto const& o) const noexcept
    {
        return t > o;
    }
    friend auto operator<< (auto& os, analyzer const& a) noexcept -> auto&
    {
        return os << a.t;
    }
};

template <typename T>
analyzer (T) -> analyzer <T>;



#define _LOOP(...) __VA_ARGS__ } ();

//#define LOOP(n) []{for(auto _i_ = ANALYZER (n); _i_  < n; ++_i_) _LOOP

#define LOO(...) __VA_ARGS__

#define LOOP(n, ...) [__VA_ARGS__]{for(auto _i = 0; _i  < n; ++_i) _LOOP


#ifndef cexp
#define cexp inline static constexpr
#endif


#define FULL (active() + 1 >= passive())

//auto operator<< (std::ostream& os, auto&& value) -> std::ostream&
//requires requires (decltype (value))
//{
//    {value.begin ()};
//    {value.end ()};
//}
//{
//    return os << std::forward <decltype (value)> (value);
//}
//
//auto operator<< (std::ostream& os, auto&& value) -> std::ostream&
//{
//    return os << std::forward <decltype (value)> (value);
//}
