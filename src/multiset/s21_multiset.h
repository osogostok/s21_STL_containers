#ifndef S21_CONTAINERS_MULTISET_S21_MULTISET_H_
#define S21_CONTAINERS_MULTISET_S21_MULTISET_H_
#include "../tree/s21_tree.h"

namespace s21 {
template <class Key>
class multiset {
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
  multiset() : RBTree(new tree_type{}){};
  multiset(std::initializer_list<value_type> const &items);
  multiset(const multiset &other) : RBTree(new tree_type(*other.RBTree)){};
  multiset(multiset &&other)
      : RBTree(new tree_type(std::move(*other.RBTree))){};
  multiset &operator=(const multiset &other);
  multiset &operator=(multiset &&other);
  ~multiset() { delete RBTree; };

  iterator end() noexcept;
  const_iterator end() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;

  bool empty() const noexcept;

  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();

  iterator insert(const value_type &value);

  void erase(iterator pos);

  void swap(multiset &other);

  void merge(multiset &other);

  size_type count(const key_type &key);

  bool contains(const key_type &key) const;

  iterator find(const key_type &key);

  std::pair<iterator, iterator> equal_range(const key_type &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  tree_type *RBTree;
};
}  // namespace s21
#include "s21_multiset.tcc"
#endif  // S21_CONTAINERS_MULTISET_S21_MULTISET_H_
