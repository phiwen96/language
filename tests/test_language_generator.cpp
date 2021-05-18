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


TEST_CASE ("Let lexer generate a token sequence from input")
{
    GIVEN ("input string: -7+11+2+3-40")
    {
        
        THEN ("output vector <token> should be <minus> <number> <plus>...")
        {
            auto s = seq(3);
            auto t = take_until (s, 3);
            auto a = add (t, 0);
            for (auto i : a)
                cout << i << endl;
        }
    }
}
