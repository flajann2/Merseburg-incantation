#pragma once

#include <tuple>
#include <thread>

namespace merseberg {
  /**
   */
  template <typename Container, class... Args> class incantation {
    std::tuple<Args...> m_tuple;
    
  public:
    template <class Function>
    incantation(Function&& f, Args&&... args) {
      m_tuple = std::tuple<Args...>(args...);
    }
    
    void join() {}
    void detach() {}
  };

} // namespace merse



