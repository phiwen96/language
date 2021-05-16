#include "test.hpp"







auto test0 () -> task <promise_type>
{
    cout << "::test0" << endl;
    co_await suspend <true> {};
    co_await suspend <true> {};
    cout << "test0::" << endl;
    co_return;
}







auto test1 () -> task <promise_type>
{
    cout << "::test1" << endl;
    co_await test0();
    co_await suspend <true> {};
    cout << "test1::" << endl;
    co_return;
}





auto test2 () -> task <promise_type>
{
    cout << "::test2" << endl;
    co_await test1();
    cout << "test2::" << endl;
    co_return;
}







auto factor () -> task <promise_type>
{
    
    
    co_return;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


auto test_task_and_promise ()
{
    auto t = test2();
    t.resume ();
    cout << "==============" << endl;
    t.resume ();
    t.resume ();
    t.resume ();
}


//auto tt0() -> lexer
//{
//    cout << "::test0" << endl;
//    co_await suspend_always {};
////    co_await suspend_always {};
//    cout << "test0::" << endl;
//    co_return;
//}


auto test_lexer (string const& str)
{
    
//    auto t = tt0 ();
//    t.process('s');
//    t.process('a');
//    return;
    auto l = lex ();
    
    
    cout << "========" << endl;
    
    
    for (auto c : str)
    {
        l.process (c);
//        cout << "kmdskmd" << endl;
    }
    
//    cout << l.lexemes().size() << endl;
    
    for (auto i : l.lexemes())
        cout << i << endl;
    
//    l.process ('h');
//    l.process ('i');
    
}

auto run () -> int
{
    
//    test_task_and_promise();
    test_lexer ("-7+11+2+3-40");

//    test_lexer ("2+3-4/6");
    return 0;
}




