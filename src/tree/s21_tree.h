#ifndef S21_CONTAINERS_TREE_S21_TREE_H_
#define S21_CONTAINERS_TREE_S21_TREE_H_
#include <functional>
#include <iostream>
#include <limits>
#include <utility>

#include "../iterator/s21_iterator.h"

namespace s21 {
template <class K, class Compare = std::less<K>>
class RBTree {
 public:
  using key_type = K;
  using reference = key_type &;
  using const_reference = const key_type &;
  using size_type = std::size_t;
  using tree_type = RBTree;
  using tree_node = s21::Node<key_type>;
  using iterator = s21::Iterator<key_type>;
  using const_iterator = s21::ConstIterator<key_type>;

 public:
  RBTree() : head_(new tree_node), size_(0){};
  RBTree(const tree_type &other);
  RBTree(tree_type &&other);
  RBTree &operator=(const tree_type &other);
  RBTree &operator=(tree_type &&other);
  ~RBTree();

  iterator TreeBegin() noexcept;
  iterator TreeEnd() noexcept;
  const_iterator TreeConstEnd() const noexcept;
  const_iterator TreeConstBegin() const noexcept;
  iterator TreeSearch(const_reference key);
  const_iterator TreeConstSearch(const_reference key) const;
  bool TreeEmpty() const noexcept;
  size_type TreeSize() const noexcept;
  size_type TreeMaxSize() noexcept;
  iterator TreeErase(iterator pos);
  void TreeClear();
  void TreeSwap(tree_type &other);
  void TreeMerge(tree_type &other);
  void TreeMergeUniq(tree_type &other);
  iterator TreeLowerBound(const key_type &key);
  iterator TreeUpperBound(const key_type &key);
  std::pair<iterator, bool> Insert(const key_type &key);
  void NotUniq() { flag_uniq = false; }

 private:
  tree_node *head_;
  size_type size_;
  Compare less_;
  bool flag_uniq = true;

  tree_node *&root_() const;
  bool IsRed(tree_node *node);
  bool equal(key_type key_1, key_type key_2);
  tree_node *FixUp(tree_node *node);
  tree_node *MostMin(tree_node *node) const;
  tree_node *ColorFlip(tree_node *node);
  tree_node *RotateLeft(tree_node *node);
  tree_node *RotateRight(tree_node *node);
  tree_node *SwapAndDeletenodes(tree_node *node);
  tree_node *LeanRight(tree_node *node);
  tree_node *DeleteMin(tree_node *node);
  tree_node *MoveRedLeft(tree_node *node);
  tree_node *MoveRedRight(tree_node *node);
  tree_node *TreeCopy(const tree_node *node);
  void TreeClear(tree_node *node);
  tree_node *Insert(tree_node *node, tree_node *Parent, const key_type &key,
                    std::pair<iterator, bool> &pair_res);
  tree_node *TreeErase(tree_node *node, iterator pos);
  bool EqualNodes(tree_node *node_1, tree_node *node_2);
  void RessetingParents(tree_node *node);
};
}  // namespace s21
#include "s21_tree.tcc"
#endif  // S21_CONTAINERS_TREE_S21_TREE_H_