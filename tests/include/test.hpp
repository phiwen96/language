#include <catch2/catch.hpp>
#include <language/language.hpp>

using namespace std;
#include <experimental/coroutine>
using namespace std::experimental;
#include <latch>
/**
 bool = types <int, char, string> | identical
 bool types <int, char, string> | distinct
 */





auto test0 () -> task
{
    cout << "::test0" << endl;
    co_await suspend <true> {};
    co_await suspend <true> {};


//    cout << "_test0" << endl;
//    co_await suspend_always {};

    cout << "test0::" << endl;
    co_return;

}


auto test1 () -> task
{
//    latch s {3};
//    s.count_down ();
//    s.try_wait();
    cout << "::test1" << endl;
    co_await test0();
//    co_await suspend <true> {};
//    co_await suspend_always {};
//    co_await suspend_always {};
    cout << "test1::" << endl;
    co_return;

}

auto test2 () -> task
{
//    latch s {3};
//    s.count_down ();
//    s.try_wait();
    cout << "::test2" << endl;
    co_await test1();
//    co_await suspend_always {};
//    co_await suspend_always {};
    cout << "test2::" << endl;
    co_return;

}



auto run () -> int 
{
    cout << "hi" << endl;
    auto t = test1();
    t.resume ();
    
    cout << "==============" << endl;
    t.resume ();
//    t.resume ();
    
    
    return 0;
}


