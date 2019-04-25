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
    std::vector<std::thread> m_threads{};

    /// compliation of all results from all threads
    std::vector<value_t> m_results{};

    const Container& m_container;

    void do_something_with_values() {
      invoke_task(m_tuple, std::index_sequence_for<Args...>());
    }

    template <class Function, class Iterator, std::size_t... Is>
    void invoke_task(Function&& f, const Iterator begin, const Iterator end,
                     std::index_sequence<Is...>) {
      auto result = f(begin, end, std::get<Is>(m_tuple)...);
      m_results.emplace_back(result); // TODO make thread safe
    }

   public:
    incantation(const Container& c, Args&&... args)
        : m_container(c), m_tuple(std::tuple<Args...>(args...)) {}

    std::size_t threads() { return m_thread_count; }

    /**
     * Run all the tasks. Start all threads running. Devide the contents of
     * container among all threads.
     */
    template <class Function>
    void invoke(Function&& f) {
      std::size_t size_bucket = m_container.size() / m_thread_count;
      std::size_t dust = m_container.size() % m_thread_count;

      auto i = m_container.begin();
      while (i < m_container.end()) {
        auto j = i + size_bucket + (dust-- > 0 ? 1 : 0);
        m_threads.emplace_back(std::thread(invoke_task, f, i, j, std::index_sequence_for<Args...>()));
        i = j;
      }
    }

    /**
     * Wait until all threads are completed.
     */
    void join() {}

    /**
     * Detach all running threads. You will not be able to join anymore.
     */
    void detach() {}

    /**
     * Reduction function / lambda passed in here.
     */
    template <class Function>
    value_t operator()(Function&& freduce) {
      return freduce(m_results);
    }
  };

}  // namespace merseberg
