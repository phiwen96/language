#include <catch2/catch.hpp>
#include <language/language.hpp>
#include <language/task.hpp>
#include <language/generator.hpp>
#include <language/promise.hpp>
#include <language/lexer.hpp>
#include <language/uni.hpp>
#include <language/token.hpp>
#include <experimental/coroutine>
#include <language/generator.hpp>
using namespace std;
using namespace std::experimental;


auto seq (int n = 0) -> generator
{
    for (int i = n;; ++i)
    {
        co_yield i;
    }
}

auto raandom () -> generator
{
    for (;;)
        co_yield rand();
}

auto take_until (generator& gen, int value) -> generator
{
    for (auto&& v : gen)
    {
        if (v == value)
        {
            co_return;
        }
        co_yield v;
    }
}

auto add (generator& gen, int a) -> generator
{
    for (auto&& v : gen)
    {
        co_yield v + a;
    }
}

template <int i, int j>
struct itt
{

    struct _itt
    {
        int curr;
        
        auto operator++()
        {
            ++ curr;
            return *this;
        }
        bool operator==(_itt const& other)
        {
            return other.curr == curr;
        }
        auto operator* ()
        {
            return curr;
        }
    };
    
    auto begin ()
    {
        return _itt {i};
    }
    auto end ()
    {
        return _itt {j};
    }
    

};


TEST_CASE ("Let lexer generate a token sequence from input")
{
    GIVEN ("input string: -7+11+2+3-40")
    {
        
        THEN ("output vector <token> should be <minus> <number> <plus>...")
        {
//            itt <0, 10> _d;
//
//            for (auto i = _d.begin(); i != _d.end(); ++i)
//            {
//                cout << *i << endl;
//            }
//            return 0;
//            auto s = seq (0);
//            for (auto i = s.begin(); i != 10; ++i)
//            {
//                cout << *i << endl;
//            }
            
//            auto i = s.begin();
//            cout << *i << endl;
//            for (auto i = s.begin(); i != 10; ++i)
//            {
//                cout << *i << endl;
//            }
            
//            auto d = raandom();
//            cout << d << endl;
//
//            cout << d << endl;
            
            
//            for (auto i : s)
//                cout << i << endl;
            
            
//            auto t = take_until (s, 3);
//            auto a = add (t, 0);
//            for (auto i : a)
//                cout << i << endl;
        }
    }
}
