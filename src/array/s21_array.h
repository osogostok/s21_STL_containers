#ifndef S21_CONTAINERS_ARRAY_S21_ARRAY_H_
#define S21_CONTAINERS_ARRAY_S21_ARRAY_H_

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() {}

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > N)
      throw std::invalid_argument("too many initializer values");

    size_type i = 0;
    for (auto it = items.begin(); i < items.size(); ++i, ++it) array_[i] = *it;
    set_array_value(i, N, value_type{});
  }

  array(const array &a) { std::copy(a.cbegin(), a.cend(), array_); }

  array(array &&a) { std::move(a.cbegin(), a.cend(), array_); }

  ~array() {}

  array operator=(const array &a) {
    std::copy(a.cbegin(), a.cend(), array_);
    return *this;
  }

  array operator=(const array &&a) {
    std::move(a.cbegin(), a.cend(), array_);
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= N) throw std::invalid_argument("argument is out of range");
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }

  const_reference operator[](size_type pos) const { return array_[pos]; }

  const_reference front() const { return array_[0]; }

  const_reference back() const { return array_[N - 1]; }

  iterator data() { return array_; }

  iterator begin() { return array_; }

  const_iterator cbegin() const { return array_; }

  iterator end() { return array_ + N; }

  const_iterator cend() const { return array_ + N; }

  bool empty() const { return N == 0; }

  size_type size() const { return N; }

  size_type max_size() const { return N; }

  void swap(array &other) { std::swap(array_, other.array_); }

  void fill(const_reference value) { set_array_value(0, N, value); }

 private:
  T array_[N];

  void set_array_value(size_type start_index, size_type end_index,
                       const_reference value) {
    for (size_type i = start_index; i < end_index; ++i) array_[i] = value;
  }
};
}  // namespace s21

#endif  //  S21_CONTAINERS_ARRAY_S21_ARRAY_H_