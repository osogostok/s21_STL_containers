#ifndef S21_CONTAINERS_ITERATOR_S21_ITERATOR_H_
#define S21_CONTAINERS_ITERATOR_S21_ITERATOR_H_

#include <iostream>

namespace s21 {
enum Color { BLACK, RED };

template <class T>
struct Node {
  using key_type = T;
  key_type key;
  Node *parent;
  Node *left;
  Node *right;
  bool color;

  Node() : parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

  Node(const key_type &key)
      : key(key), parent(nullptr), left(nullptr), right(nullptr), color(RED) {}

  Node(key_type &&key)
      : key(std::move(key)),
        parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(RED) {}

  ~Node() {}
};

template <class T>
class Iterator {
 public:
  using key_type = T;
  using reference = key_type &;
  using const_reference = const reference;
  using pointer = key_type *;
  using tree_node = s21::Node<key_type>;
  using iterator = Iterator;

  Iterator() = delete;

  Iterator(tree_node *Node) : ptr_node_(Node) {}

  Iterator(const iterator &it) : ptr_node_(it.ptr_node_) {}

  Iterator(iterator &&it) : ptr_node_(std::move(it.ptr_node_)) {}

  Iterator &operator=(const iterator &it) {
    ptr_node_ = it.ptr_node_;
    return *this;
  }

  Iterator &operator=(iterator &&it) {
    ptr_node_ = std::move(it.ptr_node_);
    return *this;
  }

  ~Iterator() {}

  iterator &operator++() {
    if (!ptr_node_) {
      return *this;
    }

    if (ptr_node_->parent == nullptr) {
      ptr_node_ = ptr_node_->left;
      while (ptr_node_->right) ptr_node_ = ptr_node_->right;
      return *this;
    }

    if (ptr_node_->right) {
      ptr_node_ = ptr_node_->right;
      while (ptr_node_->left) ptr_node_ = ptr_node_->left;
    } else {
      tree_node *temp;
      while ((temp = ptr_node_->parent) && ptr_node_ == temp->right) {
        ptr_node_ = temp;
      }
      ptr_node_ = temp;
    }
    return *this;
  }

  reference operator*() { return ptr_node_->key; }

  iterator operator++(int) {
    iterator tmp{ptr_node_};
    ++(*this);
    return tmp;
  }

  iterator &operator--() {
    if (!ptr_node_) {
      return *this;
    }

    if (ptr_node_->left) {
      ptr_node_ = ptr_node_->left;
      while (ptr_node_->right) ptr_node_ = ptr_node_->right;
    } else {
      tree_node *temp;
      while ((temp = ptr_node_->parent) && ptr_node_ == temp->left) {
        ptr_node_ = temp;
      }
      ptr_node_ = temp;
    }
    return *this;
  }

  iterator operator--(int) {
    iterator tmp{ptr_node_};
    --(*this);
    return tmp;
  }

  bool operator==(const iterator &other) {
    return ptr_node_ == other.ptr_node_;
  }

  bool operator!=(const iterator &other) {
    return ptr_node_ != other.ptr_node_;
  }

  tree_node *ptr_node_;
};

template <class T>
class ConstIterator {
 public:
  using key_type = T;
  using tree_node = s21::Node<key_type>;
  using iterator = ConstIterator<key_type>;
  using pointer = const key_type *;
  using reference = const key_type &;
  tree_node *ptr_node_;

  ConstIterator() = delete;

  ConstIterator(tree_node *Node) : ptr_node_(Node) {}

  ConstIterator(const iterator &it) : ptr_node_(it.ptr_node_) {}

  ConstIterator(iterator &&it) : ptr_node_(std::move(it.ptr_node_)) {}

  ConstIterator &operator=(const iterator &it) {
    ptr_node_ = it.ptr_node_;
    return *this;
  }

  ConstIterator &operator=(iterator &&it) {
    ptr_node_ = std::move(it.ptr_node_);
    return *this;
  }

  ~ConstIterator() = default;

  iterator &operator++() {
    if (!ptr_node_) {
      return *this;
    }
    if (ptr_node_->parent == nullptr) {
      ptr_node_ = ptr_node_->left;
      while (ptr_node_->right) ptr_node_ = ptr_node_->right;
      return *this;
    }

    if (ptr_node_->right) {
      ptr_node_ = ptr_node_->right;
      while (ptr_node_->left) ptr_node_ = ptr_node_->left;
    } else {
      tree_node *temp;
      while ((temp = ptr_node_->parent) && ptr_node_ == temp->right) {
        ptr_node_ = temp;
      }
      ptr_node_ = temp;
    }

    return *this;
  }

  iterator &operator--() {
    if (!ptr_node_) {
      return *this;
    }
    if (ptr_node_->left) {
      ptr_node_ = ptr_node_->left;
      while (ptr_node_->right) ptr_node_ = ptr_node_->right;
    } else {
      tree_node *temp;
      while ((temp = ptr_node_->parent) && ptr_node_ == temp->left) {
        ptr_node_ = temp;
      }
      ptr_node_ = temp;
    }
    return *this;
  }

  iterator operator--(int) {
    iterator tmp{ptr_node_};
    --(*this);
    return tmp;
  }

  bool operator==(const iterator &other) {
    return ptr_node_ == other.ptr_node_;
  }

  bool operator!=(const iterator &other) {
    return ptr_node_ != other.ptr_node_;
  }

  reference operator*() { return ptr_node_->key; }

  iterator operator++(int) {
    iterator tmp{ptr_node_};
    ++(*this);
    return tmp;
  }
};
}  // namespace s21
#endif  // S21_CONTAINERS_ITERATOR_S21_ITERATOR_H_