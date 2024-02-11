#ifndef S21_CONTAINERS_STACK_S21_STACK_H_
#define S21_CONTAINERS_STACK_S21_STACK_H_

#include <algorithm>

#include "../s21_containers.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
 private:
  using value_type = T;
  using size_type = size_t;
  using reference = T &;
  using const_reference = const T &;
  Container container;

 public:
  stack() : container() {}

  explicit stack(std::initializer_list<value_type> const &other)
      : container(other){};

  stack(const stack &other) : container(other.container){};

  stack(stack &&other) : container(std::move(other.container)){};

  ~stack() {}

  stack &operator=(const stack &other) {
    container = other.container;
    return *this;
  }

  stack &operator=(stack &&other) {
    container = std::move(other.container);
    return *this;
  }

  reference top() { return container.back(); }

  const_reference top() const { return container.back(); }

  bool empty() const { return container.empty(); }

  size_type size() const { return container.size(); }

  void push(const T &value) { container.push_back(value); }

  void push(T &&value) { container.push_back(std::move(value)); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    container.insert_many_back(std::forward<Args>(args)...);
  }

  void pop() { container.pop_back(); }

  void swap(stack &other) { std::swap(container, other.container); }
};
}  // namespace s21

#endif  //  S21_CONTAINERS_STACK_S21_STACK_H_