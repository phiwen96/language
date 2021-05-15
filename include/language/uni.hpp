#pragma once
using namespace std;




template <typename...>
union uni;




template <typename T, typename... U>
union uni <T, U...>
{
    T t;
    uni <U...> rest;
};




template <typename T>
union uni <T>
{
    T t;
};








auto test_union () -> int;
