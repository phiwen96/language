#pragma once
#include <experimental/coroutine>
using namespace std::experimental;
using namespace std;





template <template <typename> typename PromiseType, template <typename...> typename... Mixins>
struct task : Mixins <task <PromiseType, Mixins...>>...
{
    using promise_type = PromiseType <task>;
    
    
    coroutine_handle <promise_type> m_handle;
    
    task () = delete;
    task (task const&) = delete;
    task (task&& o) : m_handle {exchange (o.m_handle, {})} {}
    explicit task (coroutine_handle <promise_type> handle) : m_handle {handle} {}
    ~task () {
        if (m_handle)
            m_handle.destroy();
    }
    
    auto resume () {
        m_handle.promise().resume();
    }
    auto done () {
        return m_handle.done();
    }
};










