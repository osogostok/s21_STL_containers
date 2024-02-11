CC=g++
OPTION_FLAGS=-Wall -Werror -Wextra -g
CPP_FLAGS=-lstdc++ -std=c++17 
GCOV_FLAGS=--coverage
GTEST_FLAGS=-lgtest

OS := $(shell uname -s)

ifeq ($(OS), Linux)
	TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	TEST_FLAGS = -lcheck
endif

DIR_TEST=./tests
DIR_SRC=./src
SRC_DIRS= map set multiset stack queue list vector array iterator tree


SRC_FILES := $(wildcard $(addsuffix /*.cc,$(DIR_SRC)$(SRC_DIRS)))
OBJ_FILES := $(patsubst %.cc,%.o,$(SRC_FILES))

TEST_FILES := $(wildcard $(addsuffix /*.cc,$(DIR_TEST)))
TEST_OBJ := $(patsubst %.cc,%.o,$(TEST_FILES))

LIBRARY_NAME = s21_containers.a


.PHONY: all clean test build clang gcov_report valgrind leak

SRC_ALL_FILES = $(SRC_MAP)test_map.cc $(SRC_SET)test_set.cc $(SRC_MULTISET)test_multiset.cc $(SRC_STACK)test_stack.cc $(SRC_QUEUE)test_queue.cc $(SRC_LIST)test_list.cc $(SRC_VECTOR)test_vector.cc $(SRC_ARRAY)test_array.cc

all: test

test: $(LIBRARY_NAME) $(TEST_OBJ)
	@$(CC) $(OPTION_FLAGS) $(CPP_FLAGS) $^ -o test $(GTEST_FLAGS) $(TEST_FLAGS)
	@./test
	@rm -rf ./tests/*.o


build: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJ_FILES)
	@ar rcs $(LIBRARY_NAME) $(OBJ_FILES)

%.o: %.cc
	@$(CC) $(OPTION_FLAGS) $(CPP_FLAGS) -c $< -o $@

%.o: $(DIR_TEST)/%.cc
	@$(CC) $(OPTION_FLAGS) $(CPP_FLAGS) -c $<

clang:
	@bash ./tests/clang.sh 
	
gcov_report: clean
	@$(CC) $(OPTION_FLAGS) $(GCOV_FLAGS) s21_test.cc $(SRC_ALL_FILES) -o test $(GTEST_FLAGS) $(CPP_FLAGS) $(TEST_FLAGS)
	@./test
# gcov test
# lcov -t "test" -o test.info -c -d . --no-external
# genhtml -o report/ test.info
# rm -rf *.o *.gcno *.gcda *.info ./test
# open ./report/index.html
	@mkdir report && cd report && gcovr -r ../ --html --html-details -o index.html
	@rm -rf *.o *.gcno *.gcda *.info ./test
	@open report/index.html

valgrind: build
	@valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

leak: test
	@CK_FORK=no leaks --atExit -- ./test

clean:
	@rm -rf ./tests/*.o test main report *.a *.gcno *.gcda *.gcov *.info .clang-format
