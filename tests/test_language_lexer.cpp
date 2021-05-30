#include <catch2/catch.hpp>
#include <language/language.hpp>
#include <language/task.hpp>
#include <language/promise.hpp>
#include <language/lexer.hpp>
#include <language/uni.hpp>
#include <language/token.hpp>
#include <experimental/coroutine>
<<<<<<< HEAD
=======
#include <language/generator.hpp>
>>>>>>> 20a80ece91aa4e4bb4e26790834faec9d802a06b
using namespace std;
using namespace std::experimental;



TEST_CASE ("Let lexer generate a token sequence from input string")
{
    GIVEN ("input string: -7+11+2+3-40")
    {
        
        THEN ("output vector <token> should be <minus> <number> <plus>...")
        {
            
<<<<<<< HEAD
        }
    }
}
=======
            vector <token> l = tokenize ("-7+11+2+3-40");
//            vector <token::type> program {}
            for (auto i : l)
            {
                cout << i << endl;
                if (i.m_str.size() > 0)
                {
                    cout << i.m_str << endl;
                }
            }
            
        }
    }
}

>>>>>>> 20a80ece91aa4e4bb4e26790834faec9d802a06b
