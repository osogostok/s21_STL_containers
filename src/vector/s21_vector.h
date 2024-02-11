#ifndef S21_CONTAINERS_VECTOR_S21_VECTOR_H_
#define S21_CONTAINERS_VECTOR_S21_VECTOR_H_

namespace s21 {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using allocator_type = std::allocator<T>;

  vector() : array_(nullptr), size_(0), capacity_(0), alloc_() {}

  vector(size_type n) {
    array_ = alloc_.allocate(n);
    try {
      std::uninitialized_fill(array_, array_ + n, value_type{});
    } catch (...) {
      alloc_.deallocate(array_, n);
      throw;
    }
    size_ = capacity_ = n;
  }

  vector(std::initializer_list<value_type> const &items) {
    array_ = alloc_.allocate(items.size());
    CopyElements(items.begin(), items.end(), items.size());
    size_ = capacity_ = items.size();
  }

  vector(const vector &v) {
    array_ = alloc_.allocate(v.size_);
    CopyElements(v.cbegin(), v.cend(), v.size());
    size_ = capacity_ = v.size_;
  }

  vector(vector &&v)
      : array_(v.array_), size_(v.size_), capacity_(v.capacity_) {
    v.array_ = nullptr;
    v.size_ = v.capacity_ = 0;
  }

  ~vector() {
    clear();
    alloc_.deallocate(array_, capacity_);
    capacity_ = 0;
  }

  vector &operator=(const vector &v) {
    v.size_ <= size_ ? clear() : reserve(v.size_);
    CopyElements(v.cbegin(), v.cend(), v.size());
    size_ = v.size_;
    return *this;
  }

  vector &operator=(vector &&v) {
    clear();
    alloc_.deallocate(array_, capacity_);
    array_ = v.array_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.array_ = nullptr;
    v.size_ = v.capacity_ = 0;

    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::invalid_argument("argument is out of range");
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }

  const_reference operator[](size_type pos) const { return array_[pos]; }

  const_reference front() const { return array_[0]; }

  const_reference back() const { return array_[size_ - 1]; }

  T *data() { return array_; }

  iterator begin() { return array_; }

  const_iterator cbegin() const { return array_; }

  iterator end() { return array_ + size_; }

  const_iterator cend() const { return array_ + size_; }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size < capacity_) return;

    ReserveCapacity(size);
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    if (size_ == capacity_) return;

    ReserveCapacity(size_);
  }

  void clear() {
    for (size_type i = 0; i < size_; ++i) {
      alloc_.destroy(array_ + i);
    }
    size_ = 0;
  }

  iterator insert(iterator pos, const_reference value) {
    return insert_many(pos, value);
  }

  void erase(iterator pos) {
    for (auto it = pos; it != end() - 1; ++it) {
      *it = *(it + 1);
    }
    alloc_.destroy(array_ + size_);
    --size_;
  }

  void push_back(const_reference value) { insert_many(end(), value); }

  void pop_back() {
    if (size_ > 0) {
      erase(end() - 1);
    }
  }

  void swap(vector &other) {
    std::swap(array_, other.array_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_type pos_diff = pos - begin(), arg_count = sizeof...(args);
    size_type newcap = GetCapacity(capacity_, arg_count);

    if (pos == end() && newcap <= capacity_) {
      InsertBack(args...);
    } else {
      InsertInArray(pos, newcap, args...);
    }

    size_ += arg_count;
    return begin() + pos_diff;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_many(end(), args...);
  }

 private:
  T *array_;
  size_type size_;
  size_type capacity_;
  allocator_type alloc_;

  void ReserveCapacity(size_type size) {
    value_type *newarr = alloc_.allocate(size);

    try {
      std::uninitialized_move(begin(), end(), newarr);
    } catch (...) {
      alloc_.deallocate(array_, size);
      throw;
    }
    for (size_type i = 0; i < size_; ++i) {
      alloc_.destroy(array_ + i);
    }
    alloc_.deallocate(array_, capacity_);

    array_ = newarr;
    capacity_ = size;
  }

  void ChangeCapacity(value_type *arr, size_type capacity) {
    alloc_.deallocate(array_, capacity_);
    array_ = arr;
    capacity_ = capacity;
  }

  size_type GetCapacity(size_type capacity, size_type arg_count = 0) {
    if (!capacity) capacity = size_ + arg_count;

    while (size_ + arg_count > capacity) capacity *= 2;
    return capacity;
  }

  template <typename... Args>
  void InsertBack(Args &&...args) {
    auto it = end();
    try {
      for (auto i : {std::forward<Args>(args)...}) {
        alloc_.construct(it, std::move(i));
        ++it;
      }
    } catch (...) {
      for (auto i = end(); i != it; ++i) alloc_.destroy(i);
      throw;
    }
  }

  template <typename... Args>
  void InsertInArray(const_iterator pos, size_type newcap, Args &&...args) {
    value_type *newarr = alloc_.allocate(newcap);

    auto it = newarr, it2 = begin();
    try {
      for (; it2 < pos; ++it, ++it2) {
        alloc_.construct(it, std::move(*it2));
      }

      for (auto i : {std::forward<Args>(args)...}) {
        alloc_.construct(it, std::move(i));
        ++it;
      }

      for (; it2 != end(); ++it, ++it2) {
        alloc_.construct(it, std::move(*it2));
      }
    } catch (...) {
      for (auto i = begin(); i != it; ++i) alloc_.destroy(i);
      throw;
    }

    ChangeCapacity(newarr, newcap);
  }

  template <typename Iterable>
  void CopyElements(Iterable begin, Iterable end, value_type size) {
    try {
      std::uninitialized_move(begin, end, array_);
    } catch (...) {
      alloc_.deallocate(array_, size);
      throw;
    }
  }
};
}  // namespace s21

#endif  //  S21_CONTAINERS_VECTOR_S21_VECTOR_H_