#ifndef S21_CONSTAINERS_MAP_S21_MAP_H_
#define S21_CONSTAINERS_MAP_S21_MAP_H_
#include "../tree/s21_tree.h"

namespace s21 {
template <class Key, class Type>
class map {
 public:
  using key_type = Key;
  using mapped_type = Type;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  struct CompareLess {
    bool operator()(const_reference key1, const_reference key2) const {
      return (key1.first < key2.first);
    }
  };

  using tree_type = s21::RBTree<value_type, CompareLess>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;

 public:
  map() : RBTree(new tree_type{}){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : RBTree(new tree_type(*other.RBTree)){};
  map(map &&other) : RBTree(new tree_type(std::move(*other.RBTree))){};
  map &operator=(const map &other);
  map &operator=(map &&other);
  ~map() { delete RBTree; };

  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  iterator end() noexcept;
  const_iterator end() const noexcept;
  iterator begin() noexcept;
  const_iterator begin() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);

  void erase(iterator pos);

  void swap(map &other);

  void merge(map &other);

  bool contains(const key_type &key) const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  tree_type *RBTree;
};
}  // namespace s21
#include "s21_map.tcc"
#endif  // S21_CONSTAINERS_MAP_S21_MAP_H_
