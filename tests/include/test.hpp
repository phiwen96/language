#pragma once
#include <catch2/catch.hpp>
#include <language/language.hpp>
#include <language/task.hpp>
#include <language/promise.hpp>
#include <language/lexer.hpp>
#include <language/uni.hpp>
#include <language/token.hpp>
#include <experimental/coroutine>
using namespace std;
using namespace std::experimental;
//#include <latch>
//#include <barrier>




auto run () -> int;

