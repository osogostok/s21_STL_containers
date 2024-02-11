#include "s21_map.h"

namespace s21 {
template <class key_type, class mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const& items)
    : map() {
  for (auto i : items) {
    insert(i);
  }
}

template <class key_type, class mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(
    map<key_type, mapped_type>&& other) {
  if (this != &other) {
    *RBTree = std::move(*other.RBTree);
  }
  return *this;
}

template <class key_type, class mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(
    const map<key_type, mapped_type>& other) {
  if (this != &other) {
    clear();
    for (auto i = other.begin(); i != other.end(); ++i)
      RBTree->Insert(i.ptr_node_->key);
  }
  return *this;
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::at(const key_type& key) {
  value_type search(key, mapped_type{});
  iterator it = RBTree->TreeSearch(search);
  if (it == end()) throw std::out_of_range("s21::map::at");
  return (*it).second;
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::mapped_type&
map<key_type, mapped_type>::operator[](const key_type& key) {
  value_type search(key, mapped_type{});
  iterator it = RBTree->TreeSearch(search);
  if (it == end()) {
    auto it_iterator = RBTree->Insert(search);
    it = it_iterator.first;
  }
  return (*it).second;
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() noexcept {
  return RBTree->TreeEnd();
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::end() const noexcept {
  return RBTree->TreeConstEnd();
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() noexcept {
  return RBTree->TreeBegin();
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::const_iterator
map<key_type, mapped_type>::begin() const noexcept {
  return RBTree->TreeConstBegin();
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  return insert(std::pair<key_type, mapped_type>(key, obj));
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
  std::pair<iterator, bool> res = RBTree->Insert(value);
  return res;
}

template <class key_type, class mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  value_type search(key, mapped_type{});
  iterator res = RBTree->TreeSearch(search);
  std::pair<iterator, bool> pair_iter{res, false};
  if (res == end()) {
    pair_iter = RBTree->Insert({key, obj});
  } else {
    (*res).second = obj;
  }
  return pair_iter;
}

template <class key_type, class mapped_type>
bool map<key_type, mapped_type>::empty() const noexcept {
  return RBTree->TreeEmpty();
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::clear() {
  RBTree->TreeClear();
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() const noexcept {
  return RBTree->TreeSize();
}

template <class key_type, class mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() const noexcept {
  return RBTree->TreeMaxSize();
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  try {
    RBTree->TreeErase(pos);
  } catch (...) {
    throw std::runtime_error("s21::map::erase");
  }
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  RBTree->TreeSwap(*other.RBTree);
}

template <class key_type, class mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  RBTree->TreeMergeUniq(*other.RBTree);
}

template <class key_type, class mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) const {
  value_type search(key, mapped_type{});
  const_iterator it = RBTree->TreeConstSearch(search);
  if (it == end()) return false;
  return true;
}

template <class key_type, class mapped_type>
template <typename... Args>
std::vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  for (auto i : {std::forward<Args>(args)...}) {
    std::pair<iterator, bool> res = insert(i);
    result.push_back(res);
  }
  return result;
}
};  // namespace s21
