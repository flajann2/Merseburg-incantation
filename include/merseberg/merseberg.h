#pragma once

#include <thread>
#include <tuple>
#include <vector>

namespace merseberg {
  /**
   */
  template <class Container, class... Args>
  class incantation {
    using args_t = std::tuple<Args...>;
    using value_t = typename Container::value_type;

    // TODO: make this more flexible.
    const std::size_t m_thread_count = (std::thread::hardware_concurrency() > 0)
                                           ? std::thread::hardware_concurrency()
                                           : 4;
    args_t m_tuple;
    
    /// compliation of all results from all threads
    std::vector<value_t> m_results {};

    const Container& m_container;

    void do_something_with_values() {
      invoke_task(m_tuple, std::index_sequence_for<Args...>());
    }

    void yadda(Args... values) {}

    // The helper method.
    template <std::size_t... Is>
    void invoke_task(const args_t& tuple, std::index_sequence<Is...>) {
      yadda(std::get<Is>(tuple)...);
    }

   public:
    template <class Function>
    incantation(const Container& c, Function&& f, Args&&... args)
        : m_container(c), m_tuple(std::tuple<Args...>(args...)) {

    }

    void invoke() {}
    void join() {}
    void detach() {}
    template <class Function>
    value_t operator()(Function&& freduce) {
      return freduce(m_results); 
    }
  };

}  // namespace merseberg
