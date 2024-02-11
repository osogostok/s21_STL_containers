#ifndef S21_SET_TPP_
#define S21_SET_TPP_
#include "s21_set.h"

namespace s21 {
template <class key_type>
set<key_type>::set(std::initializer_list<key_type> const& items) : set() {
  for (auto i : items) {
    insert(i);
  }
}

template <class key_type>
set<key_type>& set<key_type>::operator=(set<key_type>&& other) {
  if (this != &other) {
    *RBTree = std::move(*other.RBTree);
  }
  return *this;
}

template <class key_type>
set<key_type>& set<key_type>::operator=(const set<key_type>& other) {
  if (this != &other) {
    clear();
    for (auto i = other.begin(); i != other.end(); ++i)
      RBTree->Insert(i.ptr_node_->key);
  }
  return *this;
}

template <class key_type>
typename set<key_type>::iterator set<key_type>::end() noexcept {
  return RBTree->TreeEnd();
}

template <class key_type>
typename set<key_type>::const_iterator set<key_type>::end() const noexcept {
  return RBTree->TreeConstEnd();
}

template <class key_type>
typename set<key_type>::iterator set<key_type>::begin() noexcept {
  return RBTree->TreeBegin();
}

template <class key_type>
typename set<key_type>::const_iterator set<key_type>::begin() const noexcept {
  return RBTree->TreeConstBegin();
}

template <class key_type>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
    const value_type& value) {
  std::pair<iterator, bool> res = RBTree->Insert(value);
  return res;
}

template <class key_type>
bool set<key_type>::empty() const noexcept {
  return RBTree->TreeEmpty();
}

template <class key_type>
void set<key_type>::clear() {
  RBTree->TreeClear();
}

template <class key_type>
typename set<key_type>::size_type set<key_type>::size() const noexcept {
  return RBTree->TreeSize();
}

template <class key_type>
typename set<key_type>::size_type set<key_type>::max_size() const noexcept {
  return RBTree->TreeMaxSize();
}

template <class key_type>
void set<key_type>::erase(iterator pos) {
  try {
    RBTree->TreeErase(pos);
  } catch (...) {
    throw std::runtime_error("s21::set::erase");
  }
}

template <class key_type>
void set<key_type>::swap(set& other) {
  RBTree->TreeSwap(*other.RBTree);
}

template <class key_type>
void set<key_type>::merge(set& other) {
  RBTree->TreeMergeUniq(*other.RBTree);
}

template <class key_type>
bool set<key_type>::contains(const key_type& key) const {
  const_iterator it = RBTree->TreeConstSearch(key);
  if (it == end()) return false;
  return true;
}

template <class key_type>
typename set<key_type>::iterator set<key_type>::find(const key_type& key) {
  return RBTree->TreeSearch(key);
}

template <class key_type>
template <typename... Args>
std::vector<std::pair<typename set<key_type>::iterator, bool>>
set<key_type>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  for (auto i : {std::forward<Args>(args)...}) {
    std::pair<iterator, bool> res = insert(i);
    result.push_back(res);
  }
  return result;
}
};      // namespace s21
#endif  // CS21_SET_TPP_
