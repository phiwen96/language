#include "test.hpp"




bool operator ==(vector <token> const& toks, vector <token::type> const& types)
{
    if (toks.size() != types.size())
        return false;
    
    for (int i = 0; i < toks.size(); ++i)
    {
        if (toks[i].m_type != types[i])
            return false;
    }
    
    return true;
}


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







//auto factor () -> task <promise_type>
//{
//
//
//    co_return;
//}





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


auto test_lexer (string const& str) -> lexemes const&
{
    auto l = lex ();
    

    
    cout << str << endl << "====================" << endl;
    
    
    for (auto c : str)
    {
        l.process (c);
    }
    
    l.finish();
    
    
    if (true)
    {
        for (auto i : l.lexemes())
        {
            
            if (i.m_str.size() > 0)
            {
                cout << i << " = " << i.m_str << endl;
            } else
            {
                cout << i << endl;
            }
        }
        cout << "====================" << endl;
    }
    
    
    return l.lexemes();
}


auto test_parser (vector <token> const& tokens)
{
    auto p = parse ();
//    p.process (tokens[0]);
//    p.process (tokens[1]);
//    p.process (tokens[2]);
//    for (auto const& token : tokens)
//    {
////        cout << token << endl;
//        p.process (token);
//    }
//    for (auto const& t : p.lexemes())
//    {
//        cout << t << endl;
//    }
    cout << "====================" << endl;
}




auto run () -> int
{
    
//    test_task_and_promise();
//    test_lexer ("hej");
//    test_lexer ("hej-7+11+2+3-40");

    
    {
        string inp = "21-3-4/6";

        lexemes const& l = test_lexer (inp);
        
        test_parser (l);
      
        
//        vector <token::type> right {
//            token::type::number,
//            token::type::number,
//            token::type::number,
//            token::type::division,
//            token::type::number
//        };
//        assert (l == right);
    }
//    dbug (3 << 4 << endl << 3)
    
    return 0;
}




