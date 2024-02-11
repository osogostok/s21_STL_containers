#include "s21_test.h"

template <typename key_type>
bool compare_set(s21::set<key_type> my_set, std::set<key_type> std_set) {
  bool res = true;
  auto i2 = my_set.begin();
  for (auto i1 = std_set.begin(); i1 != std_set.end(); ++i1, ++i2) {
    if ((*i1) != (*i2)) res = false;
  }
  return res;
}

TEST(set, default_constructor_1) {
  s21::set<int> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(set, default_constructor_2) {
  s21::set<char> A;
  ASSERT_TRUE(A.empty());
  EXPECT_EQ(A.size(), 0);
}

TEST(set, constructor) {
  s21::set<int> A{1, 2, 3, 4};
  std::set<int> B{1, 2, 3, 4};
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), 4);
}

TEST(set, insert) {
  s21::set<int> A;
  std::set<int> B;
  A.insert(21);
  B.insert(21);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, copy_constructor) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A;
  auto B1 = B;
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(set, move_constructor_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = std::move(A);
  auto B1 = std::move(B);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(set, operator_copy) {
  s21::set<char> A = {
      'b',
      'c',
  };
  s21::set<char> A1 = {'b', 'c', 'd', 'a'};
  std::set<char> B = {
      'b',
      'c',
  };
  std::set<char> B1 = {'b', 'c', 'd', 'a'};
  A = A1;
  B = B1;
  EXPECT_TRUE(compare_set(A1, B1));
}

TEST(set, operator_move) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  s21::set<int> A1;
  A1 = std::move(A);
  std::set<int> B1;
  B1 = std::move(B);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
}

TEST(set, func_begin_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_begin_2) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A.erase(A1);
  B.erase(B1);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}
TEST(set, func_end_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1--, B1--;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_end_2) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1++, B1++;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_end_3) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  --A1, --B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_end_4) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  ++A1, ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_cend_1) {
  const s21::set<int> A = {9, 10, 123, -4};
  const std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  --A1, --B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_cend_2) {
  const s21::set<int> A = {9, 10, 123, -4};
  const std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.end();
  auto B1 = B.end();
  A1--, B1--;
  EXPECT_EQ((*A1), (*B1));
}
TEST(set, func_cbegin_1) {
  const s21::set<int> A = {9, 10, 123, -4};
  const std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A1++, B1++;
  EXPECT_EQ((*A1), (*B1));
}
TEST(set, func_cbegin_2) {
  const s21::set<int> A = {9, 10, 123, -4};
  const std::set<int> B = {9, 10, 123, -4};
  auto A1 = A.begin();
  auto B1 = B.begin();
  ++A1, ++B1;
  EXPECT_EQ((*A1), (*B1));
}

TEST(set, func_empty_1) {
  s21::set<int> A = {9, 10, 123, -4};
  EXPECT_FALSE(A.empty());
}

TEST(set, func_empty_2) {
  s21::set<int> A;
  EXPECT_TRUE(A.empty());
}

TEST(set, func_empty_3) {
  s21::set<int> A = {9, 10, 123, -4};
  A.clear();
  EXPECT_TRUE(A.empty());
}

TEST(set, func_size_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_size_2) {
  s21::set<int> A;
  std::set<int> B;
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_clear_0) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  A.clear();
  B.clear();
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  EXPECT_EQ(A.insert(3).second, B.insert(3).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_2) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  EXPECT_EQ(A.insert(9).second, B.insert(9).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_3) {
  s21::set<int> A;
  std::set<int> B;
  EXPECT_EQ(A.insert(9).second, B.insert(9).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_4) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  EXPECT_FALSE(A.insert(9).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}
TEST(set, func_insrt_5) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4, 1};
  EXPECT_TRUE(A.insert(1).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_6) {
  s21::set<int> A;
  std::set<int> B = {9};
  EXPECT_TRUE(A.insert(9).second);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}
