
#include "s21_multiset.h"

namespace s21 {
template <class key_type>
multiset<key_type>::multiset(std::initializer_list<key_type> const& items)
    : multiset() {
  for (auto i : items) insert(i);
}

template <class key_type>
multiset<key_type>& multiset<key_type>::operator=(multiset<key_type>&& other) {
  if (this != &other) {
    *RBTree = std::move(*other.RBTree);
  }
  return *this;
}

template <class key_type>
multiset<key_type>& multiset<key_type>::operator=(
    const multiset<key_type>& other) {
  if (this != &other) {
    clear();
    for (auto i = other.begin(); i != other.end(); ++i)
      RBTree->Insert(i.ptr_node_->key);
  }
  return *this;
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::end() noexcept {
  return RBTree->TreeEnd();
}

template <class key_type>
typename multiset<key_type>::const_iterator multiset<key_type>::end()
    const noexcept {
  return RBTree->TreeConstEnd();
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::begin() noexcept {
  return RBTree->TreeBegin();
}

template <class key_type>
typename multiset<key_type>::const_iterator multiset<key_type>::begin()
    const noexcept {
  return RBTree->TreeConstBegin();
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::insert(
    const value_type& value) {
  RBTree->NotUniq();
  std::pair<iterator, bool> res = RBTree->Insert(value);
  return (res.first);
}

template <class key_type>
bool multiset<key_type>::empty() const noexcept {
  return RBTree->TreeEmpty();
}

template <class key_type>
void multiset<key_type>::clear() {
  RBTree->TreeClear();
}

template <class key_type>
typename multiset<key_type>::size_type multiset<key_type>::size()
    const noexcept {
  return RBTree->TreeSize();
}

template <class key_type>
typename multiset<key_type>::size_type multiset<key_type>::max_size()
    const noexcept {
  return RBTree->TreeMaxSize();
}

template <class key_type>
void multiset<key_type>::erase(iterator pos) {
  try {
    RBTree->TreeErase(pos);
  } catch (...) {
    throw std::runtime_error("s21::multiset::erase");
  }
}

template <class key_type>
void multiset<key_type>::swap(multiset& other) {
  RBTree->TreeSwap(*other.RBTree);
}

template <class key_type>
void multiset<key_type>::merge(multiset& other) {
  RBTree->NotUniq();
  RBTree->TreeMerge(*other.RBTree);
}

template <class key_type>
typename multiset<key_type>::size_type multiset<key_type>::count(
    const key_type& key) {
  iterator low_it = lower_bound(key);
  iterator up_it = upper_bound(key);
  size_type count = 0;
  while (low_it != up_it) {
    ++count;
    ++low_it;
  }
  return count;
}

template <class key_type>
bool multiset<key_type>::contains(const key_type& key) const {
  const_iterator it = RBTree->TreeConstSearch(key);
  if (it == end()) return false;
  return true;
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::find(
    const key_type& key) {
  return RBTree->TreeSearch(key);
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::lower_bound(
    const key_type& key) {
  return RBTree->TreeLowerBound(key);
}

template <class key_type>
typename multiset<key_type>::iterator multiset<key_type>::upper_bound(
    const key_type& key) {
  return RBTree->TreeUpperBound(key);
}

template <class key_type>
std::pair<typename multiset<key_type>::iterator,
          typename multiset<key_type>::iterator>
multiset<key_type>::equal_range(const key_type& key) {
  return std::pair<iterator, iterator>((lower_bound(key)), (upper_bound(key)));
}

template <class key_type>
template <typename... Args>
std::vector<std::pair<typename multiset<key_type>::iterator, bool>>
multiset<key_type>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  for (auto i : {std::forward<Args>(args)...}) {
    iterator res = insert(i);
    result.push_back(std::make_pair(res, true));
  }
  return result;
}

};  // namespace s21
