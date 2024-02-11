#include "s21_tree.h"

namespace s21 {
template <class key_type, class Compare>
RBTree<key_type, Compare>::RBTree(const tree_type &other) : RBTree() {
  TreeClear(root_());
  try {
    root_() = TreeCopy(other.root_());
  } catch (...) {
    TreeClear();
  }
  size_ = other.size_;
  less_ = other.less_;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::TreeCopy(const tree_node *node) {
  if (!node) return nullptr;
  tree_node *copy;
  copy = new tree_node(node->key);
  if (node->left) copy->left = TreeCopy(node->left);
  if (node->right) copy->right = TreeCopy(node->right);
  copy->parent = node->parent;
  copy->color = node->color;
  return copy;
}

template <class key_type, class Compare>
RBTree<key_type, Compare>::RBTree(tree_type &&other) : RBTree() {
  TreeClear(root_());
  root_() = nullptr;
  TreeSwap(other);
}

template <typename key_type, typename Compare>
RBTree<key_type, Compare> &RBTree<key_type, Compare>::operator=(
    tree_type &&other) {
  TreeClear();
  TreeSwap(other);
  return *this;
}

template <class key_type, class Compare>
RBTree<key_type, Compare>::~RBTree() {
  if (head_) {
    TreeClear();
    delete head_;
  }
}

template <class key_type, class Compare>
std::pair<typename RBTree<key_type, Compare>::iterator, bool>
RBTree<key_type, Compare>::Insert(const key_type &key) {
  bool flag_insert = false;
  iterator iterator_res = nullptr;
  std::pair<iterator, bool> pair_res(iterator_res, flag_insert);
  try {
    root_() = Insert(root_(), nullptr, key, pair_res);
  } catch (...) {
    TreeClear();
  }
  if (head_->left) head_->left->parent = head_;
  return pair_res;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::Insert(tree_node *node, tree_node *Parent,
                                  const key_type &key,
                                  std::pair<iterator, bool> &pair_res) {
  if (!node) {
    node = new tree_node(key);
    node->parent = Parent;
    ++size_;
    pair_res = {iterator(node), true};
  } else {
    bool compare_less = less_(key, node->key);
    bool compare_equal = equal(key, node->key);
    if (compare_equal && flag_uniq) {
      pair_res = {iterator(node), false};
    } else {
      if (compare_less) {
        node->left = Insert(node->left, node, key, pair_res);
      } else {
        node->right = Insert(node->right, node, key, pair_res);
      }
    }
  }
  return FixUp(node);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *RBTree<key_type, Compare>::FixUp(
    tree_node *node) {
  if (IsRed(node->right)) node = RotateLeft(node);
  if (IsRed(node->left) && node->left && IsRed(node->left->left))
    node = RotateRight(node);
  if (IsRed(node->left) && IsRed(node->right)) node = ColorFlip(node);
  if (root_()) root_()->color = BLACK;
  return node;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeErase(iterator pos) {
  if (pos == TreeEnd()) throw std::runtime_error("s21::erase");
  iterator temp = pos;
  ++temp;
  TreeErase(root_(), pos);
  if (root_()) root_()->color = BLACK;
  return temp;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::TreeErase(tree_node *node, iterator pos) {
  const key_type key = pos.ptr_node_->key;
  bool compare_less = less_(key, node->key);
  if (compare_less) {
    if (!IsRed(node->left) && !IsRed(node->left->left))
      node = MoveRedLeft(node);
    node->left = TreeErase(node->left, pos);
  } else {
    if (IsRed(node->left) && node->right) node = LeanRight(node);
    if (!IsRed(node->right) && node->right && !IsRed(node->right->left))
      node = MoveRedRight(node);
    if (EqualNodes(pos.ptr_node_, node)) {
      if (node->right) {
        node = SwapAndDeletenodes(node);
      } else {
        RessetingParents(node);
        delete node;
        --size_;
        return nullptr;
      }
    } else {
      if (equal(key, node->key))
        node->left = TreeErase(node->left, pos);
      else
        node->right = TreeErase(node->right, pos);
    }
  }
  return FixUp(node);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::MoveRedLeft(tree_node *node) {
  node = ColorFlip(node);
  if (IsRed(node->right->left)) {
    node->right = RotateRight(node->right);
    node = RotateLeft(node);
    node = ColorFlip(node);
  }
  return node;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::MoveRedRight(tree_node *node) {
  node = ColorFlip(node);
  if (node->left && IsRed(node->left->left)) {
    node = RotateRight(node);
    node = ColorFlip(node);
  }
  return node;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::LeanRight(tree_node *node) {
  tree_node *temp = RotateRight(node);
  temp->color = temp->right->color;
  temp->right->color = RED;
  return temp;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::RotateLeft(tree_node *node) {
  tree_node *temp = node->right;
  node->right = temp->left;
  if (temp->left) temp->left->parent = node;
  temp->left = node;
  temp->parent = node->parent;
  if (node == root_()) root_() = temp;
  node->parent = temp;
  temp->color = temp->left->color;
  temp->left->color = RED;
  return temp;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::RotateRight(tree_node *node) {
  tree_node *temp = node->left;
  node->left = temp->right;
  if (temp->right) temp->right->parent = node;
  temp->right = node;
  temp->parent = node->parent;
  if (node == root_()) root_() = temp;
  node->parent = temp;
  temp->color = temp->right->color;
  temp->right->color = RED;
  return temp;
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::RessetingParents(tree_node *node) {
  if (EqualNodes(node->parent->right, node)) node->parent->right = node->right;
  if (EqualNodes(node->parent->left, node)) node->parent->left = node->left;
  if (node->left) node->left->parent = node->parent;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::ColorFlip(tree_node *node) {
  node->color = !node->color;
  if (node->left) node->left->color = !node->left->color;
  if (node->right) node->right->color = !node->right->color;
  return node;
}

template <class key_type, class Compare>
bool RBTree<key_type, Compare>::IsRed(tree_node *node) {
  return (node != nullptr && node->color == RED);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::SwapAndDeletenodes(tree_node *node) {
  tree_node *temp = MostMin(node->right);
  if (node->parent->left == node)
    node->parent->left = temp;
  else
    node->parent->right = temp;
  if (temp->parent->left == temp)
    temp->parent->left = node;
  else
    temp->parent->right = node;
  std::swap(node->parent, temp->parent);
  std::swap(node->left, temp->left);
  std::swap(node->right, temp->right);
  std::swap(node->color, temp->color);
  if (node->left) node->left->parent = node;
  if (node->right) node->right->parent = node;
  if (temp->left) temp->left->parent = temp;
  if (temp->right) temp->right->parent = temp;
  temp->right = DeleteMin(temp->right);
  --size_;
  return temp;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeBegin() noexcept {
  tree_node *node = MostMin(head_);
  return iterator(node);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *&
RBTree<key_type, Compare>::root_() const {
  return head_->left;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeEnd() noexcept {
  return iterator(head_);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::const_iterator
RBTree<key_type, Compare>::TreeConstEnd() const noexcept {
  return const_iterator(head_);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::const_iterator
RBTree<key_type, Compare>::TreeConstBegin() const noexcept {
  tree_node *node = MostMin(head_);
  return const_iterator(node);
}

template <class key_type, class Compare>
bool RBTree<key_type, Compare>::TreeEmpty() const noexcept {
  return size_ == 0;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::size_type
RBTree<key_type, Compare>::TreeSize() const noexcept {
  return size_;
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::size_type
RBTree<key_type, Compare>::TreeMaxSize() noexcept {
  return std::numeric_limits<size_t>::max() / sizeof(tree_node) / 2;
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::TreeClear() {
  TreeClear(root_());
  size_ = 0;
  head_->left = nullptr;
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::TreeClear(tree_node *node) {
  if (node != nullptr) {
    TreeClear(node->left);
    TreeClear(node->right);
    delete node;
  }
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::TreeSwap(tree_type &other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
  std::swap(less_, other.less_);
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::TreeMergeUniq(tree_type &other) {
  auto i = other.TreeBegin();
  std::pair<iterator, bool> res{other.TreeBegin(), false};
  while (i != other.TreeEnd()) {
    res = Insert(i.ptr_node_->key);
    if (res.second)
      i = other.TreeErase(i);
    else
      ++i;
  }
}

template <class key_type, class Compare>
void RBTree<key_type, Compare>::TreeMerge(tree_type &other) {
  for (auto i = other.TreeBegin(); i != other.TreeEnd(); ++i)
    Insert(i.ptr_node_->key);
  other.TreeClear();
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeLowerBound(const key_type &key) {
  tree_node *node = root_();
  tree_node *res = TreeEnd().ptr_node_;
  while (node != nullptr) {
    if (!less_(node->key, key)) {
      res = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return iterator(res);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeUpperBound(const key_type &key) {
  tree_node *node = root_();
  tree_node *res = TreeEnd().ptr_node_;
  while (node != nullptr) {
    if (less_(key, node->key)) {
      res = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return iterator(res);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::const_iterator
RBTree<key_type, Compare>::TreeConstSearch(const_reference key) const {
  tree_node *node = root_();
  while (node) {
    int compare_less = less_(key, node->key);
    if (!(less_(key, node->key) || less_(node->key, key))) {
      return const_iterator(node);
    } else if (compare_less) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return TreeConstEnd();
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::iterator
RBTree<key_type, Compare>::TreeSearch(const_reference key) {
  tree_node *node = root_();
  while (node) {
    int compare_less = less_(key, node->key);
    if (!(less_(key, node->key) || less_(node->key, key))) {
      return iterator(node);
    } else if (compare_less) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return TreeEnd();
}

template <class key_type, class Compare>
bool RBTree<key_type, Compare>::EqualNodes(tree_node *node_1,
                                           tree_node *node_2) {
  int flag = 0;
  if (node_1 && node_2) {
    flag += (node_1->key == node_2->key);
    if (node_1->right && node_2->right) {
      flag += (node_1->right->key == node_2->right->key);
    } else {
      flag += ((node_1->right == nullptr) && (node_2->right == nullptr));
    }
    if (node_1->left && node_2->left) {
      flag += (node_1->left->key == node_2->left->key);
    } else {
      flag += ((node_1->left == nullptr) && (node_2->left == nullptr));
    }
    flag += (node_1->color == node_2->color);
  }
  return (flag == 4);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::DeleteMin(tree_node *node) {
  if (node->left == nullptr) {
    delete node;
    return nullptr;
  }
  if (!IsRed(node->left) && node->left && !IsRed(node->left->left))
    node = MoveRedLeft(node);
  node->left = DeleteMin(node->left);
  return FixUp(node);
}

template <class key_type, class Compare>
typename RBTree<key_type, Compare>::tree_node *
RBTree<key_type, Compare>::MostMin(tree_node *node) const {
  if (!node->left) return node;
  return MostMin(node->left);
}

template <class key_type, class Compare>
bool RBTree<key_type, Compare>::equal(key_type key_1, key_type key_2) {
  return (!(less_(key_1, key_2)) && !(less_(key_2, key_1)));
}
};  // namespace s21