TEST(set, func_clear_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  A.clear();
  B.clear();
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_clear_2) {
  s21::set<int> A;
  std::set<int> B;
  A.clear();
  B.clear();
  EXPECT_EQ(A.empty(), B.empty());
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_erase_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  EXPECT_ANY_THROW(A.erase(A.end()));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_swap_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  s21::set<int> A1;
  std::set<int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(set, func_swap_2) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  s21::set<int> A1 = {1, 2, 3, 4, 5};
  std::set<int> B1 = {1, 2, 3, 4, 5};
  A1.swap(A);
  B1.swap(B);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(set, func_swap_3) {
  s21::set<int> A;
  std::set<int> B;
  s21::set<int> A1;
  std::set<int> B1;
  A1.swap(A);
  B1.swap(B);
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
}

TEST(set, func_merge_1) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  s21::set<int> A1 = {1, 2, 3, 4, 5};
  std::set<int> B1 = {1, 2, 3, 4, 5};
  B1.merge(B);
  A1.merge(A);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(set, func_merge_2) {
  s21::set<int> A = {9, 10, 123, -4};
  std::set<int> B = {9, 10, 123, -4};
  s21::set<int> A1;
  std::set<int> B1;
  A1.merge(A);
  B1.merge(B);
  EXPECT_TRUE(compare_set(A1, B1));
  EXPECT_EQ(A1.size(), B1.size());
  EXPECT_EQ(A1.empty(), B1.empty());
  EXPECT_EQ(A.size(), B.size());
  EXPECT_EQ(A.empty(), B.empty());
}

TEST(set, func_contains_1) {
  s21::set<int> A{1, 2, 3, 4, 5};
  EXPECT_TRUE(A.contains(1));
}

TEST(set, func_contains_2) {
  s21::set<int> A{1, 2, 3, 4, 5};
  EXPECT_FALSE(A.contains(6));
}

TEST(set, func_find_1) {
  s21::set<int> A{1, 2, 3, 4, 5};
  std::set<int> B{1, 2, 3, 4, 5};
  auto A1 = A.find(2);
  auto B1 = B.find(2);
  EXPECT_TRUE((*A1) == (*B1));
}

TEST(set, func_find_2) {
  s21::set<int> A{1, 2, 3, 4, 5};
  auto A1 = A.find(6);
  auto A2 = A.end();
  EXPECT_TRUE(A1 == A2);
}

TEST(set, func_insert_many_1) {
  s21::set<int> A{1, 2, 3, 4, 5, 5, 5, 5, -4};
  std::set<int> B{1, 2, 3, 4, 5, 5, 5, 5, -4, 9, 9, 7, 4};
  A.insert_many(9, 9, 7, 4);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, func_insert_many_2) {
  s21::set<int> A;
  std::set<int> B{9, 9, 7, 4};
  A.insert_many(9, 9, 7, 4);
  EXPECT_TRUE(compare_set(A, B));
  EXPECT_EQ(A.size(), B.size());
}

TEST(set, max_size_function) {
  s21::set<int> A{9, 9, 7, 4};
  std::set<int> B{9, 9, 7, 4};

  EXPECT_EQ(A.max_size(), B.max_size());

  std::set<int> A1;
  s21::set<int> B1;

  EXPECT_EQ(A1.max_size(), B1.max_size());
}

TEST(set, big_erase_1) {
  s21::set<int> A{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  std::set<int> B{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  auto A1 = A.begin();
  auto B1 = B.begin();
  A.erase(A1);
  B.erase(B1);

  auto A2 = A.begin();
  auto B2 = B.begin();
  ++A2;
  ++A2;
  ++B2;
  ++B2;
  A.erase(A2);
  B.erase(B2);
  EXPECT_TRUE(compare_set(A, B));

  for (int i = 0; i < 11; ++i) {
    auto A3 = A.begin();
    A.erase(A3);
  }
  EXPECT_TRUE(A.empty());
}

TEST(set, big_erase_2) {
  s21::set<int> A;
  std::set<int> B;

  for (int i = 5; i < 85; ++i) {
    A.insert(i);
    B.insert(i);
  }

  for (int i = 6; i < 79; i += 5) {
    auto A1 = A.find(i);
    auto B1 = B.find(i);
    A.erase(A1);
    B.erase(B1);
  }
  EXPECT_TRUE(compare_set(A, B));
}