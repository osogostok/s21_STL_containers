#ifndef S21_CONTAINERS_SET_S21_SET_H_
#define S21_CONTAINERS_SET_S21_SET_H_
#include "../tree/s21_tree.h"

namespace s21 {
template <class Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using size_type = std::size_t;
  using const_reference = const value_type &;

  struct CompareLess {
    bool operator()(const_reference key1, const_reference key2) const {
      return (key1 < key2);
    }
  };

  using tree_type = s21::RBTree<value_type, CompareLess>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

 public:
  set() : RBTree(new tree_type{}){};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : RBTree(new tree_type(*other.RBTree)){};
  set(set &&other) : RBTree(new tree_type(std::move(*other.RBTree))){};
  set &operator=(const set &other);
  set &operator=(set &&other);
  ~set() { delete RBTree; };

  iterator end() noexcept;
  const_iterator end() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;

  bool empty() const noexcept;

  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);

  void erase(iterator pos);

  void swap(set &other);

  void merge(set &other);

  bool contains(const key_type &key) const;

  iterator find(const key_type &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  tree_type *RBTree;
};
}  // namespace s21
#include "s21_set.tcc"
#endif  // S21_CONTAINERS_SET_S21_SET_H_
