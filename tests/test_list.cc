#include "s21_test.h"

TEST(list, default_constructor) {
  std::list<int> std_list;
  s21::list<int> s21_list;

  EXPECT_EQ(std_list.size(), s21_list.size());
}

TEST(list, parameterized_constructor) {
  std::list<int> std_list(3);
  s21::list<int> s21_list(3);

  auto s21_it = s21_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list.size(), s21_list.size());
}

TEST(list, list_constructor) {
  std::list<int> std_list = {1, 2, 3};
  s21::list<int> s21_list = {1, 2, 3};

  auto s21_it = s21_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list.size(), s21_list.size());
}

TEST(list, copy_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  std::list<int> std_list2(std_list1);
  s21::list<int> s21_list2(s21_list1);

  auto s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, move_constructor) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  std::list<int> std_list2(std::move(std_list1));
  s21::list<int> s21_list2(std::move(s21_list1));

  auto s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, copy_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  s21::list<int> s21_list2 = {5, 4, 3, 2, 1};

  std_list2 = std_list1;
  s21_list2 = s21_list1;

  auto s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, move_operator) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  s21::list<int> s21_list2 = {5, 4, 3, 2, 1};

  std_list2 = std::move(std_list1);
  s21_list2 = std::move(s21_list1);

  auto s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, front_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.front(), s21_list1.front());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.front(), s21_list2.front());
}

TEST(list, back_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.back(), s21_list1.back());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.back(), s21_list2.back());
}

TEST(list, begin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(*std_list2.begin(), *s21_list2.begin());
}

TEST(list, cbegin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.cbegin(), *s21_list1.cbegin());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(*std_list2.cbegin(), *s21_list2.cbegin());
}

TEST(list, end_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.end()), *(--s21_list1.end()));

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(*std_list2.end(), *s21_list2.end());
}

TEST(list, cend_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*(--std_list1.cend()), *(--s21_list1.cend()));

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(*std_list2.cend(), *s21_list2.cend());
}

TEST(list, empty_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.empty(), s21_list1.empty());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.empty(), s21_list2.empty());
}

TEST(list, size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, max_size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.max_size(), s21_list1.max_size());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.max_size(), s21_list2.max_size());
}

TEST(list, clear_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.clear();
  s21_list1.clear();

  EXPECT_EQ(std_list1.size(), s21_list1.size());
}

TEST(list, insert_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto std_pos = std_list1.insert(std_list1.begin(), 0);
  auto s21_pos = s21_list1.insert(s21_list1.begin(), 0);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(*std_pos, *s21_pos);

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_pos = std_list1.insert(--std_list1.end(), 0);
  s21_pos = s21_list1.insert(--s21_list1.end(), 0);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(*std_pos, *s21_pos);

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, erase_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.erase(std_list1.begin());
  s21_list1.erase(s21_list1.begin());

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1.erase(--std_list1.end());
  s21_list1.erase(--s21_list1.end());

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, push_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_back(6);
  s21_list1.push_back(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_back();
  s21_list1.pop_back();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, push_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_front(6);
  s21_list1.push_front(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_front();
  s21_list1.pop_front();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, swap_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  s21::list<int> s21_list2 = {5, 4, 3, 2, 1};

  std_list1.swap(std_list2);
  s21_list1.swap(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());
  EXPECT_EQ(*std_list2.begin(), *s21_list2.begin());
}

TEST(list, merge_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {9, 8, 7};
  s21::list<int> s21_list2 = {9, 8, 7};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7};
  s21_list1 = {9, 8, 7};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {1, 2, 3, 4, 5};
  s21_list1 = {1, 2, 3, 4, 5};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, splice_function) {
  std::list<int> std_list1 = {1, 2, 3, 4};
  s21::list<int> s21_list1 = {1, 2, 3, 4};

  std::list<int> std_list2 = {9, 8, 7};
  s21::list<int> s21_list2 = {9, 8, 7};

  std_list1.splice(std_list1.end(), std_list2);
  s21_list1.splice(s21_list1.cend(), s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list2.splice(std_list2.begin(), std_list1);
  s21_list2.splice(s21_list2.cbegin(), s21_list1);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  s21_it = s21_list2.begin();
  for (auto std_it = std_list2.begin(); std_it != std_list2.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, reverse_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std_list1.reverse();
  s21_list1.reverse();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, unique_function) {
  std::list<int> std_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};
  s21::list<int> s21_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};

  std_list1.unique();
  s21_list1.unique();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, sort_function) {
  std::list<int> std_list1 = {2, 7, 1, 3, 8, 5};
  s21::list<int> s21_list1 = {2, 7, 1, 3, 8, 5};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7, 6, 5};
  s21_list1 = {9, 8, 7, 6, 5};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_function) {
  std::list<int> std_list1 = {1, 6, 7, 8, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  auto pos = s21_list1.insert_many(++s21_list1.cbegin(), 6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());
  EXPECT_EQ(6, *pos);

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {1, 6, 7, 8, 2, 3, 4, 0, 0, 0, 5};

  pos = s21_list1.insert_many(--s21_list1.cend(), 0, 0, 0);

  EXPECT_EQ(11, s21_list1.size());
  EXPECT_EQ(0, *pos);

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_back(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_front_function) {
  std::list<int> std_list1 = {6, 7, 8, 1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_front(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}
