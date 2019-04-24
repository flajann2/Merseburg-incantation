#pragma once

#include <thread>
#include <tuple>

namespace merseberg {
  /**
   */
  template <typename Container, class... Args>
  class incantation {
    using args_t = std::tuple<Args...>;

    // TODO: make this more flexible.
    const std::size_t m_thread_count = (std::thread::hardware_concurrency() > 0) ? std::thread::hardware_concurrency() : 4;
    args_t m_tuple;

    void do_something_with_values() {
      invoke_task(m_tuple, std::index_sequence_for<Args...>());
    }

    void yadda(Args... values) {}

    // The helper method.
    template <std::size_t... Is>
    void invoke_task(const args_t& tuple,
                     std::index_sequence<Is...>) {
      yadda(std::get<Is>(tuple)...);
    }

   public:
    template <class Function>
    incantation(const Container&& c, Function&& f, Args&&... args) {
      m_tuple = std::tuple<Args...>(args...);
    }

    void invoke() {}
    void join() {}
    void detach() {}
  };

}  // namespace merseberg
